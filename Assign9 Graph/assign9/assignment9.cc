/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    04/27/18
Assignment:  Assignment9


Purpose:     To create and maintain a graph


***************************************************************************************************/

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include "assignment9.h"
using namespace std;


//These are global variables
vector<bool> visited;//used to determine if a node has been visited
vector<char> pathOrder;//used to know which order the nodes are visited in
vector<char> visitedOrder;//used to determine how the graph is connected


////////////////////////////////////////////////////////////////////////////////////////////////////
//This is the constructor, which takes the name of a text file to open and read data from
////////////////////////////////////////////////////////////////////////////////////////////////////
graph::graph ( const char* filename ){
	ifstream fin;
	string line;
	list<int> tempList;
	int temp = 0;
	fin.open(filename);
	if (fin.is_open()){//Determines if the file opened correctly
		getline(fin,line);//Gets the size of the graph
		temp = line[0] - 48;//48 is the integer value to get the correct numeric value from the ASCII value
		size = temp;
		getline(fin,line);//read the extra data,aka the vertices.Will read them in the following getlines
		while(getline(fin, line)){//get the line of data next line of data until eof
			if( line.length() < 2 ){//Determines if the graph has enough data to be built
				cerr << "Not enough data"<<endl;
				break;
			}
			for (unsigned int i = 0; i < line.length()-1;++i){//Loops through the line to find white spaces
				if (isspace(line[i])){//Determines if it is a white space
					line.erase(i,1);//Deletes the white space
				}
			}
			labels.push_back(line[0]);//Add the vertex label to the vector
			tempList.clear();//flush the old data help in tempList
			for ( unsigned int i = 1; i <= line.length()-1; ++i){//loops through the rest of the line of 1 and 0's(1 is connected)
				temp = line[i] - 48;
				tempList.push_back(temp);//add the information to a temporary list
			}
			adj_list.push_back(tempList);//Adds the temporary list to the adj_list
		}
	fin.close();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method provides a way for the traverse method to traverse through the graph
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void graph :: depth_first( int v){
	visited[v] = true;
	pathOrder.push_back(labels[v]);
	list<int>::const_iterator adjacents;
	int count = 0;
	visitedOrder.push_back(labels[v]);
	for(adjacents = adj_list[v].begin(); adjacents != adj_list[v].end(); ++adjacents){//Loop through the adj_list
		if( *adjacents == 1){//Determines if the nodes are adjacent to one another
			int w = count;
			if(!visited[w]){
				depth_first(w);//recursively call on the next unvisited node
			}
		}
		++count;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method traverses through the graph and visits each node
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void graph::traverse(){
	if (visited.size() != (unsigned)size)//Makes sure that the size of the vector is correct
		visited.resize(size);
	for(unsigned int i = 0; i < visited.size(); ++i)//reset the visted vector to none visted
		visited[i] = false;
	pathOrder.erase(pathOrder.begin(), pathOrder.end());//Resests the path order
	visitedOrder.erase(visitedOrder.begin(), visitedOrder.end());//Reset the visited order
	cout << "Starting at vertex: " << labels[0] << endl;

	for (int i = 0; i < size; ++i){//Loop through and traverse the graph
		if(!visited[i]){//Determines if the vertex has not been visited
			depth_first(i);//visite node
			visitedOrder.push_back('0');//Adds a zero to represent a backtrack of the graph/if a graph is disconnected
			visitedOrder.push_back(labels[i]);
		}
	}

        cout << "------The Traversed Path is----------" << endl;
	bool skip = false;
	int addON = 0;
	string connection;
        for (unsigned int i = 0; i < pathOrder.size(); ++i){//loop through the pathOrder
                cout << setw(3) << pathOrder[i];

		//A zero represents when the visitedOrder backtracked when reading the graph
		if( visitedOrder[i + 2] == '0'){//Determines if the iteration should be skipped
			skip = true;
		}
		if ( skip == false){//skips to the next iteration to avoid printing the 0
			 if( visitedOrder[i + 1] == '0'){//Builds a string that deals with backtracking
                       	        connection += "(";
                                connection += " ";
                                connection += visitedOrder[i+2];
                                connection += ",";
                                connection += ' ';
                                connection += visitedOrder[i];
                                connection += ' ';
                                connection += ')';
                                connection += ' ';
				addON++;//increase the part of where the data is be appended
				++i;//increases the the data to get past the zero
			}
			else{//Builds a string with a path that goes in order
				connection += "(";
				connection += " ";
				connection += visitedOrder[i + addON];
				connection += ",";
				connection += ' ';
				connection += visitedOrder[i+1+addON];
				connection += ' ';
				connection += ')';
				connection += ' ';
			}
		}
		else{
			skip = false;
		}
        }
        cout << endl;
	cout << connection << endl;
        cout << "---------End of Traversal------------" << endl;

}


////////////////////////////////////////////////////////////////////////////////////////////////////
//This method prints the current node and all of its adjacent nodes
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void graph::print() const{

	list<int>::const_iterator adjacents;
	cout << "The size of the graph is: " << size << endl << endl;

	cout << "--------Graph--------" << endl;
	int lineCount = 0;
	bool firstTime = true;
	while (lineCount < size){//Loops through each line until the line count is greater than the size of the adj_list
		adjacents = adj_list[lineCount].begin();
		cout << labels[lineCount] << ":  ";
		for (int i = 0; i < size; ++i){//Loop through each line and print out the label 
			if (*adjacents == 1 && firstTime == false){//Determines if the node is adjacent to the current lineNode
				cout << ',' << ' ' <<labels[i];
			}
			else if(*adjacents == 1){//If this is the first time through, do not print a comma
				cout << labels[i];
				firstTime = false;
			}
			++adjacents;
		}
		firstTime = true;
		++lineCount;
		cout << endl;
	}

	cout << "------End of Graph-----" << endl << endl;

}



#define ASSIGNMENT9_TEST
#ifdef 	ASSIGNMENT9_TEST

int main(int argc, char** argv) {
    if ( argc < 2 ) {
        cerr << "args: input-file-name\n";
        return 1;
    }
    
    graph g(argv[1]);

    g.print();
    
   g.traverse();

    return 0;
}

#endif
