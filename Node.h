#include "Data.h"

class Node{

private:
	Node *left, *right;
	Data values;


public:
	//Setters
	Node(Data data)
	{
		this->values = data;
		left = NULL;
		right = NULL;
	}
    void setLeft(Node *node)
	{
		left = node;
	}
	void setRight(Node *node)
	{
		right = node;
	}
	
	//Getters

	Data getData(){
		return values;
	}
	Node* getLeft(){
		return left; 
	}
	Node* getRight(){
		return right;
	}
};