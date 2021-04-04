#include "Read.h"

int main(){
	
  Tree arv = Read("netflix_titles.csv");
  cout<<arv.getRoot()->getData().getId();
}
