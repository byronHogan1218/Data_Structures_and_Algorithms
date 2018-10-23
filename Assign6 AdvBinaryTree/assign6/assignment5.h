/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    03/06/18
Assignment:  Assignment5


Purpose:     Creates a class for a Binary tree


***************************************************************************************************/
#ifndef ASSIGNMENT5
#define ASSIGNMENT5
#include<iostream>

class binTree;
class BST;

//Class declaration for a Node Class
class Node {
friend class binTree;
friend class BST;
public:
        int data;
        Node* left;
        Node* right;
        Node(int);
        Node(){data = 0; left = nullptr; right = nullptr;};//default constructor
};


//Class declaration for a Binary Tree Class
class binTree {
    public:
        binTree();
        virtual void insert( int );
        int height() const;
        unsigned size() const;
        void inorder( void(*)(int) );
        void preorder( void(*)(int) );
        void postorder( void(*)(int) );

    protected:
        Node* root;
    private:
        void insert( Node*&, int );
        int height( Node* ) const;
        unsigned size( Node* ) const;
	void inorder( Node*, void(*)(int) );
	void preorder( Node*, void(*)(int) );
	void postorder( Node*, void(*)(int) );
};

#endif
