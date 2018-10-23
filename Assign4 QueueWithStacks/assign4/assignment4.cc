/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    02/22/18
Assignment:  Assignment4


Purpose:     Provides functionality for a Queue class using STL Stacks


***************************************************************************************************/

#include<iostream>
#include"assignment4.h"
#include<string>
#include<iomanip>
#include<stack>

using std::stack;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::cerr;

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method determines if the Queue is empty
//      Returns:True if both stacks are empty,False if one of the stacks have a value in them
////////////////////////////////////////////////////////////////////////////////////////////////////
bool Queue::empty() const{
	return (s1.empty() && s2.empty());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method determines the size of the Queue by adding the sizes of the two stacks together
//      Returns:An Integer which is the size of the Queue
////////////////////////////////////////////////////////////////////////////////////////////////////
int Queue::size() const{
	return ( s1.size() + s2.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method determines the front value in the stack
//      Returns:An Integer which is the value of the front of the Queue
////////////////////////////////////////////////////////////////////////////////////////////////////
int Queue::front(){
	if(s2.empty()){//Determines if the s2 is empty
		unsigned int sizeOfs1 = s1.size();
		for(unsigned int i = 0; i < sizeOfs1; ++i){//moves all of the elemnts in s1 to s2
			s2.push(s1.top());
			s1.pop();
		}
	}
	return s2.top();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method determines the last/back value in the Queue
//      Returns:An Integer which is the last number in the Queue
////////////////////////////////////////////////////////////////////////////////////////////////////
int Queue::back(){
	return s1.top();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method adds the passed in value to the Queue at the top
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void Queue::push(const int& val){
	s1.push(val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method removes the last element of the Queue
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void Queue::pop(){
        if(s2.empty()){//Determines if s2 is empty
		unsigned int sizeOfs1 = s1.size();
                for(unsigned int i = 0; i < sizeOfs1; ++i){//moves all of the elements of s1 to s2
                        s2.push(s1.top());
                        s1.pop();
                }
        }
	s2.pop();//removes the last element in the Queue
}



int main() {
    Queue q;
    string op;
    int val = 0;

   cout << "operation -- size front end" << endl;
   cin >> op;
   while ( !cin.eof() ) {
        if ( op == "push" ) {
            cin >> val;
            q.push( val );
            cout << op << " " << val << "    -- ";
        }
        else if ( op == "pop" ) {
            q.pop();
            cout << op << "       -- ";
        }
        else {
            cerr << "Error input: " << op << endl;
            return 1;
        }
        cout << setw(3) << q.size() << setw(5) << q.front() << setw(5) << q.back() << endl;
        cin >> op;
    }

    while ( !q.empty() )
        q.pop();

    return 0;
}
