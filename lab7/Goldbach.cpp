#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

class prime_partition {
	public:
		// constructor
		prime_partition();
		// operator(int)
		void operator()(int);
	private:
		void create_pset();
		bool isprime(int);
		// compute_partitions
		void compute_partitions(int = 0);
		void print_partitions();
		// member data
		set<int> pset; // hold prime numbers
		unsigned int max_terms; // number of terms
		int given_val;
		vector< vector<int> >partitions;
		vector<int>numbers;
};

bool prime_partition::isprime(int set){
	int pri = 1;
	int p_sqrt = sqrt(set) + 1;
	while(++pri <= p_sqrt){
		if(set % pri == 0)
			return false;
	}
	return true;
}

void prime_partition::create_pset(){
	for(int i = 2; i < 2000 ; i++){
		if(isprime(i)){
			pset.insert(i);
		}
	}
}

prime_partition::prime_partition(){
	pset.insert(2);
	create_pset();	
}

void prime_partition::operator()(int number){
	if(number < 2 || number >= 2000)
		return;

	given_val= number;

	max_terms = (number%2 == 0) ? 2 : 3;
	numbers.clear();
	partitions.clear();
	compute_partitions();
	print_partitions();
}

void prime_partition::print_partitions(){
	for(unsigned int i = 0; i < partitions.size(); i++){
		for(unsigned int j = 0; j < partitions[i].size();j++){
			cout << partitions[i][j] << ' ';
		}
		cout << endl;
	}
}

void prime_partition::compute_partitions(int sum){
	// that means only one term needed for answer
	if(sum == given_val && numbers.size() <= max_terms){
		partitions.push_back(numbers);
		// numbers is a private vector in class prime_partition
		if(numbers.size() < max_terms){
			max_terms = numbers.size();
			partitions.clear();
			partitions.push_back(numbers);
			return;
		}
	}
	//pset_max calculated in find_max()
	if(sum > given_val || numbers.size() > max_terms){
		return;
	}

	set<int>::iterator lower = pset.begin();
	set<int>::iterator upper;
	set<int>::iterator move;
	// if its empty upper equals to last value in pset
	if( !numbers.size() )
		upper = pset.upper_bound(given_val);
	// else its equal to the last number in numbers
	else
		upper = pset.upper_bound(numbers[numbers.size()-1]);

	for(move = lower; move != upper; move++){
		numbers.push_back(*move);	
		compute_partitions( sum+(*move) );
		numbers.pop_back();
	}
}

int main(int argc, char *argv[]){
	prime_partition goldbach;

	int number;
	while (1) {
		cout << "number = ";
		cin >> number;
		if (cin.eof())
			break;

		goldbach(number);
	}

	cout << "\n";
}
