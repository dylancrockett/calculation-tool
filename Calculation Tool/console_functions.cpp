#include <windows.h>
#include <iostream>
#include <string>
#include "ConsoleFunctions.h"

using namespace std;

//set the text color | options: (r,g,b,y,p,c,w)
void color(char color) {
	switch (color) {

	case 'r':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case 'g':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case 'b':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case 'y':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case 'p':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case 'c':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	default:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	}
}

//returns a spesified # of the same char as a string 
string charLoop(char type, int number) {
	int x = number;
	string output = "";

	while (x != 0) {
		output = output + type;
		x--;
	}

	return output;
}

//clear screen
void clear() {
	system("cls");
};

//pause screen
void pause() {
	system("pause");
};