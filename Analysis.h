#include<fstream>
#include<iostream>
#include "Read.h"

#include <vector>

using namespace std;

bool Compare(string s_1, string s_2){
	bool equal = true;
	for (int i = 0; i < s_1.length(); i++){
		if (s_1[i] != s_2[i]){
			equal = false;
		}
	}
	return equal;
}

class Analysis{
	
	private:
		
		Tree arv;
		
		void FilterAux(
					Node * node,
					int N,
					int * current,
					Data * cResults,
					string (Data::*comparatorTypes[])(),
					string * comparators
					){
			
			if (node != NULL){
				
				FilterAux(node -> getLeft(), N, current, cResults, comparatorTypes, comparators);
				
				bool filtered = false;
				cout<<"2"<<endl;
				for (int i = 0; i < N; i++){
					cout<<comparators[i]<<endl;
					cout<<(node->getData().*comparatorTypes[i])()<<endl;
					if ( !Compare( comparators[i], (node->getData().*comparatorTypes[i])() ) ){
						cout<<"3"<<endl;
						filtered = true;
					}

				}
				
				if (!filtered){
					cout<<"4"<<endl;
					*(cResults + *current) = node->getData();
					*current = *current + 1;
				}
				
				FilterAux(node -> getRight(), N, current, cResults, comparatorTypes, comparators);
				
			}

		}
		
		void FragmentAux(
						int b, 
						int e, 
						int s, 
						Node * node, 
						int * current,
						//vector <Data> * cResults 
						Data * cResults 
						){
			
			if (node != NULL){
				
				FragmentAux(b, e, s, node->getLeft(), current, cResults);
				
				if ( *current >= b && *current <= e && (*current % s) == 0 ){
					
					//cResults->push_back(node->getData());
					*(cResults + ( (*current - b) / s) ) = node->getData();
					
				}
				
				*current = *current + 1;
				
				FragmentAux(b, e, s, node->getRight(), current, cResults);
			}	
		}
		
		void ListAux( 
				Node* node, 
				string * cStrings,
				vector< vector<Data> > * cResults,
				string (Data::*comparatorType)(), 
				int * N,
				string comparator
				){
			
			if (node != NULL){
				
				ListAux(node -> getLeft(), cStrings, cResults, comparatorType, N, comparator);
				
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
				
				if (!foundType && Compare( comparator, (node -> getData().*comparatorType)() ) ){					
					*(cStrings + *N) = (node -> getData().*comparatorType)();
					(cResults -> at(*N))[0] = node -> getData();
					*N = *N + 1;
				}
				
				ListAux(node -> getRight(),  cStrings, cResults, comparatorType, N, comparator);	
							
			}
		}
		
	public:
		
		Analysis(Tree a){
			arv = a;
		}
		
		Data * Filter( string (Data::*comparatorTypes[])(), string comparators[]  ){
			
			int N = 0;
			while (  comparatorTypes[N] != NULL  ){
				
				//if (comparators[N] == ""){
					
				//}
				
				N++;
			}
			
			Data * cResults = new Data [arv.qtNodes()];
			
			int current = 0;
			cout<<"1"<<endl;
			FilterAux(arv.getRoot(), N, &current, cResults, comparatorTypes, comparators);
			cout<<"4"<<endl;
			///*
			for (int i = 0; i < current; i++){
				cout<< cResults[i].getId()<<endl;
			}
			//*/
			
			return cResults;
			
		}
		
		//Listar os elementos de begin até end, na ordem de grandeza da arvore, levando em conta o pulo do step
		/*vector <Data>*/ Data * Fragment(int begin = 0, int end = -1, int step = 1){

			if (begin > arv.qtNodes() || begin < 0){
				begin = 0;
			}

			if (end < begin || end > arv.qtNodes()){
				end = arv.qtNodes();
			}
			
			int N = 1;
			if (step != 1){
				while ((begin + N) % step != 1){
					N++;
				}
			}

			
			/*vector <Data>*/ Data * cResults = new Data [ (( end - begin ) / step) + 1 ];

			FragmentAux(begin, end, step, arv.getRoot(), &N, /*&cResults);*/ cResults);
			
			
			for (int i = 0; i < ((end - begin) / step) + 1; i++){
				cout<< cResults[i].getId()<<endl;
			}
			
			
			return cResults;
			
		}
		
		//Listar elementos baseado no metodo comparador passado em string (Data::*comparatorType)()
		vector< vector<Data> > List( string (Data::*comparatorType)(), string comparator = "" ){

			int N = 0;
			
			string * cStrings = new string[arv.qtNodes()];
			vector< vector<Data> > cResults (arv.qtNodes());
			
			for (int i = 0; i < arv.qtNodes(); i++){
				cResults[i].resize(1);
			}
				
			if (comparator == ""){
				*(cStrings) = "None";
				N++;	
			}

			
			ListAux(arv.getRoot(), cStrings, &cResults, comparatorType, &N, comparator);
			
			cResults.resize(N);
			
		
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
			
			
			return cResults;
			
		}
		
		//***********************************************************************************************************
};
