#include<fstream>
#include<iostream>
#include "Tree.h"
using namespace std;

/*
	Função para fazer a leitura do .csv. Basicamente estámos 
	utilizando o a blioteca fstream e iostream para lermos o arquivo
	.csv.E Tratamos os dados e passamos para nossa classe de dados Data
	
	Simplificadamente o arquivo Read.h percorre a tabela e coloca o valor de cada
	coluno em um  atributo da classe de dados Data

*/

Tree Read(std::string file)
{
	
    ifstream myFile(file.c_str()); //abrindo o arquivo
	
    string tipos;     
    getline(myFile, tipos, myFile.widen('\n'));  
	
    Tree csvArv; // criando uma classe arvore
	
    while(myFile.good()){ //Enquanto o arquivo não acabar 
    		
		string data_Linha [12]; // array de string 
		string data_Atual; // dado atual 
		getline(myFile, data_Atual, myFile.widen('\n')); // pegando o valor do dado  atual e passando para data 
		int index = 0;
		bool emAspas = false;
	    
	    	// Operação para  saber so existem algum tipo de erro no arquivo, tais como datas com " ou ' 
	    
		for (int j = 0; j < data_Atual.length(); j++){
			if (data_Atual[j] == char(34) ){
				emAspas = !emAspas;
			}
			
			else if (data_Atual[j] == char(44) && !emAspas){
				index++;
				continue;
			}
			
			data_Linha[index] += data_Atual[j];
		}
	
	 //Apos isso é passado os valores do vetor para nossa classe de dados Data.
	    
	Data data; // ciração da classe Data 
	    
	//abaixo usamos os setters para  definir os  valores para nossa classe de dados.      
	data.setId(data_Linha[0]);
        data.setType(data_Linha[1]);
        data.setTitle(data_Linha[2]);
        data.setDirector(data_Linha[3]);
        data.setCast(data_Linha[4]);
        data.setCountry(data_Linha[5]);
        data.setDateAdded(data_Linha[6]);
        data.setReleaseYear(data_Linha[7]);
        data.setRating(data_Linha[8]);
        data.setDuration(data_Linha[9]);
        data.setListedIn(data_Linha[10]);
        data.setDescription(data_Linha[11]);
		
	csvArv.insert(data); //Inserindo a nossa classe Data na árvore avl 
	}	
	return csvArv;//Retorna a árvore.  
}
