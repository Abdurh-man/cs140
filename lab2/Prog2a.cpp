#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
	"8", "9", "10", "Jack", "Queen", "King" }; 
const string suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };

string random_card(bool verbose=false) {
	string card;

	card = face[ rand()%13 ];
	card += " of ";
	card += suit[ rand()%4 ];

	if (verbose)
		cout << card << "\n";

	return card;
}
// breaks up value returned by random_card
// passed by refrence updates v and s in intmain
void decode(const string & str_card, int & v, int & s){
	string temp;
	// breaks up the first word and puts it to temp
	stringstream iss(str_card);
	iss >> temp;

	// runs through face-global-array and assigns the index number where temp == face to v
	for(int i = 0; i < 13; i++){
		if(temp == face[i]){
			v = i;
			break;
		}
	}
	// assigns the send word in string card to temp
	// the of the 2nd extraction is ignored since its of
	iss >> temp;
	// gets 3rd word in string and assignes to temp
	iss >> temp;
	// updates the s value with the index where temp == suit
	for(int i = 0; i < 4; i++){
		if(temp == suit[i]){
			s = i;
			break;
		}
	}

}

int main(int argc, char *argv[])
{
	bool verbose = false;
	int seedvalue = 0;

	for (int i=1; i<argc; i++) {
		string option = argv[i];
		if (option.compare(0,6,"-seed=") == 0) {
			seedvalue = atoi(&argv[i][6]);
		} else if (option.compare("-verbose") == 0) {
			verbose = true;
		} else 
			cout << "option " << argv[i] << " ignored\n";
	}

	srand(seedvalue);
	int s = 0; // suit
	int v = 0; // value
	// declare a table[][] that can keep track of the
	int table[4][13];

	// cards dealt for each suit -- initialize to 0
	// table[0][0] = 0 table [0][1] = 0 and so on
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 13; j++){
			table[i][j] = 0;
		}
	}



	while (1) {
		string card = random_card(verbose);
		// reverse engineer card suit and face (value)
		decode(card, v, s);
		// update accordingly: table[suit][value]++
		table[s][v]++; // inital value at that place is 0 but now its 1 if called again then 2 and so on
		// break out of loop if stopping criteria met
		// after table is updated [row][coln] it looks at the value of the last row updated at index 10,11,12
		if(table[s][10] >= 1 && table[s][11] >= 1 && table[s][12] >= 1) 
			break;
	}

	for(int i = 0; i < 4; i++){
		cout << setw(9) << left << suit[i] << ": ";
		for(int j = 0; j < 13; j++){
			// cout table[0][0] table[0][1] and so on
			cout << setw(3) << table[i][j];
		}
		// the break out statment above breaks when the last value of table[s][10,11,12] >= 1 
		// cout ** at whatever row the loop above breakout of 
		if(s==i)
			cout << "**";
		cout << endl;
	}
}
