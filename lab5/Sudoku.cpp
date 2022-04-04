#include <sys/time.h>

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <utility>
using namespace std;

const char *units[] = { "sec", "msec", "usec" };

class omega {
	public:
		omega();
		float get_sec();

	private:
		long Tinit;
		long Tmark;
};

omega::omega() {
	struct timeval T;
	gettimeofday(&T, NULL);

	Tinit = 1000000*T.tv_sec + T.tv_usec;
}

float omega::get_sec() {
	struct timeval T;
	gettimeofday(&T, NULL);

	Tmark = 1000000*T.tv_sec + T.tv_usec;

	return (float)(Tmark-Tinit)/1000000.0;
}

string elapsed(float duration, int i = 0) {	
	ostringstream oss;
	oss <<  endl<< "Time: " << fixed << setprecision(2) << duration << ' ' <<units[i] 
		<< " (" << setprecision(6) << duration << ' ' <<units[i] <<")\n\n";
	// if base case return solution

	if(duration < 0.1)	
		return elapsed(duration * 1000, i + 1);
	
	return oss.str();
}

class sudoku {
	public:
		sudoku();

		void solve();

		void read(const char *);
		void write(const char *);
		void write(const char *, const char *);

	private:
		bool solve(vector< pair<int,int> >&, unsigned int c);
		vector<int>valid_values(int,int);
		// sees if sudoku is filled with unique no-zero values
		bool solution();
		// various support functions 
		bool error_check_value(bool);
		bool error_check_uniqueness();
		// helper check functions
		bool check_row(int, int);
		bool check_col(int, int);
		bool check_square(int, int, int);
	
		void display();

		int game[9][9];
};

sudoku::sudoku() { 
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++)
			game[i][j] = 0;
	}
}

void sudoku::solve() {
	cout << "SOLVE\n";
	int v = 0;

	vector< pair <int,int> > cells;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++){
			v = game[i][j];
			if( v == 0 )
				cells.push_back(make_pair(i,j));
		}
	}

	// call recursive solve function
	if ( solve(cells, 0) )
		display();
	// error check data values and uniqueness exit if errors detected
	if( error_check_value(false) || error_check_uniqueness())
		exit(0);
}

bool sudoku::error_check_value(bool read){
	bool wrong = false;
	int v = 0;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			v = game[i][j];
			if(read){
				if(v < 0 || v > 9){
					cerr << "cell " << i << ' ' << j << ": out-of-bounds data value " << v << endl;
					wrong = true;
				}
			}
			else{
				if(v < 1 || v > 9){
					cerr << "cell " << i << ' ' << j << ": out-of-bounds data value " << v << endl;
					wrong = true;
				}
			}
		}
	}
	return wrong;
}

bool sudoku::error_check_uniqueness(){	
	bool wrong = false;
	int v = 0;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			v = game[i][j];
			if(v){
				if( !(check_row(i,v) && check_col(j,v) && check_square(i,j,v)) ){
					cerr << "cell " << i << " " << j <<": non-unique value " << v << endl;
					wrong = true;
				}		
			}
		}		
	}
	return wrong;
}

bool sudoku::check_row(int r, int v){
	int check = 0;
	for(int j = 0; j < 9; j++){
		if(game[r][j] == v)
			check++;
	}
	// has to find v more than once
	if(check > 1)
		return false;

	return true;
}

bool sudoku::check_col(int c, int v){
	int check = 0;	
	for(int i = 0; i < 9; i++){
		if(game[i][c] == v)
			check++;
	}
	// has to find v more than once
	if(check > 1)
		return false;

	return true;
}

bool sudoku::check_square(int r, int c, int v){
	// starting postion for r and c
	// let say given 5 and 5
	// 5/3 = 1 | 1 * 3 = 3
	// r = 3 and c = 3
	
	int check = 0;
	r = (r/3)*3;
	c = (c/3)*3;
		
	for(int i = r; i < r + 3; i++){
		for(int j = c; j < c + 3; j++){
			if(game[i][j] == v)
				check++;
		}
	}
	if(check > 1) 
		return false;

	return true;
}



vector<int>sudoku::valid_values(int r, int c){
			vector<int>temp;
			temp.clear();
			for(int v = 1; v < 10; v++){
				game[r][c] = v;
				if(check_row(r, v) && check_col(c, v) && check_square(r, c, v))
					temp.push_back(v);
			}
			game[r][c] = 0;
			return temp;
		}


void sudoku::read(const char *fname) {	
	int line = 1;
	bool wrong = false;

	cout << "READ\n";

	ifstream fin(fname);

	int i, j, v;

	while (fin >> i >> j >> v) {
		// error check grid indices
		if( (i < 0 || i > 8) || (j < 0 || j > 8) ){
			cerr << "line " << line << ": " << i << ' '<< j << ' ' << v << " out-of-bounds grid index\n";
			wrong = true;
		}
		line++;
		game[i][j] = v;
	}
	
	fin.close();

	// exit if bad grid indices
	if(wrong)
		exit(0);

	display();

	// error check data values
	if( error_check_value(true) )
		wrong = true;
	// error check uniqueness
	if( error_check_uniqueness() )
		wrong = true;

	// exit if errors detected
	if(wrong)
		exit(0);
}

void sudoku::write(const char *fname) {
	ofstream fout(fname);

	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (0 < game[i][j]) {
				fout << i << " "
					<< j << " "
					<< game[i][j] << "\n";
			}
		}
	}

	fout.close();
}

void sudoku::write(const char *fname, const char *addon) {
	int N1 = strlen(fname);
	int N2 = strlen(addon);

	char *n_fname = new char[N1+N2+2];

	// strip .txt suffix, then concatenate _addon.txt
	strncpy(n_fname, fname, N1-4);
	strcpy(n_fname+N1-4, "_");
	strcpy(n_fname+N1-3, addon);
	strcpy(n_fname+N1-3+N2, ".txt");

	write(n_fname);

	delete [] n_fname;
}

void sudoku::display() {
	cout << "| --------------------------- |\n";
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (j == 0) 
				cout << "| " << game[i][j];
			else if (j%3 == 0) 
				cout << " | " << game[i][j];
			else
				cout << "  " << game[i][j];
		}
		cout << " |\n";
		if (i%3 == 2)
			cout << "| --------------------------- |\n";
	}
}

bool sudoku::solve(vector< pair<int,int> >& cells, unsigned int c) {

	// if solution found, return solution-found
	if(c == cells.size())
		return true;
	
	int small_index = c ;	
	// largest amount of possible values at any index is 9
///*
	unsigned int index_smallest = 9;
	for(unsigned int low = c; low < cells.size(); low++){
		int r = cells[low].first;
		int c = cells[low].second;

		vector<int>temp = valid_values(r,c);	
		if(temp.size() == 0)
			return false;

		// sets i and j to the lowest value whereever it is in the vector
		// only overwrites if a smaller value found than the previous one
		if(temp.size() < index_smallest){
			index_smallest = temp.size(); 
			small_index = low;
		}
		temp.clear();
	}
//*/
	swap(cells[c], cells[small_index]);
	// set cell index (i,j)
	int i = cells[c].first;	
	int j = cells[c].second;
	
	// determine valid values 		
	vector<int>values = valid_values(i,j);	
	
	// if no valid values left, return road-to-nowhere
	if(values.size() == 0)
		return false;

	// iterate thru valid values 
	//   game[i][j] = next value
	for(unsigned int k = 0; k < values.size(); k++){
	//	cout << i << ' ' <<  j << "   " <<  values[k] << ' ' << values.size() << endl;
		game[i][j] = values[k];

		//  if solve(arguments) == solution-found, return solution-found
		if(solve(cells, c + 1) == true)
			return true;
		
	}

	// reset: game[i][j] = 0
	// return road-to-nowhere
	game[i][j] = 0;	
	return false;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));

	if ((argc != 3) ||
			(strcmp(argv[1], "-s") != 0) ||
			strstr(argv[argc-1], ".txt") == NULL) {
		cerr << "usage: Sudoku -s game.txt\n";
		exit(0);
	}

	omega timer;
	sudoku sudoku_game;

	float T0 = 0.0;
	float T1 = 0.0;

	if (strcmp(argv[1], "-s") == 0) {
		sudoku_game.read(argv[2]);

		T0 = timer.get_sec();
		sudoku_game.solve();
		T1 = timer.get_sec();

		sudoku_game.write(argv[2], "solved");
	}

	string elapsed_time = elapsed(T1-T0);
	//Time: 5.13 msec (0.005133 sec)
	// print string elapsed_time using two decimal places
	cout << elapsed_time;
	// print T1-T0 using six decimal places for comparison

}
