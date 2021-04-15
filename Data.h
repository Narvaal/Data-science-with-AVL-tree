#include <iostream>
#include <string>

/*
   Classe dos dados, serve para armazenar cada linha da tabela de um forma ordenada. 
   Ou seja, cada atributo da classe representa uma coluna da tabela e vice-versa.
   
   Depois nos temos os getters e setters da classe para podermos trabalhar com a classe.
*/

#include <stdlib.h> //pra usar o atoi()

/*
    O arquivo data  serve para armazenar os valores da tabela em uma classe.
    Nós criamos o arquivo data para ter fácil  acesso ao atributos de uma linha.
    Ou seja com a classe data temos todos os elementos de uma linha armazenadas
    em um só objeto.
    
    Isso serve para quando inserirmos na classe árvore seja fácil transitar entre
    os elementos de uma linha.
    
    A classe data possui um atributo para cada coluna.Que  são:  Id, Titulo, País,  etc.

*/

class Data
{

    // Atributos da classe que são iguais as colunas da tabela
private:
    int id;
    std::string type;
    std::string title;
    std::string director;
    std::string cast;
    std::string country;
    std::string date_added;
    std::string release_year;
    std::string rating;
    std::string duration;
    std::string listed_in;
    std::string description;

public:
    // Construtor da classe data, não precisamos definir
    //os valores para nulo pois todos serão inseridos por uma função.

    Data()
    {
    }

    //Setters

    void setId(std::string i)
    {                  // converte  texto para inteiro pois usaremos inteiros para ordenar a arvore.
        i.erase(0, 1); //exclui o s
        int intI;
        intI = atoi(i.c_str());

        id = intI;
    }

    //Abaixos temos todas as entradas do classe Data
    void setType(std::string t)
    {
        type = t;
    }
    void setTitle(std::string t)
    {
        title = t;
    }
    void setDirector(std::string d)
    {
        director = d;
    }
    void setCast(std::string c)
    {
        cast = c;
    }
    void setCountry(std::string c)
    {
        country = c;
    }
    void setDateAdded(std::string a)
    {
        date_added = a;
    }
    void setReleaseYear(std::string r)
    {
        release_year = r;
    }
    void setRating(std::string r)
    {
        rating = r;
    }
    void setDuration(std::string d)
    {
        duration = d;
    }

    void setListedIn(std::string l)
    {
        listed_in = l;
    }
    void setDescription(std::string d)
    {
        description = d;
    }

    //Getters

    //Abaixo temos todas as saidas da classe Data
    int getId()
    {
        return id;
    }
    std::string getType()
    {
        return type;
    }
    std::string getTitle()
    {
        return title;
    }
    std::string getDirector()
    {
        return director;
    }
    std::string getCast()
    {
        return cast;
    }
    std::string getCountry()
    {
        return country;
    }
    std::string getDateAdded()
    {
        return date_added;
    }
    std::string getReleaseYear()
    {
        return release_year;
    }
    std::string getRating()
    {
        return rating;
    }
    std::string getDuration()
    {
        return duration;
    }
    std::string getListedIn()
    {

        return listed_in;
    }
    std::string getDescription()
    {
        return description;
    }
};
