#include "Analysis.h"

int main(){
	
  Tree arv = Read("netflix_titles.csv");
  //cout<<arv.getRoot()->getData().getId()<<endl;
  Analysis a = Analysis(arv);

  
  a.List(&Data::getDirector);
  //a.List(&Data::getRating);
  //a.List(&Data::getReleaseYear);
  //a.List(&Data::getTitle);
  //a.List(&Data::getCast);
  //a.List(&Data::getType);
  
  return 0;
}
