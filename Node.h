#include "Data.h"

/*
	A class node faz o papel de nó da nossa árvore avl, a classe node tem
	4 atributos, um ponteiro para o valor esquerda, um ponteiro para o valor a direita,
	um objeto tipo data, e um inteiro para a altura da árvore.
    
	O construtor do node cria um objeto tipo node com valores  
	nulos,e após isso criamos os setters e getters para a classe node.
    
	Em suma a classe  node serve para navegar na classe árvore.Logo essa
	A classe não possui outros métodos além dos métodos de acesso. 
*/

class Node
{

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
	void setHeight(int height)
	{
		this->height = height;
	}

	//Getters

	Data getData()
	{
		return values;
	}
	Node *getLeft()
	{
		return left;
	}
	Node *getRight()
	{
		return right;
	}
	int getHeight()
	{
		return height;
	}
};
