/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    02/16/18
Assignment:  Assignment3


Purpose:     Continously ask user for a range of numbers and finding the prime numbers inbetween them

***************************************************************************************************/
#include<iostream>
#include<set>
#include<vector>
#include<iomanip>
#include <ctype.h>

using std::set;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::setw;

const int NUM_PER_LINE = 6;
const int ITEM_W = 4;


////////////////////////////////////////////////////////////////////////////////////////////////////
//This function is used to find all the primes in the given range and store it in a set
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void sieve( set<int>& s, const int lower, const int upper) {

vector<bool> v1;
for (int i = 0; i <= upper; ++i){//fills up a vector with true values
	v1.push_back(true);
}
v1[0] = false;//sets 0 to not a prime
v1[1] = false;//sets 1 to not prime
int count = 1;
int temp = 0;
int j = 2;
while( (j * j) <= upper) {//changes all the nonprime numbers to false
	if ( v1[j] == true) {
		temp = (j * j);
		count = 1;
		while (temp <= upper){//crosses out the non prime numbers
			v1[temp] = false;
			temp = (j * j) + ( j * count);
			++count;
		}
	}
	++j;//update the loop
}
int i = 0;
while (i <= upper){//fills the set with the prime numbers between lower and upper
	if (v1[i] == true){
		if (i >= lower){
			s.insert(i);
		}
	}
	++i;
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function prints the amount of primes found and what they are
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void print_primes( const set<int>& s, const int lower, const int upper) {
set<int>::iterator iter;
int printedCount = 1;
int numOfPrimes = 0;
for (iter = s.begin(); iter != s.end(); ++iter){//counts the amount of primes
	++numOfPrimes;
}
cout << "There are " << numOfPrimes << "  prime numbers inbetween " << lower << " and " << upper << " which are :" << endl;
for (iter = s.begin(); iter != s.end(); ++iter){//prints out the prime numbers in the set
	cout << setw(ITEM_W) << *iter;
	if(printedCount >= NUM_PER_LINE){//determines if a newline should be printed
		cout << endl;
		printedCount = 0;
	}
	++printedCount;
}
cout << endl;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This function has error handling to make sure a number is entered for the lower bound
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void lowerError(int & lower){
        while ( cin.fail() ){//Error Handling:Makes sure a number is entered
                cin.clear();
                cin.ignore(50, '\n');
                cout << "You must enter a number, please try again" << endl;
                cout << "Please enter the Lower bound of the range(must be above 2): ";
                cin >> lower;
        }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//This function has error handling to make sure a number is entered for the upper bound
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void upperError(int & upper){
        while ( cin.fail() ){//Error Handling:Makes sure a number is entered
                cin.clear();
                cin.ignore(50, '\n');
                cout << "You must enter a number, please try again" << endl;
                cout << "Please enter the Upper bound of the range(must be above Lower bound): ";
                cin >> upper;
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This function asks the user for the range and has error handling to make sure the information is valid
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void run_game(set<int>& s) {

int lower = 0;
int upper = 1;
bool playAgain = true;
char userChoice;
while ( playAgain ){//runs until the user tells it to stop
	cout << "Enter two numbers to search between for prime numbers" << endl;
	cout << "Please enter the Lower bound of the range(must be above 2): ";
	cin >> lower;
	lowerError(lower);
	cout << "Please enter the Upper bound of the range(must be above Lower bound): ";
	cin >> upper;
	upperError(upper);
	while (lower > upper || lower < 2 || upper < 2 ) {//Error Handling:making sure the entry is a valid number in the range
	        cout << "Invalid enter,please try again" << endl;
	        cout << "The numbers must be greater than 2 and Upper must be greater than Lower" << endl;
	        cout << "Please enter the Lower part of the range{must be above 2): ";
	        cin >> lower;
		lowerError(lower);
        	cout << "Please enter the Upper part of the range(must be above Lower bound): ";
	        cin >> upper;
		upperError(upper);

	}
	sieve(s, lower, upper);
	print_primes ( s, lower, upper);
	s.clear();//flushes the old data in the set
	userChoice = 'y';
	cout  << "Would you like to try again? (y/n) ";
	cin >> userChoice;
	while ( tolower(userChoice) != 'n' && tolower(userChoice) != 'y'){//Error Handling:Make sure that a y or n is entered
		cout << "Invalid entry, please enter either a \"y\" or a \"n\"" << endl;
	        cout  << "Would you like to try again? (y/n) ";
	        cin >> userChoice;
	}
	if ( tolower(userChoice) == 'n')//determine if the program should quit
		playAgain = false;
}
}

int main() {
    set<int> s;
    run_game(s);
    return 0;
}
