#include<fstream>
#include<iostream>
#include "Read.h"
#include <vector>
using namespace std;

/*
Observações
{
	-Apenas as mudanças de um método para outro foram comentadas
	-Na majoritaria parcela dos casos, a palavra "comparador" foi utilizada para indicar um parâmetro da classe Data de cada nó, 
		que foi preenchido para cada nó na leitura do csv, logo quando for usado comparador, na verdade é suposto a ser dito:
		diretor, elenco, ano de lançamento, descrição, listado_em, etc...
}
*/

bool Compare(string s_1, string s_2){ 		//Função para comparar strings, baseado em s_1
	bool equal = true; 						//começa como iguais
	for (int i = 0; i < s_1.length(); i++){ //No tamanho de s_1
		if (s_1[i] != s_2[i]){				//Compara pra ver se existe alguma letra diferente
			equal = false;					
		}
	}
	return equal;
}

class Analysis{ 							//Modulado em uma classe de analise
	
	private:
		
		Tree arv;							//Guarda a arvore referente a analise do csv
		
		void WriteToFile( 					//Funcao para escrever os resultados em um txt
					int N,					//Recebe um int referente a quantidade de resultados
					string operationName,   //Nome da operacao de data science (para diferenciar os arquivos)
					string (Data::*infoType)(), //endereco para o metodo da classe Data (utilizado para escolher a informacao a guardar)
					Data * cArray //Os resultados em si
					){
			
			ofstream myFile (operationName.c_str()); //Cria o arquivo no modo escrita (ofstream), utilizando como nome o operationName passado

			for (int i = 0; i < N; i++){ //Para todos os resultados
				myFile << (cArray[i].*infoType)(); //Escrev, na mesma linha, a informação (especificada em infoType) referente a aquele resultado
				myFile <<";"; //utiliza do ; como um separador entre resultados
			}						
		}
		
		void WriteToFile( //Sobrecarga para o método anterior, diferindo por trabalhar com uma contagem de resultados iguais
					int N,
					string operationName,
					string (Data::*infoType)(),
					int * cCount, //Array para contagem de resultados com mesmo sentido
					string * cArray //Array para string (identificador para a contagem)
					){

			ofstream myFile (operationName.c_str());
			//Coloca o identificador em uma linha do txt, e a contagem em outra
			for (int i = 0; i < N; i++){
				myFile << *(cArray + i);
				myFile <<";";
			}	
			
			myFile<<"\n";
			
			for (int j = 0; j < N; j++){
				myFile << *(cCount + j);
				myFile <<";";
			}	
			
		}
		
		void WriteToFile( //Outra sobrecarga para o método anteriormente citado, diferindo por trabalhar com uma matriz de resultados
					int N,
					string operationName,
					string (Data::*infoType)(), 
					string (Data::*comparatorType)(), //endereco para o metodo da classe Data (utilizado para escolher a informacao que foi procurada na listagem)
					vector < vector<Data> > cMatrix //Matriz para resultados da listagem per fator
					){
						
			ofstream myFile (operationName.c_str());
			//Tendo que a função que utiliza este método propõe a listagem de elementos baseado em fatores comuns (identificados em comparatorType)
			//E que este método propõe gravar os resultados como um tabela, com elementos de mesmo comparador por coluna
			for (int a = 0; a < N; a++){
				
				if (a != 0){ //Coloca os elementos utilizados como comparadores
					myFile<<(cMatrix[a][0].*comparatorType)();
					myFile<<";";
				}
				
				else {
					myFile<<"None"; //ou "None" caso tais não existam (filme sem diretor, etc...)
					myFile<<";";
				}
			}
			
			myFile<<"\n"; //Na linha abaixo
			
			int size = 0;
			//Procura o máximo de elementos referentes a um dado comparador			
			for (int i = 0; i < N; i++){
				
				if ( size < cMatrix[i].size()){
					size = cMatrix[i].size();
				}

			}
			//E para essa dada quantidade de linhas
			for (int j = 0; j < size; j++){
				//E na quantidade de comparadores
				for (int k = 0; k < N; k++){
					if (k < cMatrix[j].size()){ //Tendo o elemento como existente
						myFile << ((cMatrix.at(j))[k].*infoType)(); //Grava a informação pedida, em infoType, na linha atual e coluna do comparador
					}
					//Do contrário só separa os elementos
					myFile<<";";
				}
				//Pula para a próxima linha de elementos
				myFile<<"\n";
				
			}
		}
		
		void FilterAux( //Método auxiliar para percorrer a árvore em ordem, enquanto filtra e guarda os elementos baseado no que foi passado
					Node * node, //Nó atual
					int N, //Quantidade de comparadores para filtrar os elementos
					int * current, //Index de elementos não filtrados (dado em ponteiro tido problemas com retorno)
					Data * cResults, //Vetor para guardar elementos não filtrados
					string (Data::*comparatorTypes[])(), //Vetor, para guardar endereços para os métodos (da classe Data) que servirão de comparadores
														 //Recebe endereços como &Data::getDirector(), para ao exemplo, comparar diretores
					string * comparators //Vetor de strings para filtrar os elementos baseado em palavras/nomes
										 //Fortemente ordenado com relação ao vetor de comparadores acima
					){
			
			if (node != NULL){ //Se o nó não for nulo
				
				FilterAux(node -> getLeft(), N, current, cResults, comparatorTypes, comparators); //Chama para a esquerda do nó
				
				bool filtered = false; //Um dado elemento começa como não filtrado
				for (int i = 0; i < N; i++){ //Para a quantidade de comparadores
					if ( !Compare( comparators[i], (node->getData().*comparatorTypes[i])() ) ){ //Utiliza função Compare para ver se o elemento (no campo dado) começa com a string dada em comparators[i]
						filtered = true; //Caso o elemento não comece de acordo com a string comparadora, muda o booleano a dizer que o elemento foi filtrado
					}

				}
				
				if (!filtered){ //Caso o elemento não tenha sido filtrado
					*(cResults + *current) = node->getData(); //Coloca o Data dele no vetor
					*current = *current + 1; //Incrementa o index
				}
				
				FilterAux(node -> getRight(), N, current, cResults, comparatorTypes, comparators); //Chama para a direita do nó
				
			}

		}
		
		void FragmentAux( //Função auxiliar para o método de listagem de elementos na arvore
						int b, //Recebe o começo da listagem
						int e, //Recebe o final da listagem
						int s, //e o step (para pular elementos caso desejado)
						Node * node,
						int * current,
						Data * cResults
						){
			
			if (node != NULL){
				
				FragmentAux(b, e, s, node->getLeft(), current, cResults);
				
				if ( *current >= b && *current <= e && (*current % s) == 0 ){ //Se o elemento está em uma posição desejada de listagem
																			  //e está de acordo com o step (não é pra ser pulado)
					*(cResults + ( (*current - b) / s) ) = node->getData(); //Coloca o Data do elemento atual na ultima posição dada (id - começo da listagem) / step
					
				}
				
				*current = *current + 1; //incrementa o current para pular ao proximo elemento
				
				FragmentAux(b, e, s, node->getRight(), current, cResults);
			}	
		}
		
		void ListAux( //Método auxiliar para listar elementos de acordo com fatores iguais, dados no comparatorType 
					  //(caso seja passado &Data::getDirector ao exemplo, listara filmes de acordo com diretores iguais)
				Node* node, 
				string * cStrings, //Vetor para guardar os elementos de um dado comparador (nomes dos diretores, anos, classificação, etc...)
				vector< vector<Data> > * cResults, //Matriz para guardar  os resultados, de acordo com comparadores iguais
				string (Data::*comparatorType)(), 
				int * N, //Index de comparadores achados (ao exemplo, para diretores, a contagem de diretores achados)
				string comparator //uma string para filtrar os resultados (opcional, começa com NULL)
				){
			
			if (node != NULL){
				
				ListAux(node -> getLeft(), cStrings, cResults, comparatorType, N, comparator);
				
				bool foundType = false; //Booleano para indicar se um comparador (referente a o elemento atual), já existe (ao exemplo, se um diretor já existe)
				
				for (int i = 0; i < *N ; i++){ //Para a contagem de comparadores já existentes
					//Se o comparador atual *(cStrings+i) for igual ao campo do elemento atual (node -> getData().*comparatorType)()
					//E o comparador atual não seja vazio (um filme com diretor não existente/indicado, ao exemplo), indicado por !(*(cStrings+i)).empty()
					//E o campo atual no elemento não seja vazio (um filme com diretor não existente/indicado), indicado por !(node -> getData().*comparatorType)().empty()
					if( *(cStrings+i) == (node -> getData().*comparatorType)() && !(*(cStrings+i)).empty() && !(node -> getData().*comparatorType)().empty()){
						
						foundType = true;	//Achou um comparador que seja igual ao elemento atual (no campo indicado)										
						(cResults -> at(i)).push_back(node -> getData()); //No comparador dado pelo indice i, usa o push_back(), para colocar um Data no array referente
						break; //Para de procurar comparadores iguais
					}
					
					//Tendo o comparador atual igual a None, (inserido manualmente para elementos que não informam o campo desejado)
					//E o campo atual no elemento sendo vazio (node -> getData().*comparatorType)().empty()
					else if (*(cStrings+i) == "None" && (node -> getData().*comparatorType)().empty()){
						//Mesma metodologia
						foundType = true;
						(cResults -> at(i)).push_back(node -> getData());
						break;
					}
					
				}
				//Caso não tenha achado um comparador existente, igual ao campo do elemento atual
				//E tendo o elemento atual, não sendo filtrado pela string comparator
				if (!foundType && Compare( comparator, (node -> getData().*comparatorType)() ) ){		
					//Coloca o novo comparador achado no final do vetor			
					*(cStrings + *N) = (node -> getData().*comparatorType)();
					(cResults -> at(*N))[0] = node -> getData(); //Já insere o novo elemento no começo do vetor referente ao comparador, na matriz
					*N = *N + 1; //Incrementa o contador de comparadores existentes
				}
				
				ListAux(node -> getRight(),  cStrings, cResults, comparatorType, N, comparator);	
							
			}
		}

		void CountAux( //Metódo auxiliar da contagem de elementos do mesmo comparador (mesmo diretor, ano, etc...)
				Node* node, 
				string * cStrings,
				int * cResults, //Vetor para int, que guarda a contagem na posição do comparador
				string (Data::*comparatorType)(), 
				int * N,
				string comparator
				){
			//Mesma metodologia do método de listagem
			if (node != NULL){
				
				CountAux(node -> getLeft(), cStrings, cResults, comparatorType, N, comparator);
				
				bool foundType = false;
				
				for (int i = 0; i < *N ; i++){
					if( *(cStrings+i) == (node -> getData().*comparatorType)() && !(*(cStrings+i)).empty() && !(node -> getData().*comparatorType)().empty()){
						//Porém incrementa o contador para elementos iguais
						foundType = true;										
						*(cResults + i) = *(cResults + i) + 1;
						break;
					}
					
					else if (*(cStrings+i) == "None" && (node -> getData().*comparatorType)().empty()){
						
						foundType = true;
						*(cResults + i) = *(cResults + i) + 1;
						break;
					}
					
				}
				
				if (!foundType && Compare( comparator, (node -> getData().*comparatorType)() ) ){					
					*(cStrings + *N) = (node -> getData().*comparatorType)();
					*(cResults + *N) = 1; //Inicializa a contagem como 1, para novos comparadores encontrados
					*N = *N + 1;
				}
				
				CountAux(node -> getRight(),  cStrings, cResults, comparatorType, N, comparator);	
							
			}
		}
		
	public:
	
		Analysis(Tree a){ //Construtor só requerendo a arvore para analise
			arv = a;
		}
		
		//Método para filtrar elementos
		//Baseado nos parâmetros (fortemente ligados), dados em comparatorTypes[] e comparators[]
		//comparatorTypes[] é um vetor de campos (da classe Data), que se quer comparar nos elementos da arvore
		//comparators[] é um vetor de strings (ligados aos campos da classe Data), que se quer filtrar
		//N é a quantidade de campos que se vai filtrar
		//infoType é o campo (da classe Data) que irá ser gravado no txt (opcional, grava o titulo caso não informado)
		void Filter( string (Data::*comparatorTypes[])(), string comparators[], int N, string (Data::*infoType)() = &Data::getTitle  ){
			//A filtragem ocorre levando em conta pares ordenados de comparatorTypes e comparators
			//logo se for passado &Data::getDirector e "Cla", serão dados elementos da arvore que sejam compostos por diretores com nomes que começam com Cla

			Data * cResults = new Data [arv.qtNodes()]; //Cria um vetor para guardar os Data dos elementos não filtrados
			
			int current = 0; //Começa com 0 elementos
			FilterAux(arv.getRoot(), N, &current, cResults, comparatorTypes, comparators); //Chama o método auxiliar para percorrer em ordem filtrando os elementos

			string operationName = "Filter.txt"; //Coloca o nome da operação como nome do arquivo
			WriteToFile(N, operationName, infoType, cResults);	//Chama o método de gravação dos dados
		}
		
		//Listar os elementos de begin at� end, na ordem de grandeza da arvore, levando em conta o pulo do step
		void Fragment( int begin = 0, int end = -1, int step = 1, string (Data::*infoType)() = &Data::getTitle ){
			//Tendo que os parametros são opcionais
			//Checa se os passados são validos
			if (begin > arv.qtNodes() || begin < 0){
				begin = 0;
			}

			if (end < begin || end > arv.qtNodes()){
				end = arv.qtNodes();
			}
			
			int N = 1; //Index referente ao elemento atual (da arvore), tido que tal os cita em ordem de grandeza
			if (step != 1){ //não precisa setar para operação com módulo, caso o step seja 1
				//Do contrário incrementa o elemento inicial até que a divisão (do elemento atual buscado), pelo step indique resto 1
				while ((begin + N) % step != 1){
					N++;
				}
			}

			
			Data * cResults = new Data [ (( end - begin ) / step) + 1 ]; //Aloca memória dinâmicamente no tamanho referente a quantidade de elementos buscados

			FragmentAux(begin, end, step, arv.getRoot(), &N, cResults); //Chama o método auxiliar para colocar os elementos em cResults
			
			string operationName = "Fragment.txt";
			WriteToFile(N, operationName, infoType, cResults); //Chama o método para gravação dos dados	
		}
		
		//Listar elementos baseado no metodo comparador passado em string (Data::*comparatorType)()
		void List( string (Data::*comparatorType)(), string comparator = "", string (Data::*infoType)() = &Data::getTitle ){

			int N = 0; //N refente a quantidade de comparadores achados na arvore (diretores achados, anos achados)
			
			string * cStrings = new string[arv.qtNodes()]; //Aloca memória dinâmicamente para guardar os comparadores já achados
			vector< vector<Data> > cResults (arv.qtNodes()); //Cria uma matriz para guardar os elementos que possuem tais comparadores
															 //logo para um comparador em [i] de cStrings, guarda em [i][n] de cResults o elemento que possui tal comparador
			
			for (int i = 0; i < arv.qtNodes(); i++){
				cResults[i].resize(1); //Inicializa cada vetor de elementos dentro da matriz como tendo tamanho 1, para poupar memória
			}
				
			if (comparator == ""){ //Se a string opcional de filtro for vazia, por tal indiciando que não se deseja filtrar os elementos
				*(cStrings) = "None"; //Coloca um campo None nos comparadores, já que elementos com comparadores inexistentes ou não informados, não serão filtrados
				N++; //incrementa o ocntador de comparadores achados
			}

			
			ListAux(arv.getRoot(), cStrings, &cResults, comparatorType, &N, comparator); //Chama o método auxiliar para preencher cStrings e cResults, 
																						//listando elementos de mesmo comparador no ato de percorrer 
																						//a arvore em ordem de grandeza
			
			cResults.resize(N); //No final da execução do método auxiliar, retira espaços inutilizados para comparadores, usando resize no valor do contador N
				
			string operationName = "List.txt";
			WriteToFile(N, operationName, infoType, comparatorType, cResults); //Chama o método de escrita para guardar os dados obtidos
			
		}	
		//Conta elementos de um mesmo comparador, para todos os comparadores e não filtrados pela string comparator
		void Count( string (Data::*comparatorType)(), string comparator = "" ){
			
			//Mesma metodologia do método acima
			int N = 0;
			
			string * cStrings = new string[arv.qtNodes()];
			int * cResults = new int [arv.qtNodes()]; //Porém inicializa um Vetor com as contagens para cada comparador
				
			if (comparator == ""){
				*(cStrings) = "None";
				*(cResults) = 0; //Coloca zero para o vetor de comparadores não existente/informado
				N++;	
			}

			//Chama o método auxiliar de contagem, para preencher cStrings e cResults
			CountAux(arv.getRoot(), cStrings, cResults, comparatorType, &N, comparator);
	
			string operationName = "Count.txt";
			//Chama o método de gravação, para guardar os dados obtidos em um txt
			WriteToFile(N, operationName, comparatorType, cResults, cStrings);
			
		}
};
