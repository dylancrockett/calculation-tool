/*	Some Notes:
		- Fixed the issue with the file only output not working properly, was using cls which is very laggy - replaced it with a simple cout.
		- A large number of pointers should be replaced with references but I used pointers to show knowlege of use as well as a learning experience
*/
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include "ConsoleFunctions.h"
#include "Equation.h"
#include "Read.h"
#include "Write.h"
#include "MainFunctions.h"
#include "Menu.h"

using namespace std;

//setting variables, they are assigned a value at the start of the program and read from the settings.txt file
string input_folder;
string output_folder;
bool debug;
string user;

//create the menus used by the program
Menu main_menu("Main Menu", { {"Solve Equation File","Create Equation File","Solve Single Equation"}, {"Solve a file that contains properly formated equations.", "Create a file that is populated with randomized equations.","Solve a single equation entered by the user."}, {"equation_solve","equation_create","equation_single"} });
Menu equation_solve("Solve Equation File", { {"Console Only Output","File Only Output","File & Console Output"}, {"Only output solved equations to the console.","Only output solved equations to a created file.","Both output solved equations to a new file and the console."}, {"equation_solve_console","equation_solve_file","equation_solve_both"} }, &main_menu);
Menu equation_create("Create Equation File", { {"Simple Equation File", "Complex Equation File"}, {"Create a file containing equations that only have one step. (ex. 4* 2 =)","Create a file containing equations that have multiple steps. (ex. (5 * 2) / 10 =)"}, {"equation_create_simple","equation_create_complex"} }, &main_menu);

//by default the chosen menu is the main_menu
string input = "main_menu";

//forward declare the functions used in the main switch statement
//the purpose of these functions is to reduce the amount of code in main as well as make it clear what code each selection runs
void equation_solve_console(string & input);
void equation_solve_file(string & input);
void equation_solve_both(string & input);
void equation_create_simple(string & input);
void equation_create_complex(string & input);
void equation_single(string & input);

int main() {
	//set random seed
	srand((unsigned)time(NULL));

	//grab the settings
	getSettings(&input_folder, &output_folder, &debug, &user);

	//welcome the user once
	color('r');  cout << "Welcome " << user << " to the Calculation Tool" << endl << endl;

	//this while loop runs the program. exited when the main menu is exited
	while (true) {
		/*
			This switch statement controlls the menus as well as what will be executed by the program when the user makes a choice, this switch statement takes strings as 
			its input and then hashes them to an integer to resolve them, making choices easier to follow in the program but also granting switch function practicality 
			over tons of if and else if statements
		*/
		switch (s_hash(input)) {
			case 3800383818:
				//case "main_menu"
				//display the main menu menu and get the user input
				input = main_menu.display();

				break;
			case 3183626367:
				//case "equation_solve"
				//display the equation solve menu and get the user input
				input = equation_solve.display();

				break;
			case 2775445745:
				//case "equation_solve_console"
				equation_solve_console(input);

				break;
			case 3382657886:
				//case "equation_solve_file"
				equation_solve_file(input);

				break;
			case 3382520939:
				//case "equation_solve_both"
				equation_solve_both(input);

				break;
			case 1357572650:
				//case "equation_create"
				input = equation_create.display();

				break;
			case 2043944915:
				//case "equation_create_simple"
				equation_create_simple(input);

				break;
			case 4071834209:
				//case "equation_create_complex"
				equation_create_complex(input);

				break;
			case 1973395352:
				//selection "equation_single"
				equation_single(input);

				break;
			default:
				//debug stuff - gives hash so corrections are possible when a new selection is made or an old one is made
				color('r');
				cout << "If you see this something has gone wrong! This menu is only meant for debug purposes." << endl;
				cout << "Desired Menu: " << input << " | Hash: " << s_hash(input) << endl;
				pause();

				//go back to main menu if something has gone wrong
				input = "main_menu";
		}

		//if the returned input is nothing then break the loop
		if (input == "") {
			break;
		}
	}
	//end of program
	return 0;
}

void equation_solve_console(string & input) {
	//read the file that the user directs us to
	Read in(userInput("Enter desired file name for solving (leave out .txt)"), input_folder);

	//solve the equations within the file and print the solved equations
	solveEquations(&in.contents, true, NULL, NULL, false, debug);

	//go back to where we came from
	input = "equation_solve";
}

void equation_solve_file(string & input) {
	//get file name
	string f_n = userInput("Enter desired file name for solving (leave out .txt)");

	//read that file
	Read in(f_n, input_folder);

	//add solved suffix
	f_n = f_n + "_solved";

	//solve the equations in that file
	solveEquations(&in.contents, false, &f_n, &output_folder, true);

	//go back
	input = "equation_solve";
}

void equation_solve_both(string & input) {
	//get file name
	string f_n = userInput("Enter desired file name for solving (leave out .txt)");

	//read that file
	Read in(f_n, input_folder);

	//add solved suffix
	f_n = f_n + "_solved";

	//solve the equations in that file
	solveEquations(&in.contents, true, &f_n, &output_folder, true, debug);

	//go back
	input = "equation_solve";
}

void equation_create_simple(string & input) {
	//get user input
	int a = stoi(userInput("Enter how many equations you want the file to contain (must be an integer)"));
	string c = userInput("Enter the desired name of the file that will contain the equations");

	//correct inputs if they are invalid
	if (a < 0) {
		a = 10;
	}

	//create the equations
	vector<string> equations = createEquations(a, 0, 0, debug);

	//create a Write object
	Write out({""}, c, input_folder);

	//output the contents of equations to the new file
	out.output(true, &equations);

	input = "equation_create";
}

void equation_create_complex(string & input) {
	//get user input
	int a = stoi(userInput("Enter how many equations you want the file to contain (must be an integer)"));
	int b = stoi(userInput("Enter the difficulty level you want the expressions to be generated with (0 is no the same as simple equations,  maximum complexity is 25)"));
	string c = userInput("Enter the desired name of the file that will contain the equations");

	//correct inputs if they are invalid
	if (a < 0) {
		a = 10;
	}
	if (b > 25 || b < 0) {
		b = 10;
	}

	//create the equations
	vector<string> equations = createEquations(a, 1, b, debug);

	//create a Write object
	Write out({""}, c, input_folder);

	//output the contents of equations to the new file
	out.output(true, &equations);

	input = "equation_create";
}

void equation_single(string & input) {
	vector<string> in = {"", userInput("Enter the equation you want to be solved (ex. '1 + 1 =')") };

	//solve the equations within the file and print the solved equations
	solveEquations(&in, true, NULL, NULL, false, true);

	input = "main_menu";
}