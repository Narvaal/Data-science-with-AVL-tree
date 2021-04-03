#include "Data.h"
#include<fstream>
using namespace std;

int main()
{
	//ifstream myFile;
	ifstream myFile("netflix_titles.csv");
	
	//while(myFile.good()){
		//string line;
		//getline(myFile,line, ',');
		//cout << line << endl;
	//}
    
    for(int i = 0; i < 10; i++){
	    string line;
		getline(myFile,line, ',');
		cout << line << endl;		
	}

    /*
    	Por enquanto so o básico,
    	o main é so para abrir o
    	arquivo e exibir as infromações.
    	
		O unico  problema é  que parece  
		que so é  possivel ler uma célula 
		por vez.Então se executarmos o 
		código  acima  ele vai exíbir 
		o nome de cada coluna. 
		
		Para exibir os dados da tabela 
		ele tem que ser executado mais 
		vezes até ele descer para a
		próxima linha.  
    */  
}