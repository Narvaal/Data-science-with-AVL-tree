#include "Data.h"

class Node{

private:
	Node *left, *right;
	Data values;
	int height;


public:
	//Setters
	Node(Data data)
	{
		this->values = data;
		left = NULL;
		right = NULL;
		height = 0;
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