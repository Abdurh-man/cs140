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

class list{
	struct node {   
		node(int data = 0); 
		int data;  
		node *next; 
	};

	public:
	list();
	~list();

	bool insert(int);

	private:
	node *head;

	friend ostream & operator<<(ostream &, const list &);
};

list::node::node(int n_data){ 
	data = n_data;  
	next = NULL;
}

list::list(){
	head = new node;
}

list::~list(){
	node *p_next = head;
	// point to first val if empty null if not then a number
	node *p = head -> next;
	while(p != NULL){
		// p_next value after p 
		p_next = p -> next;
		
		// deletes p
		delete p;
		// p = p_next
		p = p_next;
	}
}

bool list::insert(int num){
	node *prev = head;
	node *p = head -> next;

	while(p != '\0'){
		// if p == num delete
		if(p -> data == num){
			// links prev rest of list
			prev -> next = p -> next;
			// deletes p and breaks out 
			delete p;
			return false;
		}
		// if p > num change the order of p to where its after num
		else if(p->data > num){
			// new node goes between prev and p
			prev -> next = new node(num);
			prev -> next -> next = p;
			return true;
		}
		// go to next values
		prev = prev -> next;
		p = p -> next;
	}
	// if p == add a new value to p
	if(p == '\0'){
		p = new node(num);
		p -> next = prev->next;
		prev -> next = p;
	}

	return true;}

	ostream & operator<<(ostream & out, const list & l){
		list::node *p;
		p = l.head-> next;

		// while p hold a value print
		while(p != NULL){
			// p point to data and the value found gets passed to face and the index is printed
			out << ' ' << face[p->data];			
			p = p-> next;
		}

		return out;
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

	// an array of type list. it has 4 rows
	list drawn[4] = {};

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

		// insert(v) to row s 
		// if insert returns true increment if false decrement
		if(drawn[s].insert(v))
			table[s][v]++; 

		else
			table[s][v]--; 

		//l.insert(v);

		// break out of loop if stopping criteria met
		// after table is updated [row][coln] it looks at the value of the last row updated at index 10,11,12
		if(table[s][10] == 1 && table[s][11] == 1 && table[s][12] == 1) 
			break;
	}
	for(int i = 0; i < 4; i++){
		cout << setw(8) << suit[i] << " :";
		// passes all of row i to the overload operator 
		cout << drawn[i];
		// if the row has jack queen and king cout ** at said row
		// s hold row index where the breakout statment is true
		if(s == i)
			cout << " **";
		cout << endl;
	}
}
