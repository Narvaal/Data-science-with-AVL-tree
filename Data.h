#include<iostream>
#include<string>

#include <stdlib.h> //pra usar o atoi()

class Data{
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
        
        //N�o sei c tinha algum motivo pra n colocar esses 2, mas tava faltando
        std::string listed_in;
        std::string description;
        
    public:
    	
    	Data(){
    		
		}
    	    
        //Setters 

        void setId(std::string i){
        	i.erase(0,1); //exclui o s
        	int intI;
        	intI = atoi(i.c_str()); //Aparentemente converte de str pra int
            id = intI;
        }
        void setType(std::string t){
            type = t;
        }
        void setTitle(std::string t){
            title = t;
        }
        void setDirector(std::string d){
            director = d;
        }
        void setCast(std::string c){
            cast = c;
        }
        void setCountry(std::string c){
            country = c;
        }
        void setDateAdded(std::string a){
            date_added = a;
        }
        void setReleaseYear(std::string r){
            release_year = r;
        }
        void setRating(std::string r){
            rating = r;
        }
        void setDuration(std::string d){
            duration = d;
        }
		
		//N�o sei c tinha algum motivo pra n colocar esses 2, mas tava faltando
		void setListedIn(std::string l){
			listed_in = l;
		}
		void setDescription(std::string d){
			description = d;
		}
		
        //Getters  

        int getId(){
            return id;
        }
        std::string getType(){
            return type;
        }
        std::string getTitle(){
            return title;
        }
        std::string getDirector(){
            return director;
        }
        std::string getCast(){
            return cast;
        }
        std::string getCountry(){
            return country;
        }
        std::string getDateAdded(){
            return date_added;
        }
        std::string getReleaseYear(){
            return release_year;
        }
        std::string getRating(){
            return  rating;
        }
        std::string getDuration(){
            return duration;
        }
        
        //N�o sei c tinha algum motivo pra n colocar esses 2, mas tava faltando
        std::string getListedIn(){
        	return listed_in;
		}
		std::string getDescription(){
			return description;
		}
};