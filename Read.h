#include<fstream>
#include<iostream>
#include "Tree.h"
using namespace std;



Tree Read(std::string file)
{
	ifstream myFile(file.c_str());
	
    string tipos;
    getline(myFile, tipos, myFile.widen('\n'));
	
	Tree csvArv;
	
    while(myFile.good()){
    	
    	/* método antigo
    	string data_Linha [12];
    	for (int j = 0; j < sizeof(data_Linha)/sizeof(data_Linha[0]); j++){
    		string data_Atual;
    		
    		if (j == (sizeof(data_Linha)/sizeof(data_Linha[0])) - 1 ){
    			getline(myFile, data_Atual, myFile.widen('\n'));
			}
			else{
				getline(myFile, data_Atual, ',');
				if (data_Atual[0] == char(34)){
					string nulo;
					string temp;
					getline(myFile, temp, char(34));    			
	    			data_Atual += temp;
				}
			}

			data_Linha[j] = data_Atual;
		}
		*/	
		
		string data_Linha [12];
		string data_Atual;
		getline(myFile, data_Atual, myFile.widen('\n'));
		int index = 0;
		bool emAspas = false;
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
		
		Data data;
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
		
		csvArv.insert(data);
	}	
	return csvArv;
}
