/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    03/06/18
Assignment:  Assignment5


Purpose:     Defines the methods used in the class for a binary tree


***************************************************************************************************/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "assignment5.h"
using namespace std;

const int MAX_SIZE = 40;
const int MAX_COUNT = 40;
const int WIDTH = 5;
const int ROW_SIZE = 8;

////////////////////////////////////////////////////////////////////////////////////////////////////
//This is a constructor for a Node being passed an integer
////////////////////////////////////////////////////////////////////////////////////////////////////
Node:: Node(int data){
        Node* n = new Node;
        n->data = data;
        n->left = nullptr;
        n->right = nullptr;
};

/****************************************************************************************************/
//                             Public Binary Tree Methods Follow
/****************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////
//This is the default constructor
////////////////////////////////////////////////////////////////////////////////////////////////////
binTree::binTree(){
	root = nullptr;
}

///////////////////////////////////////////////////////////////////////////////$
//This method is the public version that calls the corresponding private version
//      Returns:An integer that is the height of the binary tree
///////////////////////////////////////////////////////////////////////////////$
void binTree::insert(int val) {
        insert(root, val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the public version that calls the corresponding private version
//      Returns:An integer that is the height of the binary tree
////////////////////////////////////////////////////////////////////////////////////////////////////
int binTree::height() const{
        return height(root);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the public version that calls the corresponding private version
//      Returns:An unsigned integer that is the Size of the binary tree
////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned binTree::size() const{
        return size(root);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the public version that calls the corresponding private version
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::inorder( void(*funcToCall)(int data) ){
        inorder(root, funcToCall);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the public version that calls the corresponding private version 
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::preorder( void(*funcToCall)(int data) ){
        preorder(root, funcToCall);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is the public version that calls the corresponding private version 
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void binTree::postorder( void(*funcToCall)(int data) ){
        postorder(root, funcToCall);
}

/****************************************************************************************************/
//                              Private Binary Tree Methods Follow
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


int mcount = 0;
int rcount = 0;

void display(int d) {
    if ( mcount < MAX_COUNT ) {
        cout << setw(WIDTH) << d;
        mcount++;
        rcount++;
        if ( rcount == ROW_SIZE ) {
            cout << endl;
            rcount = 0;
        }
    }
}
/*
//#define BINTREE_MAIN
//#ifdef BINTREE_MAIN
int main() {
    vector<int> v(MAX_SIZE);
    for (int i=1; i<MAX_SIZE; i++)
        v[i] = i;
    random_shuffle( v.begin(), v.end() );

    binTree bt;
    vector<int>::iterator it;
    for (it=v.begin(); it!=v.end(); it++)
        bt.insert( *it );

    cout << "Height: " << bt.height() << endl;
    cout << "Size: " << bt.size() << endl;
    cout << "In order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.inorder( display );
    cout << "\n\nPre order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.preorder( display );
    cout << "\n\nPost order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.postorder( display );

    cout << endl;
    return 0;
}

//#endif
*/
