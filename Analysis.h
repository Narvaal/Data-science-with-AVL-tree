#include<fstream>
#include<iostream>
#include "Read.h"

#include <vector>

using namespace std;

class Analysis{
	
	private:
		
		Tree arv;
		
	public:
		
		Analysis(Tree a){
			arv = a;
		}
		
		/*
		Tree ReOrder(Node* node, Tree* b = NULL){
			
			Tree temp;
			
			if (node == arv.getRoot()){
				temp = new Tree();
			}
			
		}
		*/		
			
		void List( string (Data::*comparatorType)() /*Colocar a informação desejada dos encontrados (nome,id,etc)*/ ){

			int N = 0;
			
			string * cStrings = new string[arv.qtNodes()];
			vector< vector<Data> > cResults (arv.qtNodes());
			
			for (int i = 0; i < arv.qtNodes(); i++){
				cResults[i].resize(1);
			}

			*(cStrings) = "None";
			N++;
			
			cout<<"\nProcessamento"<<endl;
			ListAux(arv.getRoot(), cStrings, &cResults, comparatorType, &N);
			cout<<"\nFim do Processamento\n"<<endl;
			
			for (int j = 0; j < N; j++){
				
				cout<<*(cStrings+j)<<endl;

				for (int k = 0; k < (cResults.at(j)).size(); k++){
					
					cout<<"   -   ";
					if ( !( ((cResults[j][k]).*comparatorType)().empty() ) ){
						cout<<(cResults[j][k]).getId()<<endl;	
					}
					
					
				}
				
				cout<<"\n\n"<<endl;
			}
			
		}
		
		void ListAux( 
				Node* node, 
				string * cStrings,
				vector< vector<Data> > * cResults,
				string (Data::*comparatorType)(), 
				int * N
				){
			
			if (node != NULL){
				
				ListAux(node -> getLeft(), cStrings, cResults, comparatorType, N);
				
				bool foundType = false;
				
				for (int i = 0; i < *N ; i++){
					if( *(cStrings+i) == (node -> getData().*comparatorType)() && !(*(cStrings+i)).empty() && !(node -> getData().*comparatorType)().empty()){
						
						foundType = true;										
						(cResults -> at(i)).push_back(node -> getData());
						break;
					}
					
					else if (*(cStrings+i) == "None" && (node -> getData().*comparatorType)().empty()){
						
						foundType = true;
						(cResults -> at(i)).push_back(node -> getData());
						break;
					}
					
				}
				
				if (!foundType){					
					*(cStrings + *N) = (node -> getData().*comparatorType)();
					(cResults -> at(*N))[0] = node -> getData();
					*N = *N + 1;
				}
				
				ListAux(node -> getRight(),  cStrings, cResults, comparatorType, N);	
							
			}
		}
		
		/*
		Data * MoreSpace(int n, int M, Data * d){
			Data * temp = new Data[M];
			for (int i = 0; i < n; i++){
				temp[i] = d[i];
			}
			delete[](d);
			return temp;
		}
		
		void List( std::string (Data::*comparatorType)() ){

			int N = 0;
			int M = 5;
			std::string * cStrings = new std::string[arv.qtNodes()];
			
			Data ** cResults = new Data * [arv.qtNodes()];
			for (int i = 0; i < arv.qtNodes(); i++){
				cResults[i] = new Data [M];
			}

			*(cStrings) = "None";
			N++;
					
			ListAux(arv.getRoot(), cStrings, cResults, comparatorType, &N, &M);
			cout<<"Fim";
		}
		
		void ListAux( 
				Node* node, 
				std::string * cStrings,
				Data * cResults[],
				std::string (Data::*comparatorType)(), 
				int * N,
				int * M
				){
			
			if (node != NULL){
				
				ListAux(node -> getLeft(), cStrings, cResults, comparatorType, N, M);
				
				bool foundType = false;
				
				for (int i = 0; i < *N ; i++){
					if( *(cStrings+i) == (node -> getData().*comparatorType)() && !(*(cStrings+i)).empty() && !(node -> getData().*comparatorType)().empty()){
						foundType = true;
						int cont = 0;
											
						while ((*(*(cResults + i) + cont)).getTitle().empty() == false){
							cont++;
						}
						
						if (cont > *M){
							*(cResults + i) =  MoreSpace(*M, cont, *(cResults + i));
							*M = *M + 1;
						}
						
						*( *(cResults + i) + cont) = node -> getData();
						break;
					}
					
					else if (*(cStrings+i) == "None" && (node -> getData().*comparatorType)().empty()){
						foundType = true;
						int cont = 0;
						while ((*(*(cResults + i) + cont)).getTitle().empty() == false){
							cont++;
						}
						
						if (cont > *M){
							*(cResults + i) =  MoreSpace(*M, cont, *(cResults + i));
							*M = *M + 1;
						}
						
						*( *(cResults + i) + cont) = node -> getData();
						break;
					}
					
				}
				
				if (!foundType){
					cout<<node->getData().getId();
					cout<<(node -> getData().*comparatorType)()<<endl;
					
					*(cStrings + *N) = (node -> getData().*comparatorType)();
					*(*(cResults + *N)+0) = node -> getData();
					*N = *N + 1;
				}
				
				ListAux(node -> getRight(),  cStrings, cResults, comparatorType, N, M);	
							
			}
		}
		*/
};
