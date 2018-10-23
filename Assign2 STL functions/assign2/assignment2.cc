/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    02/09/18
Assignment:  Assignment2


Purpose:     Search through randomly created vectors using an iterative and binary search method
             Also, calculate and show the percentage of the amount of times the numbers were found

***************************************************************************************************/
#include<iomanip>
#include<vector>
#include<iostream>
#include<algorithm>
#include<cstdlib>

//Common standard library references are predefined here
using std::vector;
using std::cout;
using std::endl;

const int DATA_SIZE = 100;
const int SEARCH_SIZE = 50;
const int DATA_SEED = 11;
const int SEARCH_SEED = 7;
const int NUM_PER_LINE = 10;
const int ITEM_W = 6;
const int HIGH = 100;
const int LOW = 1;

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function fills a vector with randomly generated numbers b/w 1-100
//	Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void genRndNums( vector<int>& v, int seed ) {
	srand(seed);
	for (unsigned int i = 0; i < v.size(); ++i){//loops through and fills up the vector with random numbers
		v[i] = rand () % (HIGH - LOW +1) + LOW;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function does a linear search to try and find the target
//      Returns:True if it found target, flase if it didn't
////////////////////////////////////////////////////////////////////////////////////////////////////
bool linearSearch( const vector<int>& inputVec, int x) {
	vector<int>::const_iterator it;
	it = std::find(inputVec.begin(), inputVec.end(), x);//returns an iterator to position target was found at, set to end if not found
	if (it != inputVec.end())//determines if target was found
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function sorts a vector in ascending order
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void sortVector (vector<int>& inputVec) {
        std::sort(inputVec.begin(), inputVec.end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function does a Binary search to try and find the target
//      Returns:True if it found target, flase if it didn't
////////////////////////////////////////////////////////////////////////////////////////////////////
bool binarySearch( const vector<int>& inputVec, int x) {
        if(std::binary_search(inputVec.begin(), inputVec.end(), x))//determines if target was found
                return true;
        else
                return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function calls the appropriate search function to find the target
//      Returns:The number of times it successfully found an item
////////////////////////////////////////////////////////////////////////////////////////////////////
int search( const vector<int>& inputVec, const vector<int>& searchVec, bool (*p)( const vector<int>&, int) ){
	int totalSuccesses = 0;
	bool holder;
	for (unsigned int i= 0; i < searchVec.size(); ++i){//loops through the values to be searched for
		holder = p(inputVec, searchVec[i]);
		if (holder == true)//determines if the value being searched for was found
			++totalSuccesses;
	}
	return totalSuccesses;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function calculates and prints the percentage of times it found the target
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void printStat (int totalSucCnt, int vec_size) {
	float total;
	total = 100 * ((float)totalSucCnt/ (float) vec_size);//calculates the percentage of the amount of times the values were found
	cout << std::fixed;
	cout << "Successful Searches: " << std::setprecision(2) << total << "%" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function prints the contents of a vector
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void print_vec( const vector<int>& vec ){
        int countPerLine = 0;
        for (int i = 0; i < (int)vec.size();  ++i){//loops trough and prints the content of the vector
                cout << std::setw(ITEM_W) << vec[i];
                ++countPerLine;
                if (countPerLine == NUM_PER_LINE){//determines if a new line should be printed
                        cout << endl;
                        countPerLine = 0;
                }
        }
	cout << endl;
}

int main() {
    vector<int> inputVec(DATA_SIZE);
    vector<int> searchVec(SEARCH_SIZE);
    genRndNums(inputVec, DATA_SEED);
    genRndNums(searchVec, SEARCH_SEED);

    cout << "----- Data source: " << inputVec.size() << " randomly generated numbers ------" << endl;
    print_vec( inputVec );
    cout << "----- " << searchVec.size() << " random numbers to be searched -------" << endl;
    print_vec( searchVec );

    cout << "\nConducting linear search on unsorted data source ..." << endl;
    int linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on unsorted data source ..." << endl;
    int binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    sortVector( inputVec );

    cout << "\nConducting linear search on sorted data source ..." << endl;
    linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on sorted data source ..." << endl;
    binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    return 0;
}

