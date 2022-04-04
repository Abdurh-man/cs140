#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<algorithm>
#include<iomanip>
#include<numeric>
#include<fstream>
#include<algorithm>
#include<stdlib.h>
#include<vector>

using namespace std;

class name_t {
	public:
		//constructor(s);
		name_t();
		name_t(const string&, const string&);

		bool operator<(const name_t&) const;
		void print(int W=0) const;

	private:
		string name;
};

class scores_t {
	public:
		//constructor(s);
		scores_t();

		void insert(int);
		void insert_done();
		void print();

	private:
		vector<int> scores;
		float mean;
};
//name_t
name_t::name_t(){
	name = " ";
}

name_t::name_t(const string& first, const string& last){
	name = last + ", " + first + " ";
}

bool name_t::operator<(const name_t& rhs) const{
	return(name < rhs.name);
	/*
	operator<: A < B
	operator>: B < A
	operator==: !(A < B) && !(B < A)
	operator!=: (A < B) || (B < A)
	operator<=: !(B < A)
	operator>=: !(A < B)
*/
	}

void name_t::print(int w) const{
	cout<< setw(w) << setfill('.') << left << name;
}

//scores_t
scores_t::scores_t(){
	mean = 0.0;
}

void scores_t::insert(int value){
	scores.push_back(value);
}

void scores_t::insert_done(){
	if(scores.size() == 0)
		return;
	float sum = accumulate(scores.begin(), scores.end() , 0);
	mean = sum/scores.size();
}

void scores_t::print(){
	cout << right << setfill(' ');
	for(unsigned int i = 0; i < scores.size(); i++)
		cout << " " << setw(2) << scores[i];
	cout << " : " <<fixed << setprecision(1) << mean << endl;
}



int main(int argc, char **argv) {
	//  commandline parsing
	// argv[1]: W (width of name field)
	// argv[2]: filename.txt

	if(argc < 3){
		cerr << "Expected width and filename\n";
		return -1;
	}

	int w = atoi(argv[1]);
	string file = argv[2];

	//open filename.txt
	ifstream fin (file.c_str());
	if (!fin){
		cout << "Unable to open file\n";
		return 1;
	}

	map<name_t,scores_t> NS;
	map<name_t,scores_t>::iterator it;

	string line;
	while(  getline(fin,line)  ){
		istringstream iss(line);
		string first, last;
		iss >> first;
		iss >> last;
		name_t name(first,last);
		
		scores_t scores;
		int grade;
		while(iss >> grade)
			scores.insert(grade);
		scores.insert_done();
		//only insert if the name is unique 
		it = NS.find(name);
		if(it == NS.end()) 
			NS.insert( make_pair(name,scores) );
	}
		fin.close();

	for(it = NS.begin(); it != NS.end(); it++){
		it->first.print(w+3);
		it->second.print();
	}
	return 0;
}

/*
   while (more data in file) {
   add first and lastname to name_t object

   while (more scores) {
   insert score into scores_t object
   have insert_done calculate mean score

   create and insert (name_t,scores_t) pair into NS map
   }

   close filename.txt

   while (NP map iterator loop) {
   print name
   print scores
   }
   }
   */
