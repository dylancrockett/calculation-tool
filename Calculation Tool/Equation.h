#pragma once

class Equation {
	private:
		//private functions and variables

		/* Functions
			doCalculate - evaluate a given expression, references itself, only used by member functions so is private
			findInParenth - used within doCalculate to find the contents of parenthesis
			insertSolution - used within doCalculate to insert a simplified solution and replace the unsimplified variant
		*/
		std::string doCalculate(std::string equation, bool debug = false);
		void findInParenth(int * i, std::string * expression, std::string * in_parenth);
		void insertSolution(std::string debug_output, int * i, std::string * expression, std::string * in_parenth, std::string * insert, std::string * function, bool * debug);


	public:
		//public functions and variables

		/* Variables
			equation - the equation stored within the class
		*/
		std::string equation = "";
		std::string solution = "";

		/* Functions
			Equation - takes args when a Equation is made
			setEquation - sets the equation entered to the private equation variable
			calculate - will resolve the function into a float and return it
		*/
		Equation(const std::string eq = "1 + 1 =");
		void setEquation(const std::string in);
		void calculate(bool debug = false);
};