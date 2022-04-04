#include<iostream>

using namespace std;

void encode(string& word,int shift){
// the index is assgined her and increment in the loop and used in the loops condition
int i = 0;
// gets c the first value of word so you can have something to start the change
char c = word[0];

// run through the characte array word until u get the null value
while(word[i] != '\0'){
	// only letters should be changed
	if(isalpha(c)){
		
		// sees if c is shifted if it would take it out a-z 
		if(islower(c) && (c+ shift) > 'z')
		// subtracts the difference between a and z 
			c -= 26;
		
		else if(isupper(c) && (c+ shift) > 'Z')
		// subtracts the difference between A and Z 
			c -= 26;
		
		c += shift;

		}	
	// changes the first character in the word
	word[i] = c;
	
	// this is done after c is assigned back to word so c gets assigned back in the correct address
	i++;
	// asssigns the 2nd character and starts the process again
	c = word[i];

	}
}

// word is changed by refrence meaning that word is minpulated in the function and changed
void decode(string& word ,int shift){ 

int i = 0;
// gets c the first value of word
char c = word[0];
// changes ascii to char
while(word[i] != '\0'){
	if(isalpha(c)){
		
		if(islower(c) && (c-shift) < 'a')
			c += 26;
		else if(isupper(c) && (c-shift) < 'A')
			c += 26;

		c -= shift;
	}	
	word[i] = c;
	i++;
	c = word[i];
	}
}

int main(int argc, char* argv[]){

	if(argc != 3 ){
		cerr << "WRONG COMMAND" << endl;
		return 1;}

	string code = argv[1];
	// gets the address of shift
	char *temp = argv[2];
	// gets ascii value of shift
	int shift = (int)(*temp);
	// subtract shift by 48 cause 0 starts at 48 
	shift -= 48;

	// checks the second value of argv if there is a second value end
	// if the operation value is not 0-9 end
	if((*(temp+1) != '\0') || !(shift >= 0 && shift <= 9 )){
		cerr << "WRONG SHIFT OPPERATION" << endl;
		return 1;}

	// (!(true || true)) makes it only have to go off one or the other 
	// (true || !( true || true)) 
	// rather than 
	// (true || !true || !true) because if -encode is given then its wrong cause -decode is not given 
	if (argc > 3 || (!(code == "-decode" || code == "-encode")) || !(shift >= 0 && shift <= 9 )){
		cerr << "WRONG COMMAND" << endl;
		return 1;}

	else{
		// keeps promting the user for inputs until terminated
		while(!cin.eof()){
		string word;
		// gets the line and puts it in word
		getline(cin,word);
		
	
			if(code == "-encode")
				encode(word,shift);

			if(code == "-decode")
				decode(word,shift);
			// notice how its cout << word not decode or encode 
			// word is  changed in whatever function is called then updated here 
			cout << word;
			cout<< endl;
		}
	}
	return 0;}
