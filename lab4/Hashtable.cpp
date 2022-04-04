#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<fstream>
#include<ctype.h>
#include<sstream>

using namespace std;

typedef unsigned int uint;

class hash_table { 
	private:
		struct key_line{
			// Checks to see if the key is being used or not
			bool inuse(){
				if(key == string()) 
					return false;
				return true;}
			// compares the inputed string to key and retruns true if equale or fasle if not
			bool operator==(const string& eq) const{ return (eq == key);}

			key_line(){		
				key = string();
				lines = vector<int>();
			};
			string key;		
			vector<int>lines;
		};

	public: 
		hash_table(int num);  
		~hash_table();
		void insert(const string &,const int&); 

		// this vector returns the line number that holds key
		const vector<int>&find (const string &key);
		//{return (table[ qprobe(key,false) ].lines);}	

		// when inserting is dont print the load
		void insert_done();
		//{ if(showstats) showload();}

		// updates showstats if the argument -showstats is given in main
		void set_showstats();
		//{showstats = true;}

	private: 
		int hash(const string &);  
		int  nextprime(int); 
		int  qprobe(const string &,bool ); 
		void resize();   
		void showload();

		int num_inuse; 
		int max_inuse;   
		int collisions;
		bool showstats;

		vector<key_line> table;

};
// constructor takes an int and asigns that int to N
hash_table::hash_table(int num){
	int N = nextprime(num); 
	table.assign(N, key_line()); 

	num_inuse = 0; 
	max_inuse = N/2;
	collisions = 0;

	showstats = false;
}
const vector<int> &hash_table::find(const string &key){
		return (table[ qprobe(key,false) ].lines);
}	

		// when inserting is dont print the load
void hash_table::insert_done(){ 
	if(showstats) 
		showload();
}

		// updates showstats if the argument -showstats is given in main
void hash_table::set_showstats(){
	showstats = true;
}
// inserts key at a specific hash values
void hash_table::insert(const string &key, const int& val){
	int index = qprobe(key,true); 

	//if the index is not being used then set the index to key and increment the amount of lines
	if (!table[index].inuse()){   
		table[index].key = key; 
		num_inuse++;
	}
	// if the line number is not found then add it to the table
	if(std::find(table[index].lines.begin(), table[index].lines.end(), val) == table[index].lines.end())
		table[index].lines.push_back(val);

	// if the amount of lines used is bigger than or half the size then resize the talbe
	if (num_inuse >= max_inuse){ 
		// the load is called each time the table size is changed
		insert_done();
		resize();  
	}
}

int hash_table::hash(const string &key){
	uint index = 0;  
	const char *c = key.c_str(); 

	while (*c)    
		index = ((index << 5) | (index >> 27)) + *c++;  

	return index % table.size();
}


int hash_table::nextprime(int N){
	// keeps the size odd
	N = (2*N + 1);
	int i = 2; 
	while (i*i <= N){
		if (N%i == 0) { 
			N+=2; i = 1; 
		}    
		i++;  
	} 

	return max(3,N);
}

int hash_table::qprobe(const string &key, bool collision){
	int index = hash(key); 
	int k = 0;

	while (table[index].inuse() && (!(table[index] == key)) ){
		index += 2*(++k) - 1; 
		index = index % table.size(); 
		// increment collision if the arugment that is based in is true and the while loop condition is true
		if(collision)
			++collisions;
	}

	return index;
}

void hash_table::resize(){
	// tmp table to move things over so we can resize
	vector<key_line> tmp_table;

	for (int i=0; i<(int)table.size(); i++){
		if (table[i].inuse())   
			tmp_table.push_back(table[i]); 
	} 
	// N = the next size
	int N = nextprime(table.size());
	// assignes N to line
	table.assign(N, key_line());   

	num_inuse = 0; 
	max_inuse = N/2;

	for (int i=0; i < (int)tmp_table.size(); i++){ 
		key_line &key = tmp_table[i]; 
		table[ qprobe(key.key,false) ] = key;   
		num_inuse++;  
	}
}
// prints of -showstats is given in intmain
void hash_table::showload(){
	if(showstats)
		printf("** N = %6d load = %4.2f\n", + (int)table.size(), (float)num_inuse/(float)table.size());
}
// if -showstats is given then when leaving the scope print the stats
hash_table::~hash_table(){
	if(showstats){
		cout << endl << "Run stats ..." << endl
			<< "Number of slots used: " << num_inuse << endl
			<< "Max number of slots:  " << max_inuse << endl
			<< "Number of collisions: " << collisions << endl;
	}
}
char replace_punctuation(char c){
	char empty = ' ';
	if(ispunct(c))
		return empty;
	else	
		return c;
}

int main(int argc, char *argv[]){

	if(argc < 3){
		cerr << "./Hashtable [-N number] [-showstats] -f textfile \n";
		return 1;
	}

	int N = 23;
	bool show = false;
	string file;

	string _N = "-N";
	string _f = "-f";
	string _showstats ="-showstats";

	for(int i = 1; i < argc; i++){

		if(argv[i] == _N){
			N = atoi(argv[++i]);
			if(N < 1){
				cerr << "incompatible size";
				return 1;
			}
		}

		else if(argv[i] == _f)
			// going to the next comand line argument beacuse it should be the file and increment i as well
		file = argv[++i];

		else if(argv[i] == _showstats)
			show = true;

		else{
			cerr << "./Hashtable [-N number] [-showstats] -f textfile \n";
			return 1;
		}
	}


	hash_table H(N);


	if(show)
		H.set_showstats();

	ifstream fin (file.c_str());

	if (!fin){
		cout << "Unable to open file\n"; 
		return 1;
	}

	string line;
	vector<string>text; 
	// line starts at 1 not 0
	int num_lines = 1; 

	// gets then line then pushs it back the the string vector text
	// breaks the line string by string and inserts it to the Hashtable
	while(	getline(fin,line)  ){
		text.push_back(line);		

		std::transform( line.begin(), line.end(), line.begin(), replace_punctuation );

		istringstream iss(line);

		string temp;

		while(iss>>temp){
			H.insert(temp,num_lines);
		}
		num_lines++;	
	}
	// close because you have read everthing from the file and dont need it anymore
	fin.close();

	H.insert_done();
	// print ouf stats


	string input;

	cout << "find> ";
	while(cin >> input){
		// reads the find vector line 
		for(unsigned int i = 0; i < H.find(input).size() ; i++){
			// the [i] acts as derfrence it 
			int temp =  H.find(input)[i] ;
			//temp minus when when indexed into text because text starts at 0 and the first line is 1
			cout << temp << ": " <<text[temp-1] << endl;
		}
		cout << "find> ";
	}

	cout << endl;
	return 0;
}
