#include <string>
#include <iostream>
#include <math.h>
#include "ConsoleFunctions.h"
#include "Equation.h"

using namespace std;

bool checkForNonSubtraction(string equation);
string cleanNumb(string input);
bool checkForParenth(string * expression);
unsigned long long factorial(signed long long input);

Equation::Equation(const string eq) {
	setEquation(eq);
}

void Equation::setEquation(const string in) {
	equation = in;
}

void Equation::calculate(bool debug) {
	solution = doCalculate(equation, debug);
}

string Equation::doCalculate(string equation, bool debug) {
	/* Variables
		expression - will store the compressed and reduced equation, will be modified as the program simplifies the expression
		in_parenth - stores what the parser finds inside of parenthesis and then will be solved, then reset, and the proccess repeats
		function - will the be function tag, used to help cut the function correctly when it is reduced
		insert - the reduced number or equation that will take the place of a function or equation contaned within parenthesis
	*/
	string expression;
	string in_parenth = "";
	string function = "";
	string insert = "";

	//if for some reason a blank string is passed then return a blank string, it is here to prevent throwing exeptions
	if (equation == "") {
		return "";
	}

	//remove uneccessary spaces or symbols (" " & "=") and create the expression
	for (int i = 0; i < equation.length(); i++)
	{
		if (equation[i] != ' ' && equation[i] != '=') {
			expression += equation[i];
		}
	}

	//set i at the begining of the expression
	int i = expression.length() - 1;

	//this whole while process doesn't matter if the program doesnt have parenthesis (required for order of operations or functions)
	if (checkForParenth(&equation)) {
		//debug output
		if (debug) {
			color('p'); cout << endl << "Debug Output Start for Equation: "; color('c'); cout << equation << endl;
		}

		//the first do while loop will begin parsing from the front of the expression backwards, until it finds a "("
		do {
			if (i > 3) {
				//if the function is recognized as "sqrt(" then find the sqrt of the functions input
				if (expression[i - 4] == 's' && expression[i - 3] == 'q' && expression[i - 2] == 'r' && expression[i - 1] == 't' && expression[i] == '(') {
					//let the program know what function was found so it can cut it out properly
					function = "sqrt(";

					//grab what is inside the parenthesis
					findInParenth(&i, &expression, &in_parenth);

					//result of the square root of whatever is in the parenthesis used to be insert into the equation so it can be simplified
					insert = to_string(sqrt(stold(doCalculate(in_parenth))));

					//insert the solution into the equation where the original unsimplified expression was before
					insertSolution("Finding the Square Root of : ", &i, &expression, &in_parenth, &insert, &function, &debug);

					//go to the next iteration of the while loop, we have finished with this iteration, will start again from the top of the expression
					continue;
				}

				//if the function is recognized as "sqrt(" then find the sqrt of the functions input
				if (expression[i - 4] == 'f' && expression[i - 3] == 'a' && expression[i - 2] == 'c' && expression[i - 1] == 't' && expression[i] == '(') {
					//let the program know what function was found so it can cut it out properly
					function = "fact(";

					//grab what is inside the parenthesis
					findInParenth(&i, &expression, &in_parenth);

					//result of the factorial of whatever is in the parenthesis used to be insert into the equation so it can be simplified
					insert = to_string(factorial(stold(doCalculate(in_parenth))));

					//insert the solution into the equation where the original unsimplified expression was before
					insertSolution("Finding the Factorial of: ", &i, &expression, &in_parenth, &insert, &function, &debug);

					//go to the next iteration of the while loop, we have finished with this iteration, will start again from the top of the expression
					continue;
				}
			}

			if (i > 2) {
				if (expression[i - 3] == 'a' && expression[i - 2] == 'b' && expression[i - 1] == 's' && expression[i] == '(') {
					//let the program know what function was found so it can cut it out properly
					function = "abs(";

					//grab what is inside the parenthesis
					findInParenth(&i, &expression, &in_parenth);

					//result of the absolute value of whatever is in the parenthesis
					insert = to_string(abs(stold(doCalculate(in_parenth))));

					//insert the solution into the equation where the original unsimplified expression was before
					insertSolution("Finding the Absolute Value of : ", &i, &expression, &in_parenth, &insert, &function, &debug);

					//go to the next iteration of the while loop, we have finished with this iteration, will start again from the top of the expression
					continue;
				}
				
				if (expression[i - 3] == 'l' && expression[i - 2] == 'o' && expression[i - 1] == 'g' && expression[i] == '(') {
					//let the program know what function was found so it can cut it out properly
					function = "log(";

					//grab what is inside the parenthesis
					findInParenth(&i, &expression, &in_parenth);

					//result of the log base 10 of whatever is in the parenthesis
					insert = to_string(log10(stold(doCalculate(in_parenth))));

					//insert the solution into the equation where the original unsimplified expression was before
					insertSolution("Finding the Log Base 10 of : ", &i, &expression, &in_parenth, &insert, &function, &debug);

					//go to the next iteration of the while loop, we have finished with this iteration, will start again from the top of the expression
					continue;
				}
			}

			if (i > 1) {
				if (expression[i - 2] == 'l' && expression[i - 1] == 'n' && expression[i] == '(') {
					//let the program know what function was found so it can cut it out properly
					function = "ln(";

					//grab what is inside the parenthesis
					findInParenth(&i, &expression, &in_parenth);

					//result of the natural log of whatever is in the parenthesis
					insert = to_string(log(stold(doCalculate(in_parenth))));

					//insert the solution into the equation where the original unsimplified expression was before
					insertSolution("Finding the Natural Log of : ", &i, &expression, &in_parenth, &insert, &function, &debug);

					//go to the next iteration of the while loop, we have finished with this iteration, will start again from the top of the expression
					continue;
				}
			}

			//reset function
			function.clear();

			//once a "(" is found start the second parse
			if (expression[i] == '(') {
				//let the program know what function was found so it can cut it out properly
				function = "(";

				//grab what is inside the parenthesis
				findInParenth(&i, &expression, &in_parenth);

				//result of the square root of whatever is in the parenthesis used to be insert into the equation so it can be simplified
				insert = doCalculate(in_parenth);

				//insert the solution into the equation where the original unsimplified expression was before
				insertSolution("Simplifying the Equation: ", &i, &expression, &in_parenth, &insert, &function, &debug);

				//go to the next iteration of the while loop, we have finished with this iteration, will start again from the top of the expression
				continue;
			}

			//if no "(" is found then go to the next char in the string
			i--;
		} while (i >= 0);
		//once this loop finishes we can finaly solve the reduced expression
	}
	//now to the second part of the function

	//TODO add proper order of operations for a string such as '1 * 2 + 3', until then overuse parenthesis!

	//parse through the expression until you find a operator, do operators seperatly to follow the order of operations

	//do exponents fist
	for (int i = 0; i <= expression.length(); i++) {

		switch (expression[i]) {
		case '^':

			//return solution
			return cleanNumb(to_string(pow(stold(expression.substr(0, i)), stold(doCalculate(expression.substr(i + 1, expression.length() - i - 1))))));
		default:

			//nothin - if you are reading this I am suffering and making this has been pain, but its so much better than the old one
			break;
		}
	}

	//do multiplication and division second
	for (int i = 0; i <= expression.length(); i++) {

		switch (expression[i]) {
		case '*':

			//return the solution
			return cleanNumb(to_string(stold(expression.substr(0, i)) * stold(doCalculate(expression.substr(i + 1, expression.length() - i - 1)))));
		case '/':

			//return the solution
			return cleanNumb(to_string(stold(expression.substr(0, i)) / stold(doCalculate(expression.substr(i + 1, expression.length() - i - 1)))));;
		default:

			//nothin - if you are reading this I am suffering and making this has been pain, but its so much better than the old one
			break;
		}
	}

	//do addition and subtraction last
	for (int i = 0; i <= expression.length(); i++) {

		//use a switch to determine if the current char is one of the operators because switch statements are the best
		switch (expression[i]) {
		case '+':

			return cleanNumb(to_string(stold(expression.substr(0, i)) + stold(doCalculate(expression.substr(i + 1, expression.length() - i - 1)))));
		case '-':
			//if the - is in the fist position of the string it represents a negative number, not a subtraction sign, this prevents exeptions.
			if (!checkForNonSubtraction(expression)) {
				break;
			}

			//if the first check passes but there is still a negative sign in front then just pass the number through
			if (expression[0] == '-') {
				return expression;
			}

			//return the solution
			return cleanNumb(to_string(stold(expression.substr(0, i)) - stold(doCalculate(expression.substr(i + 1, expression.length() - i - 1)))));
		default:

			//do nothin
			break;
		}
	}

	//if there is no operator then the function is just passing an integer, so just pass it through without issue
	return cleanNumb(expression);
}

//finds what string is contained within the ending half of the parenthesis | this code has been moved here to reduce repetition in the main do_calculate function, it directly assigned values to variables 
void Equation::findInParenth(int * i, string * expression, string * in_parenth) {
	int k = *i;
	//reverse parsing direction using this do while loop until a closing parentheses is found ")"
	do {
		//once a closing bracket is found then continue 
		if (expression->at(k) == ')') {
			//grab the equation that is contained within the parentheses and store it inside in_parenth
			for (int j = 1; j < (k - *i); j++) {
				*in_parenth += expression->at(*i + j);
			}

			//break and continue			
			break;
		}

		//if no ")" is found then go to the next char in the string
		k++;
	} while (k != expression->length());
}

//insert the reduced value into the expression and give debug output, this function exists to reduce repeated code, uses almost all references to save memory
void Equation::insertSolution(string debug_output, int * i, string * expression, string * in_parenth, string * insert, string * function, bool * debug) {
	//debug info
	if (*debug) {
		color('y'); cout << "Original Expression: "; color('r'); cout << *expression << endl;
	}

	//cut out the old value and replace it with the simplified value
	expression->replace(*i - function->length() + 1, function->length() + in_parenth->length() + 1, cleanNumb(*insert));

	//debug info
	if (*debug) {
		color('y');  cout << debug_output; color('c'); cout << *in_parenth << " = "; color('g');  cout << cleanNumb(*insert) << endl;
		color('y'); cout << "Simplified Expression: "; color('b'); cout << *expression << endl << endl;
	}

	//clear in_parenth
	in_parenth->clear();

	//reset i at the new end of the function
	*i = expression->length();
}

//this is a very spesific case check, it makes sure that if the first number is negative, that there are no other signs, if there is then return false, if not return true
//this makes sure that if you have -7+8 it wont return -7, and will properly calculate 1.
bool checkForNonSubtraction(string equation) {
	//loop through the desired equation and determine if it contains any operator other than '-' if it does return false
	for (int i = 0; i < equation.length(); i++) {
		switch (equation[i]) {
		case '+':
			return false;
		case '*':
			return false;
		case '/':
			return false;
		case '^':
			return false;
		default:
			break;
		}
	}

	//if it doesnt contain another operator than '-' return true
	return true;
}

//remove extra 0s and .s from a given string
string cleanNumb(string input) {
	//if there is just a zero, then there is nothing to be cleaned
	if (input == "0" || input == "-0") {
		return input;
	}

	//if there is no ., the number is not in double form and doesnt need to be cleaned
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '.') {
			break;
		}

		if (to_string(i) == to_string(input.length() - 1)) {
			return input;
		}
	}

	//remove trailing zeroes and dots from the string
	input.erase(input.find_last_not_of('0') + 1, string::npos);
	input.erase(input.find_last_not_of('.') + 1, string::npos);

	//return the value as a string
	return input;
}

//checks for a parenthesis, saves calculation time on simple equations
bool checkForParenth(string * expression) {
	for (int i = 0; i < expression->length(); i++) {
		if (expression->at(i) == '(') {
			return true;
		}
	}

	return false;
}

unsigned long long factorial(signed long long input) {
	//if the input is negative it is invalid, so assume the input was meant to be positive and invert it
	if (input < 0) {
		input *= -1;
	}

	//floor the input so it is an integer
	input = floor(input);

	unsigned long long out = 1;

	for (signed long long i = input; i > 0; i--) {
		out = out * i;
	}

	return out;
}