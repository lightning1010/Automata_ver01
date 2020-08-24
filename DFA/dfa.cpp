#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
using namespace std;

class DFA {
public:
	vector< vector<string> > data;
	map<string, vector<string> > instruction_set;
	map<char, int> symbols;
	string fs, str, start;
	vector<string> state_output;

	DFA(string input_string) {
		// Acts(Các hoạt động) as main operator of program. All functionality
		// is wrapped(gói) into a class to allow access of class
		// variables to simplify read/write operations and
		// reduce the cost of copying potentially(tiềm năng) large data 
		// structures.

		str = input_string;
		//cout << "input_string : " << input_string << " #(c++_format)" << endl;
		parseFile();
		construct();
		printf("%s\n", dfa_recursive(0, start) ? "Accepted" : "Denied");
	}

	void parseFile() {
		// Reads the config file from stdin to construct the rules of our DFA.
		// Sample config can be found in template.txt

		//cout << "####################### parseFile() " << endl;
		//cout << "Reads the config file from stdin to construct the rules of our DFA." << endl;
		//cout << "Sample config can be found in template.txt " << endl;

		vector<string> input;
		istringstream iss;
		string line, buffer;
		int size;

		// Parse header line
		getline(cin, line);
		//cout << "################ Parse header line : " << endl;
		//cout << "################ line : " << line << endl;
		iss.str(line);
		iss >> start; // Read start state
		//cout << "################ start : " << start << endl;
		// Add state into variable to print out 
		state_output.push_back(start);

		iss >> fs; // Read final state
		//cout << "################ fs : " << fs << endl;

		//cout << "################ Read in symbols : " << endl;
		while (iss >> buffer) {
			// Read in symbols (Ex: a , b )
			//cout << "################ buffer : " << buffer << endl;
			input.push_back(buffer);
		}
		size = input.size() + 1;
		data.push_back(input);

		// Get state instructions
		//cout << "################ Get state instructions : " << endl;
		while (getline(cin, line)) {
			//cout << "################ line : " << line << endl;
			input.resize(0);
			iss.clear();
			iss.str(line);
			while (iss >> buffer) {
				//cout << "################ buffer : " << buffer << endl;
				input.push_back(buffer);
			}
			if (input.size() != size) { fprintf(stderr, "Each symbol must have a state (found %d, expected %d)\n", input.size(), size); exit(0); }
			data.push_back(input);
		}
	}

	void construct() {
		// Creates needed links in order to make template more flexible(linh hoạt),
		// allowing for use of strings as states, as opposed(trái ngược) to integers.
		// This makes the state file more readable and potentially more
		// flexible.

		vector<string> instruction;
		int i;
		string key;

		// Convert Symbols ( Chuyển đổi ký hiệu )	# vector< vector<string> > data;
		//cout << "################ Convert Symbols  " << endl;
		//cout << "######### data[0].size() = " << data[0].size() << endl;
		for (i = 0; i < data[0].size(); i++) {
			symbols[data[0][i][0]] = i; // First letter of the string ( Chữ cái đầu tiên của chuỗi )	# map<char, int> symbols;
			//cout << "######### data[0][" << i << "][0] = " << data[0][i][0] << endl;
		}

		// Key instruction sets						# map<string, vector<string> > instruction_set;
		//cout << "################ Key instruction sets  " << endl;
		//cout << "######### data.size() : " << data.size() << endl;
		for (i = 1; i < data.size(); i++) {
			key = data[i][0];
			instruction_set[key] = data[i];
			//cout << "######### key : " << key << endl;
			//cout << "######### data[" << i << "][0] : " << data[i][0] << endl;
			//cout << "######### data[" << i << "][1] : " << data[i][1] << endl;
			//cout << "######### data[" << i << "][2] : " << data[i][2] << endl;
			//cout << "######### data[" << i << "][2][0] : " << data[i][2][0] << endl;
			//cout << "######### data[" << i << "][2][1] : " << data[i][2][1] << endl;
			//cout << "######### data[" << i << "][2][1] : " << data[i][2][2] << endl;
		}
	}

	void printData() {
		// Helper function for debugging - prints contents of data vector.
		int i, j;
		for (i = 0; i < data.size(); i++) {
			for (j = 0; j < data[i].size(); j++) {
				printf("%s ", data[i][j].c_str());
			}
			printf("\n");
		}
	}

	void printState() {
		// Range of DFA states passing through
		cout << "Range of DFA states passing through : ";
		for (int i = 0; i < state_output.size(); i++)
		{
			if (i != str.length()) {
				cout << state_output[i] << " --" << str[i] << "--> ";
			}
			else {
				cout << state_output[i] << endl;
			}

		}
	}

	bool dfa_recursive(int i, string state) {
		// Recursive algorithm which follows instructions for the lifetime
		// of the input string. Easily convertable to interative(tương tác) structure,
		// but recursion made more intuitive(trực quan) sense. Made to also practice
		// recursion.

		bool rv;
		int symbol_i;
		vector<string> instructions;
		string newstate;

		// Base case, exit out.
		if (i == str.size()) { return state == fs; }

		// Find and execute next state
		//cout << "################ dfa_recursive. Find and execute next state  " << endl;
		symbol_i = symbols[str[i]];
		//cout << "######### str[" << i << "] : " << str[i] << endl;
		//cout << "######### symbol_" << i << " : " << symbol_i << endl;
		instructions = instruction_set[state];
		//cout << "######### instruction_set[state][0] : " << instruction_set[state][0] << endl;
		//cout << "######### instruction_set[state][1] : " << instruction_set[state][1] << endl;
		//cout << "######### instruction_set[state][2] : " << instruction_set[state][2] << endl;
		//cout << "####################### instructions[0] : " << instructions[0] << endl;
		//cout << "####################### instructions[1] : " << instructions[1] << endl;
		//cout << "####################### instructions[2] : " << instructions[2] << endl;
		newstate = instructions[symbol_i + 1];
		//cout << "######### newstate : " << instructions[symbol_i + 1] << endl;
		state_output.push_back(newstate);

		return dfa_recursive(i + 1, newstate);
	}
};

int main(int argc, char** argv) {
	if (argc != 2) { fprintf(stderr, "usage dfs test_string < dfs_δ\n"); exit(0); }

	// Initialize DFA class, where all of the logic incurs. ( Khởi tạo lớp DFA, trong đó tất cả các logic phát sinh. )
	//cout << "################ Initialize DFA class, where all of the logic incurs." << endl;
	DFA *dfa = new DFA(argv[1]);
	//dfa->printData();
	dfa->printState();
}