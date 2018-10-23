/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    03/06/18
Assignment:  Assignment5


Purpose:     To create and maintain a max or min heap


***************************************************************************************************/

#include<algorithm>
#include<iostream>
#include<iomanip>
#include<vector>
using std::cout;
using std::endl;
using std::vector;
using std::setw;

const int HEAP_SIZE = 50;
const int NUM_PER_LINE = 8;

//Forward declarations of functions
void build_heap (vector<int> &v, int heap_size, bool (*compare)(int,int));
void heapify( vector<int> &v, int heap_size, int r, bool (*compare)(int,int));
void swap(int& x, int& y);
bool less_than (int e1, int e2);
bool greater_than (int e1, int e2);
int extract_heap( vector<int>& v, int& heap_size, bool (*compare)(int,int));
void print_vector( vector<int>& v, int pos, int size);

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function builds a heap
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void build_heap (vector<int> &v, int heap_size, bool (*compare)(int,int)){
	for (int i = heap_size/2;i > 0;--i){//heapifies each part of the vector
		heapify(v,heap_size,i,compare);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function maintains the heap property in a vector
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void heapify( vector<int> &v, int heap_size, int r, bool (*compare)(int,int)){
	int holder = r;//holder stores either the smallest or largest value depending on min or max heap
	int left = 2*r;
	int right = ( 2*r ) + 1;
	if (left <= heap_size && compare(v[left],v[holder])){//Determines if the left is bigger/smaller
		holder = left;
	}
	if(right <= heap_size && compare(v[right],v[holder])){//Determines if the right is bigger/smaller
		holder = right;
	}

	if(holder != r){//Determines if the bigger/smaller is the parent,if not then goes into if statement
		swap(v[r], v[holder]);//switches the parent with the largest/smallest value
		heapify(v, heap_size, holder, compare);//calls heapify on the swapped value to maintain heap property all the way down the vector
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This is a helper function that swaps the data of the two passed in variables
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void swap(int& x, int& y){
	int temp = x;
	x = y;
	y = temp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function isused to determine if the first parameter is smaller than the second
//      Returns:True if first is smaller, false if second is smaller
////////////////////////////////////////////////////////////////////////////////////////////////////
bool less_than (int e1, int e2){
	return e1 < e2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function isused to determine if the first parameter is bigger than the second
//      Returns:True if first is bigger, false if second is bigger
////////////////////////////////////////////////////////////////////////////////////////////////////
bool greater_than (int e1, int e2){
        return e1 > e2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function sorts the heap into either ascending order or decending order depending of if it is a max or min heap
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void heap_sort( vector<int>& v, int heap_size,bool (*compare)(int, int) ){
	build_heap(v, heap_size,compare);
	int n = heap_size;
	for(int i = heap_size; i > 0; --i){//puts each element in order depending on if it is a min or max heap
		swap(v[1], v[i]);
		--n;
		if (n == 0)
			++n;
		heapify(v, n, 1, compare);
	}
	for ( unsigned int i = 0; i < v.size(); ++i){//moves the useless slot to the end and moves each element up one
		if((i+1) < v.size())
			v[i] = v[i+1];
		else
			v[i] = -1000000;
	}
		std::reverse(v.begin(),v.end());//reverses the order of the vector
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function removes the root and replaces it with the last element in the heap
//      Returns:returns the old root value
////////////////////////////////////////////////////////////////////////////////////////////////////
int extract_heap( vector<int>& v, int& heap_size, bool (*compare)(int,int)){
	if (heap_size < 1)//does not extract if there is only one item in the array
		cout << "Error: Heap Underflow" <<endl;
	int holder = v[1];
	v[1] = v[heap_size];
	heap_size--;
	heapify(v, heap_size,1,compare);

	return holder;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function prints out a vector in a readable format.
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void print_vector( vector<int>& v, int pos, int size){
	int numberPrinted = 0;
	for(int i  = 0;i < size; ++i){//iterates through the vector,printing each element
		++numberPrinted;
		cout << setw(5) << v[i+pos];
		if(numberPrinted >= NUM_PER_LINE){//determines if a new line needs to be printed
			numberPrinted = 0;
			cout << endl;
		}
	}
	cout << endl;
}




int main(int argc, char** argv) {
    // ------- creating input vector --------------
    vector<int> v;
    v.push_back(-1000000);    // first element is fake
    for (int i=1; i<=HEAP_SIZE; i++)
        v.push_back( i );
    random_shuffle( v.begin()+1, v.begin()+HEAP_SIZE+1 );

    cout << "\nCurrent input numbers: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    // ------- testing min heap ------------------
    cout << "\nBuilding a min heap..." << endl;
    build_heap(v, HEAP_SIZE, less_than);
    cout << "Min heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, less_than);
    cout << "Heap sort result (in ascending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

   //  ------- testing max heap ------------------
    cout << "\nBuilding a max heap..." << endl;
    build_heap(v, HEAP_SIZE, greater_than);
    cout << "Max heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, greater_than);
    cout << "Heap sort result (in descending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    return 0;
}
