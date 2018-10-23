/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    01/29/18
Assignment:  Assignment1


Purpose:     Search through randomly created vectors using an iterative and binary search method
	     Also, shows the difference in effiecienty in the two methoods

***************************************************************************************************/
#include <iomanip>
#include <iostream>
#include<vector>
#include <algorithm>

using std::setw;
using std::endl;
using std::cout;
using std::vector;

const int DATA_SIZE = 200;
const int DATA_RANGE = 200;
const int DATA_SEED = 9;
const int SEARCH_SEED = 17;
const int NUM_PER_LINE = 8;

//Function that uses an iterative method to search through a vector
//      Returns:The location where it found the target or -1 if nothing was found
//////////////////////////////////////////////
int linear_search(const vector<int>& inputVec, const int x, int& comparisons) {
	comparisons=0;//resestes the comparison value
	for(int i = 0; i < (int)inputVec.size(); ++i){//loops through vector searching for a match
		++comparisons;
		if (inputVec[i] == x)
			return i;//return the location where the match was found
	}
	return -1;
}
//Function that uses a binary search method to search through a method
//      Returns:the location of the target or -1 if nothing was found
////////////////////////////////////////////////
int binary_search(const vector<int>& inputVec, const int x, int& comparisons) {
	comparisons=0;//reset the comparison
	int end = inputVec.size()-1;
	int begin= 0;
	int mid = (end+begin)/2;//calculates the midpoint
	while (begin <= end){
		++comparisons;
		if(inputVec[mid] == x)//checks if the midpointis equal to the target
			return mid;
		else if (inputVec[mid] > x)//If the midpoint was larger that the target,sets the end to the middle
			end = mid - 1;
		else if (inputVec[mid] < x)//If the midpoint was smaller than the target, sets the begining to the middle
			begin = mid + 1;
		mid = (end+begin)/2;//recalculate  the middle
	}
	return -1;

}
//Function that prints out the contents of a vector
//      Returns : Nothing
////////////////////////////////////////////////////////////
void print_vec( const vector<int>& vec ){
	int countPerLine = 0;
	for (int i = 0; i < (int)vec.size();  ++i){//loops trough and prints the content of the vector
		cout << setw(4) << vec[i];
		++countPerLine;
		if (countPerLine == NUM_PER_LINE){//determines if a new line should be printed
			cout << endl;
			countPerLine = 0;
		}
	}
}

//Function that calulates the amount of comparasions each method of searching takes
//    returns :nothing
//////////////////////////////////////
void average_comparisons(const vector<int>& inputVec, const vector<int>& searchVec, int (*search)(const vector<int>&, const int, int&) ) {
    int i, comparison = 0, sum = 0, found = 0;
    int res = 0;
    for (i = 0; i < (int)searchVec.size(); i++) {//loops through the vector with the valuse to search for in the target vector
        res = search( inputVec, searchVec[i], comparison );
        sum += comparison;
        if ( res >= 0 )//determines if the result was found
           found++;
    }
    cout << found << " numbers are found. The average number of comparisons in each search: " << (double)sum/(double)searchVec.size() << endl << endl;
}

//Funtion that returns a ranom intergar
//     returns: a rnadom interger
/////////////////////////////////////
int random_number() {
    return rand()%DATA_RANGE + 1;
}


int main () {

    // -------- create unique random numbers ------------------//
    vector<int> inputVec(DATA_SIZE);
    srand(DATA_SEED);
    generate(inputVec.begin(), inputVec.end(), random_number);
    sort(inputVec.begin(), inputVec.end());
    vector<int>::iterator it = unique(inputVec.begin(), inputVec.end());
    inputVec.resize( it - inputVec.begin() );
    random_shuffle( inputVec.begin(), inputVec.end() );

    cout << "------ Data source: " << inputVec.size() << " unique random numbers ------" << endl; 
    print_vec(inputVec);
    cout << endl;

    // -------- create random numbers to be searched ---------//
    vector<int> searchVec(DATA_SIZE/2);
    srand(SEARCH_SEED);
    generate(searchVec.begin(), searchVec.end(), random_number);

    cout << "------ " << searchVec.size() << " random numbers to be searched: ------" << endl;
    print_vec(searchVec);
    cout << endl;

    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    sort(inputVec.begin(), inputVec.end());
    cout << "------- numbers in data source are now sorted ---------" << endl << endl;
    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    return 0;

}


