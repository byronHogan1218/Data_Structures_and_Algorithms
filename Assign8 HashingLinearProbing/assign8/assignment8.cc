/*************************************************************************************************
Programmer:  Byron Hogan
Zid:         z1825194
Due Date:    04/18/18
Assignment:  Assignment8


Purpose:     To create and maintain a hash table


***************************************************************************************************/

#include<iomanip>
#include<iostream>
#include<sstream>
#include<string>
#include"assignment8.h"
#include<fstream>
#include<vector>

using std::vector;
using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::setw;


////////////////////////////////////////////////////////////////////////////////////////////////////
//This is the constructor for a hash table
////////////////////////////////////////////////////////////////////////////////////////////////////
HT::HT( int s = 11){

	hTable = new vector<Entry>(s);

	table_size = s;
	item_count = 0;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This is the deconstructor
////////////////////////////////////////////////////////////////////////////////////////////////////
HT::~HT(){
	delete hTable;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method searches the hash table for the key
//      Returns:An interger that is the position the it found the key in,-1 for not found
////////////////////////////////////////////////////////////////////////////////////////////////////
int HT :: search(const string& key){
	int index = hashing(key);
	int i = 0;
	int j = 0;
	while(j < table_size){//loop through the entire table
		if ((*hTable)[index + i].key == key){//determines if the key was found
			return (index + i);//key found at this position
		}
		else
			++i;
		if ( (index + i) > table_size - 1)//determines is the index needs to be set to 0
			i = i - (table_size);
		++j;
	}
	return -1;//key not found
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method inserts an item into the hash table
//      Returns:True if successfully inserted, false it it couldn't insert
////////////////////////////////////////////////////////////////////////////////////////////////////
bool HT::insert( const Entry& e ){
	int index = hashing(e.key);

	if (item_count >=  table_size){//Check for a full table,immediately return with error if true
		cout << "Error:The table is full" << endl;
		return false;
	}

	int positionOfKey = search(e.key);
	if (positionOfKey != -1){//Determines if the key already exists
                cout << "Error:This key already exists" << endl;
                return false;
        }


	int i = 0;
	int positionToInsert;

	while((*hTable)[(index + i)].key != "---" && (*hTable)[(index + i)].key != "+++"){//loops through the hash table,starting at the key
		++i;
		if ( (index + i) > table_size - 1)//Determines if the index needs to be reset to the begining of the table
			i = i - (table_size);
	}
	//Loop quits when it finds the first available poistion to insert
	positionToInsert = (i + index);

	//Sets the position to be the hash key/value pair
	(*hTable)[positionToInsert].key = e.key;
	(*hTable)[positionToInsert].description = e.description;
	++item_count;
	return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method removes a key from the hash table
//      Returns:True if it was able to remove the key,false if it could not
////////////////////////////////////////////////////////////////////////////////////////////////////
bool HT::remove(const string& s){
	int deletePosition = search(s);//Searches the table for the key to delete
	if (deletePosition == -1)//determines if the key exists in the table
		return false;
	(*hTable)[deletePosition].key = "+++";//Lazy deleteion,set key equal to +++ to indicate that it is no longer a valid entry
	--item_count;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method prints the hash table in  a readable fomrat
//      Returns:Nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void HT::print(){
	cout << "-----Hash Table-----" << endl;

	for(int i = 0;i < table_size;++i){//Loops throughthe entire table
		if((*hTable)[i].key != "---" && (*hTable)[i].key != "+++"){//Determines if the value should be printed
			cout  << setw(3) << i << ": ";
			cout  << setw(4) << (*hTable)[i].key << ": ";
			cout << (*hTable)[i].description << endl;
		}
	}
	cout << "--------------------" << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function gets the entry to be inserted into the hash table from a string
//      Returns:A pointer to an Entry object
////////////////////////////////////////////////////////////////////////////////////////////////////
Entry* get_entry(const string& line){

	char delimiter = ':';

	std::istringstream split(line);
	vector<string> tokens;
	string code,itemKey,itemDescription;
	for ( string each; getline(split,each,delimiter); tokens.push_back(each));//Splits the string with a ':' as a delimiter 

	code = tokens[0];
	itemKey = tokens[1];
	itemDescription = tokens[2];

	Entry* newEntry = new Entry();
	newEntry->key = itemKey;
	newEntry->description = itemDescription;

	return newEntry;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This function gets the a key from a string
//      Returns:A string that is the key for the hash table
////////////////////////////////////////////////////////////////////////////////////////////////////
string get_key(const string& line){

	string code,itemKey;

        char delimiter = ':';

        std::istringstream split(line);
        vector<string> tokens;

        for ( string each; getline(split,each,delimiter); tokens.push_back(each));//Splits the string using ':' as a delimiter

	if (tokens.size() == 1)//Determines if there was no key in the string,adss an empty string to avoid a segfault
		tokens.push_back("");

        code = tokens[0];
	itemKey = tokens[1];

	return itemKey;
}

// key is in form of letter-letter-digit
// compute sum <-- ascii(pos1)+ascii(pos2)+ascii(pos3)
// compute sum%htable_size
int HT::hashing(const string& key) {
   return ((int)key[0] + (int)key[1] + (int)key[2])%table_size;
}

int main(int argc, char** argv ) {

    if ( argc < 2 ) {
        cerr << "argument: file-name\n";
        return 1;
    }
    HT ht;
    ifstream infile(argv[1], ios::in);
    string line;
    infile >> line;    
    while ( !infile.eof() ) {
        if ( line[0] == 'A' ) {
            Entry* e = get_entry( line );
            ht.insert( *e );
            delete e;
        }
        else {
            string key = get_key(line);
            if ( line[0] == 'D' ) {
                cout << "Removing " << key << "...\n";
                bool removed = ht.remove( key );
                if ( removed )
                    cout << key << " is removed successfully...\n\n";
                else
                    cout << key << " does not exist, no key is removed...\n\n";
            }
            else if ( line[0] == 'S' ) {
                int found = ht.search( key );
                if ( found < 0 ) 
                    cout << key << " does not exit in the hash table ..." << endl << endl;
                else
                   cout << key << " is found at table position " << found << endl << endl;
            }
            else if ( line[0] == 'P' ) {
                cout << "\nDisplaying the table: " << endl;
                ht.print();
            }
            else
                cerr << "wrong input: " << line << endl;
        }
        infile >> line;
 
    }

    infile.close();
    return 0;
}
