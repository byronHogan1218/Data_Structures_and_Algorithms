/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    03/23/18
Assignment:  Assignment6


Purpose:     Defines the methods used in the class for a binary tree


***************************************************************************************************/
#include <iostream>
#include "assignment5.h"
#include "assignment6.h"
using namespace std;


/****************************************************************************************************/
//                             Public Binary Tree Methods Follow
/****************************************************************************************************/

//Each of the following public methods just call the provate versions of themselves
//See the private functions to see docuementation on what they doa n how they work

void BST::insert(int data){
	insert(root, data);
}
bool BST::search(int data){
	return search(root, data);
}
bool BST::remove(int data){
	return remove(root, data);
}
int BST::sumLeftLeaves(){
	int sum = 0;
	sumLeftLeaves(root->left,sum);
	return sum;
}

/****************************************************************************************************/
//                             Private Binary Tree Methods Follow
/****************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method overrides the insert method in "assignmetn5.h" It is use to insert a node into the BST
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void BST::insert(Node *&n, int val){
        if (n == NULL){//Determines if the visted spot has a Node in it
                n = new Node;//Creates a Node in the spot being visited
                n->data = val;//Assigns the Node created with the data being passed in
        }
	else if (val < n->data){//Determines if it should be inserted on the left or right
		insert(n->left ,val);//Going left
	}
	else{
		insert(n->right,val);//Going right
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method overrides the insert method in "assignmetn5.h" It is use to insert a node into the BST
//      Returns:A boolean, true means the node was found, false means it wasn't
////////////////////////////////////////////////////////////////////////////////////////////////////
bool BST::search(Node *&n, int target){
	if (n != NULL){
		if(n->data == target){//Found the target Node
			return true;
		}
		if(target > n->data){//Determines if the Node will be to the right or left of the current node
			return search(n->right,target);//Going right
		}
		else{
			return search(n->left,target);//Going left
		}
	}
	else{//Did not find the Node
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method removes a node from the BST
//      Returns:A boolean, true means the node was found and removed, false means it wasn't
////////////////////////////////////////////////////////////////////////////////////////////////////
bool BST::remove(Node *&n, int target){
	if ( n == NULL )//Immediately return if tree is empty
		return false;
	else if ( n->data > target)//Navigate through tree to find node to delete,target is smaller
		remove(n->left, target);//Going left
        else if ( n->data < target)//Navigate through tree to find node to delete,target is bigger
                remove(n->right, target);//Going right
	else if (target == n->data){//Found the node, proceed to removing it
		Node *temp = n;
		if (n->left != NULL && n->right != NULL ){//n has two children
			int holder = 0;
			Node *pred = n;
			if ( pred->left != NULL){//Find the immediate predecessor
				pred = pred->left;
				while (pred->right != NULL)
					pred = pred->right;
			}
			holder = pred->data;
			n->data = holder;
			remove(n->left,holder);
		}
		else if (n->left == NULL && n->right == NULL ){//n is a leaf
			delete n;
			n = NULL;
			return true;
		}
		else if(n->left != NULL || n->right != NULL ){//n has one child
			if (n->left != NULL)//child on the left
				n = n->left;
			else//child on the right
				n = n->right;
			delete temp;
			return true;
		}
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method overrides the insert method in "assignmetn5.h" It is use to insert a node into the BST
//      Returns:An interger used fro recursively summing up the tree
//	Prarameters: n is the node to start from, sum is a reference variable used to keep track of the total
////////////////////////////////////////////////////////////////////////////////////////////////////

int BST::sumLeftLeaves(Node *&n, int &sum){
	if (n != NULL){//Navigate through tree adding each node together
		sum += sumLeftLeaves(n->left, sum);
		sum += sumLeftLeaves(n->right, sum);
		return n->data;
	}
	else{//reached a leaf
		return 0;
	}
}

