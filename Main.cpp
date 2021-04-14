#include "Analysis.h"

int main(){
	
  Tree arv = Read("netflix_titles.csv");
  //cout<<arv.getRoot()->getData().getId()<<endl;
  Analysis a = Analysis(arv);
  
  //Funfa
  //a.List(&Data::getDirector);
  //a.List(&Data::getType);
  //a.List(&Data::getRating);
  //a.List(&Data::getListedIn);
  //a.List(&Data::getCountry);
  //a.List(&Data::getDateAdded);
  //a.List(&Data::getDuration);
  //a.List(&Data::getDescription);
  //a.List(&Data::getCast);
  //a.List(&Data::getReleaseYear);
  
  //a.Fragment(0, 1000, 4);
  
  //Problema
  //a.List(&Data::getTitle); //problema
    
  string (Data::*cT[])() = {&Data::getDirector, &Data::getTitle};
  string c[] = {"Aditya Kripalani", "Tikli and Laxmi Bomb"};
  //a.Filter( cT, c, 2);
  
  return 0;
}
