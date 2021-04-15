#include "Analysis.h"

int main()
{

  Tree arv = Read("netflix_titles.csv"); //Criando arvore utilizando a funcao Read()
  Analysis a = Analysis(arv);            //Criando instância da clase de analise

  /*
  Alguns exemplos de chamadas:
  
  a.Count(&Data::getDirector);
  a.List(&Data::getDirector);
  a.Fragment(0, 1000, 4);

  //Funcao filter:
  string (Data::*cT[])() = {&Data::getDirector, &Data::getTitle};
  string c[] = {"Aditya Kripalani", "Tikli and Laxmi Bomb"};
  a.Filter( cT, c, 2);
  */

  //Funcoes para tratamento e exportacao dos dados:
  a.Count(&Data::getType);     //Contagem de títulos por tipo
  a.Count(&Data::getCountry);  //Contagem  títulos por países
  a.Count(&Data::getRating);   //Contagem de títulos por rating
  a.Count(&Data::getDirector); //Contagem de títulos por diretores

  return 0;
}