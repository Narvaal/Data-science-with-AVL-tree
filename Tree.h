#include "Node.h"

class Tree
{
    public:
        Tree()
        {
            root = NULL;
        }
        virtual ~Tree()
        {

        }
        Node* getRoot()
        {
            return root;
        }
        bool isEmpty()
        {
            return root == NULL;
        }
        int height()
        {
            return height(root);
        }
        int qtNodes()
        {
            return qtNodes(root);
        }
        void insert (Data value)
        {
            root = insert(root,value);
        }
        void preOrder()
        {
            preOrder(root);
        }
        void posOrder()
        {
            posOrder(root);
        }
        void inOrder()
        {
            inOrder(root);
        }
        void reverseOrder()
        {
            reverseOrder(root);
        }

    private:
        Node *root;

		    int searchKey;
		
        int height(Node *node)
        {
            return node == NULL? -1:node->getHeight();
        }
        int qtNodes(Node *node)
        {
            if (node == NULL)
                return 0;
            int qtleft = qtNodes (node->getLeft());
            int qtright = qtNodes (node->getRight());
            return qtleft + qtright + 1;
        }
        Node* insert(Node* node, Data data)
        {
            if (node == NULL)
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
        void preOrder(Node *node)
        {
            if (node!=NULL)
            {
                std::cout<<node->getData().getId()<<std::endl;
                preOrder(node->getLeft());
                preOrder(node->getRight());
            }
        }
        void posOrder(Node *node)
        {
            if (node!=NULL)
            {
                posOrder(node->getLeft());
                posOrder(node->getRight());
                std::cout<<node->getData().getId()<<std::endl;
            }
        }
        void inOrder(Node *node)
        {
            if (node!=NULL)
            {
                inOrder(node->getLeft());
                std::cout<<node->getData().getId()<<std::endl;
                inOrder(node->getRight());
            }
        }
        Node* rotateLL(Node *node)
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
        void reverseOrder(Node *node)
        {
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