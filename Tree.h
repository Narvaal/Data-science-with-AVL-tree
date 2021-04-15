#include "Node.h"

/*
   	 A classe tree é onde definimos a construção da classe tree.
    	Aqui estão seus métodos e atributos.
 
	
    	A class tree é nossa estrutura de dados e possui vários métodos e atributos
   	 para organizar os dados em uma estrutura de árvore  avl.Basicamente a árvore
    	possui uma raiz que é o primeiro valor, possui 2 filhos (1 para direita, 1
    	para esquerda), e quando a raiz não é a primeira da árvore ela é chamada de
    	node. 
	A classe árvore ordena os elementos de tal maneira:

	
		3
	       /  \
	      1    5
	      
	*O elemento da esquerda é sempre menor que a raiz(nó) e o elemento da direita é sempre maior.
	
	
	A diferença entre uma árvore binária e nossa árvore é o balanceamento, uma árvore binária não 
	possui métodos para rotacionar um elemento e acabam ficando desbalanceadas.
	
	Ex: não balanceada    /     balanceada 
	
		.                       .
	       / \		       /  \
	      .   .                   .     .
	     / \                     / \   / \
	    .   .                   .   .  .  .
	   /                       /
	  .                       .
	
	
	*A árvore avl faz isso usando os métodos rotate organizando os elementos em outra ordem, linha 173
*/

class Tree
{
    public:
        Tree() //construtor da  classe tree
        {
            root = NULL;
        }
        virtual ~Tree() //descontrutor da classe tree
        {

        }
        Node* getRoot() // retorna a raiz da arvore 
        {
            return root;
        }
        bool isEmpty() // retorna null se arvore estiver vazia
        {
            return root == NULL;
        }
        int height() //retorna a altura da arvore 
        {
            return height(root);
        }
        int qtNodes()  //retorna a quantidade de nodes
        {
            return qtNodes(root);
        }
	
	//interfaces para os métodos privados
	
        void insert (Data value)  //método insert,linha 108
        {
            root = insert(root,value); 
        }
        void preOrder() //método preOrder ,linha 146
        {
            preOrder(root); 
        }
        void posOrder() //método posOrder ,linha 155
        {
            posOrder(root);
        }
        void inOrder()  //método  isOrder ,linha 164
        {
            inOrder(root);
        }
        void reverseOrder()   //método reverseOrder ,linha 201
        {
            reverseOrder(root);
        }

    private:
        Node *root;

		    int searchKey;
		
        int height(Node *node) //Retorna um inteiro com a altura da árvore 
        {
            return node == NULL? -1:node->getHeight();
        }
        int qtNodes(Node *node) //Retorna a quantidade de nos ná árvore
        {
            if (node == NULL)
                return 0;
            int qtleft = qtNodes (node->getLeft());
            int qtright = qtNodes (node->getRight());
            return qtleft + qtright + 1;
        }
        Node* insert(Node* node, Data data)	//esse método privado serve  para inserir os elementos na arvore,  
        {					//ele utiliza varias operações para ter certeza que o método sera  
            if (node == NULL)			//inserido na arvore na posição correta.
                return new Node(data);
            if (data.getId() < node->getData().getId())
            {
                    node->setLeft(insert(node->getLeft(), data));
                    if( height( node->getRight() ) - height( node->getLeft() ) == -2 )
                    {
                        if(  data.getId()< node->getLeft()->getData().getId() )
                            {
                                node = rotateLL( node );
                            }
                        else{
                                node = rotateLR( node );
                            }
                    }
            }
            else
            {
                if (data.getId() > node->getData().getId())
                    {
                            node->setRight(insert(node->getRight(),data));
                            if( height( node->getRight() ) - height( node->getLeft() ) == 2 )
                            {
                                if( data.getId() > node->getRight()->getData().getId())
                                    node = rotateRR( node );
                                else
                                    node = rotateRL( node );

                            }

                    }
            }
            node->setHeight(maximo( height(node->getLeft()), height(node->getRight()) ) + 1);

            return node;            
        }
        void preOrder(Node *node)	//Retorna todos os valores que estão armazenados na árvore em preOrder. Ou seja ele 				
        {                               //exibe na seguinte ordem: R, E, D. (raiz, filho esquerda, filho direita).
            if (node!=NULL)
            {
                std::cout<<node->getData().getId()<<std::endl;
                preOrder(node->getLeft());
                preOrder(node->getRight());
            }
        }
        void posOrder(Node *node)	//Retorna todos os valores que estão armazenados na árvore posOrder. Ou seja ele 
        {				//exibe na seguinte ordem: E, D,R. (filho esquerda, filho direita, raiz).
            if (node!=NULL)
            {
                posOrder(node->getLeft());
                posOrder(node->getRight());
                std::cout<<node->getData().getId()<<std::endl;
            }
        }
        void inOrder(Node *node)	//Retorna todos os valores que estão armazenados na árvore inOrder. Ou seja ele  
        {                               //exibe na seguinte ordem: E, R, D. (filho esquerda, raiz, filho direita).
            if (node!=NULL)
            {
                inOrder(node->getLeft());
                std::cout<<node->getData().getId()<<std::endl;
                inOrder(node->getRight());
            }
        }
        Node* rotateLL(Node *node)	//Abaixo temos todas as funçõe de rotação que servem para organizar a arvore da forma devida.  
        {
            Node *leftSubTree = node->getLeft();
            node->setLeft(leftSubTree->getRight());
            leftSubTree->setRight( node );
            node->setHeight( maximo(height(node->getLeft()), height(node->getRight())) + 1);
            leftSubTree->setHeight( maximo(height(leftSubTree->getLeft()), height(node) + 1));
            return leftSubTree;        
        }
        Node* rotateRR(Node *node)
        {
            Node *rightSubTree = node->getRight();
            node->setRight(rightSubTree->getLeft());
            rightSubTree->setLeft( node );
            node->setHeight( maximo(height(node->getLeft()), height(node->getRight())) + 1);
            rightSubTree->setHeight( maximo(height(rightSubTree->getRight()), height(node) + 1));
            return rightSubTree;
        }
        Node* rotateLR(Node *node)
        {
            node->setLeft(rotateRR(node->getLeft()));
            return rotateLL(node);
        }
        Node* rotateRL(Node *node)
        {
            node->setRight(rotateLL(node->getRight()));
            return rotateRR(node);
        }
        void reverseOrder(Node *node) 	//Retorna todos os valores armazenados em ordem reversa ou sejá do maior valor para o menor   
        {                             	//Ou sejá da base da árvore para o topo.
            if (node!=NULL)
            {
                reverseOrder(node->getRight());
                std::cout<<node->getData().getId()<<std::endl;
                reverseOrder(node->getLeft());
            }
        }
        int maximo(int lhs, int rhs)
        {
            return lhs>rhs? lhs: rhs;
        };

};
