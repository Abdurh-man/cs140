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
		friend class namescores_t;
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
		friend class namescores_t;
		vector<int> scores;
		float mean;
};

class namescores_t {
	public:
		//constructor(s);
		namescores_t();
		namescores_t(const name_t &, const scores_t &);

		bool operator<(const namescores_t&) const;
		// needed to use find() == end()
		bool operator==(const namescores_t&) const;

		void print_scores();
		void print_name(int w = 0);

	private:
		name_t n;
		scores_t s;
};

namescores_t::namescores_t(const name_t & name, const scores_t & score){
	n = name;
	s = score;
}

bool namescores_t::operator<(const namescores_t & rhs) const{
	if(this->s.mean != rhs.s.mean)
		return (this->s.mean < rhs.s.mean);
	//return(rhs.n < this->n);
	return (!(this->n < rhs.n));
}

bool namescores_t::operator==(const namescores_t & rhs) const{
	return(this->n.name == rhs.n.name && this->s.mean == rhs.s.mean);
}

void namescores_t::print_scores(){
	s.print();
}

void namescores_t::print_name(int w){
	n.print(w);	
}

//name_t
name_t::name_t(){
	name = " ";
}

name_t::name_t(const string& first, const string& last){
	name = last + ", " + first + " ";
}

bool name_t::operator<(const name_t& rhs) const{
	return(name < rhs.name);
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

	if(argc < 4){
		cerr << "Expected width, number of people, and filename\n";
		return -1;
	}

	int w = atoi(argv[1]);
	int k = atoi(argv[2]);
	string file = argv[3];

	//open filename.txt
	ifstream fin (file.c_str());
	if (!fin){
		cout << "Unable to open file\n";
		return 1;
	}

	vector<namescores_t> NS;
	string line, first, last;

	while(  getline(fin,line)  ){
		istringstream iss(line);
		iss >> first;
		iss >> last;
		name_t name(first,last);

		scores_t scores;
		int grade;
		while(iss >> grade)
			scores.insert(grade);
		scores.insert_done();

		namescores_t namescores(name,scores);
		if(find(NS.begin(), NS.end(), namescores) == NS.end())
			NS.push_back(namescores);
	}
	fin.close();

	make_heap (NS.begin(),NS.end());
	for(int i = 0; i < k && !NS.empty(); i++){
		NS[0].print_name(w+3);
		NS[0].print_scores();

		//pop heap
		pop_heap(NS.begin(),NS.end());
		NS.pop_back();
	}
	return 0;
}
