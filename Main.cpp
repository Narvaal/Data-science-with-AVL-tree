#include<iostream>
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

    
    
    
    
    
}

