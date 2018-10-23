/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    03/06/18
Assignment:  Assignment5


Purpose:     Creates a class for a Binary tree and defines the methods used in the class for a binary tree


***************************************************************************************************/
#ifndef ASSIGNMENT5
#define ASSIGNMENT5
#include<iostream>

class binTree;
class BST;

//Class declaration for a Node Class
class Node {
friend class binTree;
public:
        int data;
        Node* left;
        Node* right;
        Node(int);
        Node(){data = 0; left = nullptr; right = nullptr;};//default constructor
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//This is a constructor for a Node being passed an integer
////////////////////////////////////////////////////////////////////////////////////////////////////
Node:: Node(int data){
        Node* n = new Node;
        n->data = data;
        n->left = nullptr;
        n->right = nullptr;
};

//Class declaration for a Binary Tree Class
class binTree {
    public:
        binTree(){root = NULL;};//default constructor
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

/****************************************************************************************************/
//                                   Public Methods Follow
/****************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the publice version that calls the corresponding private version
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::insert( int data){
	insert(root, data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the publice version that calls the corresponding private version
//      Returns:An integer that is the height of the binary tree
////////////////////////////////////////////////////////////////////////////////////////////////////
int binTree::height() const{
	return height(root);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the publice version that calls the corresponding private version
//      Returns:An unsigned integer that is the Size of the binary tree
////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned binTree::size() const{
	return size(root);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the publice version that calls the corresponding private version
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::inorder( void(*funcToCall)(int data) ){
	inorder(root, funcToCall);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the publice version that calls the corresponding private version 
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::preorder( void(*funcToCall)(int data) ){
	preorder(root, funcToCall);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the publice version that calls the corresponding private version 
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::postorder( void(*funcToCall)(int data) ){
	postorder(root, funcToCall);
}
/****************************************************************************************************/
//                                     Private Methods Follow
/****************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method inserts a node into the tree
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::insert( Node*& n, int x){
        if (n == NULL){//Determines if the visted spot has a Node in it
                n = new Node;//Creates a Node in the spot being visited
		n->data = x;//Assigns the Node created with the data being passed in
	}
        else if (size(n->left) <=  size(n->right)){//Determines what side of the binary tree to insert on
                insert(n-> left, x);
	}
        else{
                insert (n->right,x);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method finds the height of the binary tree
//      Returns:An integer which is the height if the tree
////////////////////////////////////////////////////////////////////////////////////////////////////
int binTree::height( Node* n) const{
	if (n == NULL)//Determines if the tree is empty
		return -1;
	else{       //Explore each side of the tree to see which extends further down
		int lHeight = height(n-> left);
		int rHeight = height(n-> right);
		if(lHeight > rHeight)//Determines which side of the tree has more height
			return(lHeight +1);
		else
			return(rHeight +1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method finds the size of the binary tree
//      Returns:An unsigned integer that is the size of the binary tree
////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned binTree::size( Node* n) const{
	if (n == NULL)//Determines if the tree is empty
		return 0;
	else        //Explore each node in the tree to determine the size
		return(size(n->left) + 1 + size(n->right));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method outputs the binary tree in an inorder format (Left, Node, Right)
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::inorder( Node* n, void(*p)(int) ){
	if (n != NULL){//recursively call until the node is pointing at NULL
		inorder(n->left,p);
		p(n->data);
		inorder(n->right,p);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method outputs the binary tree in an preorder format  (Node, Left, Right)
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::preorder( Node* n, void(*p)(int) ){
	if ( n != NULL){//recursively call until the node is pointing at NULL
                p(n->data);
		preorder(n->left,p);
		preorder(n->right,p);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method outputs the binary tree in an postorder format (Left, Right, Node)
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::postorder( Node* n, void(*p)(int) ){
        if (n != NULL){//recursively call until the node is pointing at NULL
                postorder(n->left,p);
		postorder(n->right,p);
                p(n->data);
        }

}

#endif
