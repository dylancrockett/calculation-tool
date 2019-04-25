#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include "Equation.h"
#include "MainFunctions.h"
#include "Read.h"
#include "Write.h"
#include "ConsoleFunctions.h"

using namespace std;

//forward declare
char randomSymbol();
string eqA(int complexity, bool first = false);
string eqB(int complexity);

//return a vector full of solved equations, takes a Read file as its input
void solveEquations(vector<string> * input, bool console_output, string * file_name, string * output_folder_name, bool do_output, bool debug) {
	//get the start time of solving
	clock_t task_start_time = clock();
	clock_t solve_start_time;
	long total_solve_time = 0;

	//will store the output
	vector<string> output;
	
	//if console output is true then output
	if (console_output) {
		color('b');  cout << "Solved Equations:" << endl;
	}

	//for each line of the file run this for loop
	for (int i = 1; input->size() > i; i++) {
		//create an equation with the line
		Equation temp(input->at(i));

		//console output
		if (console_output) {
			if (debug) {
				cout << endl << endl;
			}
			color('r'); cout << "Problem #" << (i) << ": ";
		}

		//start the clock
		solve_start_time = clock();

		//calculate the solution to the equation
		temp.calculate(debug);

		//add to the total time taken
		total_solve_time += clock() - solve_start_time;

		//if console output is true then output
		if (console_output) {
			if (debug) {
				color('p'); cout << "Final Solution: ";
			}
			color('c');  cout << temp.equation << " "; color('y'); cout << temp.solution << endl;
		}
		else {
			color('r'); cout << "Currently Solving Problem #" << (i) << "" << endl;
			//dont just give a blank screen, give something useful!
			//color('c'); cout << "Task Runtime: "; color('y'); cout << ((double)(clock() - task_start_time) / CLOCKS_PER_SEC) << "s" << endl; clear();
		}

		//add to the output vector with the input line + the solution
		output.push_back(temp.equation + " " + temp.solution);
	}

	clock_t output_start_time;

	//output a file if function is told to
	if (do_output) {
		output_start_time = clock();

		//create the output file
		Write out({""}, *file_name, *output_folder_name);

		out.output(true, &output);
	}

	//output information about time taken to calculate and output file
	color('r'); cout << endl << "Time Statistics:" << endl;
	color('c'); cout << "Total Task Runtime: "; color('y'); cout << ((double)(clock() - task_start_time) / CLOCKS_PER_SEC) << "s" << endl;
	color('c'); cout << "Average Time to Solve per Equation: "; color('y'); cout << ((double)total_solve_time / CLOCKS_PER_SEC / input->size() * 1000) << "ms" << endl;
	//dont work good: color('c'); cout << "Average Clock Cycles  to Solve per Equation: "; color('y'); cout << ((double)total_solve_time / input->size()) << "" << endl;
	if (do_output) {
		color('c'); cout << "Total Time to Output File: "; color('y'); cout << ((double)(clock() - output_start_time) / CLOCKS_PER_SEC) << "s" << endl << endl;
	}
	color('r'); pause(); clear();
}

//create simple or complex equations | mode = 0 is simple | mode = 1 is complex | equations is the # of equations returned in the vector
vector<string> createEquations(int equations, int mode, int difficulty, bool debug) {
	vector<string> created_equations;
	int c = 0;

	//simple mode
	if (mode <= 0) {
		for (int i = equations; i > 0; i--) {
			created_equations.push_back(eqA(difficulty) + " =");

			if (debug) {
				color('r'); cout << "Created Simple Equation #" << c + 1 << ": "; color('c'); cout << created_equations[c] << endl;
				c++;
			}
		}
	}

	//complex mode
	if (mode >= 1) {
		for (int i = equations; i > 0; i--) {
			created_equations.push_back(eqA(difficulty) + " =");

			if (debug) {
				color('r'); cout << "Created Complex Equation #" << c + 1 << ": "; color('c'); cout << created_equations[c] << endl;
				c++;
			}
		}
	}
	
	if (debug) {
		color('r');  cout << endl << "Sucsessfully Created " << created_equations.size() << " Equations!" << endl << endl;
		pause(); clear();
	}

	return created_equations;
}

//creates a basic equation | the higher complexity is the higher chance for sub functions, 0 for no complexity | first indicates if it is the origin equation
string eqA(int complexity, bool first) {
	string equation = eqB(complexity) + " " + randomSymbol() + " " + eqB(complexity);

	return equation;
}

//will return a numer or another equation based on the randomly generated number
string eqB(int complexity) {
	int num = random(1, (20 + complexity));

	//if the random number is greater than 20 then return another equation in parenthases rather than a number
	if (num > 20) {
		return "(" + eqA(complexity) + ")";
	}

	return to_string(num);
}

//return a random symbol
char randomSymbol() {
	switch (random(1, 4)) {
		case 1:
			return '+';
		case 2:
			return '-';
		case 3:
			return '*';
		case 4:
			return '/';
	}
}

//this function will grab settings from the settings.txt file and apply them to the referenced variables
void getSettings(string * input_file_name, string * output_file_name, bool * debug_setting, string * user_name) {
	//create vectors
	vector<string> temp, setting, input;
	
	//read the settings file
	Read file("settings", "");

	//output file contents to the temp vector
	temp = file.contents;

	//temp variables for parsing
	string hold_1 = "";
	string hold_2 = "";

	/* Example How the Following Loop Functions
		file line: "input file name=input"
		the function will seperate the line into the two following sections
			-setting: "input file name"
			-input: "input"
		the function will push these to the respective vectors, so later parsing can be done to set the settings in the main.cpp
		this is expandable for more settings if the need arises in the future
	*/
	
	//cycle through each line, once you hit a '=' store the first part of the text as the "setting" then everything after that as the "input"
	for (int i = 0; i < temp.size(); i++) {
		hold_1 = temp[i];
		for (int j = 0; j < hold_1.size(); j++) {
			if (hold_1[j] == '=') {
				//once you hit a '=' then store the first part as a setting
				setting.push_back(hold_2);

				hold_2 = "";
			}
			else {
				hold_2 = hold_2 + hold_1[j];
			}
		}
		//once done reading the line add everything past the '=' as the input
		//also make sure if the loop tries to push a blank that it cant
		if (!(hold_2 == "")) {
			input.push_back(hold_2);
		}

		hold_2 = "";
	}

	//parse through the setting vector, once you find a setting that matches the string then assign that setting to the respective pointer wich will change the variable which is referenced
	for (int i = 0; i < setting.size(); i++) {
		//set the input file name setting
		if (setting[i] == "input file name") {
			input_file_name->assign(input[i]);
		} 
		
		//set the output file name setting
		if (setting[i] == "output file name") {
			output_file_name->assign(input[i]);
		}

		//set the output file name setting
		if (setting[i] == "user name") {
			user_name->assign(input[i]);
		}

		//set the debug setting
		if (setting[i] == "debug output") {
			if (input[i] == "true") {
				*debug_setting = true;
			} else if(input[i] == "false") {
				*debug_setting = false;
			} else {
				*debug_setting = true;
			}
		}
	}

	//debug
	if (*debug_setting) {
		cout << "Settings: " << endl;
		for (int i = 0; i < setting.size(); i++) {
			color('r'); cout << setting[i] << ": "; color('b'); cout << input[i] << endl;
		}

		//pause and clear the screen once unpaused
		pause();
		clear();
	}
}

//get user input by asking a question
string userInput(string question) {
	string input;
	color('b');  cout << question + ": "; color('r'); getline(std::cin >> ws, input); clear();
	return input;
}

//clean a float to remove extra 0s and .s 
string cleanFloat(float input) {
	//convert the float to a string 
	string numb = to_string(input);

	//remove trailing zeroes and dots from the string
	numb.erase(numb.find_last_not_of('0') + 1, string::npos);
	numb.erase(numb.find_last_not_of('.') + 1, string::npos);

	//return the value as a string
	return numb;
}

//convert a string into an integer for use in switch statements
unsigned long s_hash(string str) {
	unsigned long hash = 2481;
	for (size_t i = 0; i < str.size(); ++i)
		hash = 33 * hash + (unsigned char)str[i];
	return hash;
}

//generate random integer (generic)
int random(int min, int max) {
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
