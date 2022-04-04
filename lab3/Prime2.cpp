#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

class isprime {
  public:
    isprime();
	bool operator()(int);

  private:
    void magic(int);
	bool is_prime(int);
	vector<int>cache;
};

isprime::isprime(){
// cache is now [2,3]
	cache.push_back(2);
	cache.push_back(3);
}

bool isprime::operator()(int number){
	magic(number);
	// if it finds number it returns an iterator that points directly to number's location
	// if find doesnt find the number it returns an itartor to the end
	// so setting find to find != end() since the find retunrs the iterator that points directly to numebr's location 
	if(find(cache.begin(), cache.end(), number) != cache.end())
		return true;
	return false;
}
// retuns true if the numebr is prime
bool isprime::is_prime(int number){
	int pri = 1;
	int p_sqrt = sqrt(number) + 1;
	while(++pri < p_sqrt){
		if(number % pri == 0)
			return false;
	}
		return(1 < number);
}
// if the number is not found in cache and is prime then add it to cahce
void isprime::magic(int number){
	// add one so the last value is not added twice
	for(int i = cache.back() + 1; i <= number; i++){
		if(is_prime(i))
			cache.push_back(i);
	}
}

int main(){
	isprime pcheck;
	int number;

	while (!cin.eof()) {
		cin >> number;
		// number is prime cout 
		if (pcheck(number))
			cout << number << " is a prime number" << endl;
	}
}
