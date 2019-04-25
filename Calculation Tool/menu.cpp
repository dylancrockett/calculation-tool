#include <vector>
#include <string>
#include <windows.h>
#include <iostream>
#include "Menu.h"
#include "ConsoleFunctions.h"

using namespace std;

void color(char color);
string charLoop(char type, int number);
void clear();
void pause();

//i swear to god this was a lot less messy when I first came up with the idea to do this but now its really complex and hard to understand!!!!!

//create the menu when the menu class is called, require some input to populate the menu
Menu::Menu(string title, vector<vector<string>> choices, Menu * return_menu) {
	createMenu(title,choices,return_menu);
}


void Menu::createMenu(string t, vector<vector<string>> c, Menu * r_m) {
	title = t;
	choices = c;
	return_menu = r_m;
}

string Menu::display() {
	int choice = -1;

	//while the choice is not valid then continue this loop, once it is valid then continue.
	while (choice < 0 || choice > (choices[0].size() + 1)) {
		//begin menu output !MAKE IT LOOK PRETTY!
		color('b'); cout << title << ":" << endl;
		for (int i = 0; i < choices[0].size(); i++) {
			color('b'); cout << "["; color('r'); cout << (i + 1); color('b'); cout << "] "; color('c'); cout << choices[0][i] << endl;
			color('y'); cout << charLoop(' ', 5) << choices[1][i] << endl;
		}
		color('b'); cout << "["; color('r'); cout << (choices[0].size() + 1); color('b'); cout << "] "; color('c'); cout << "Exit" << endl;
		color('y'); cout << charLoop(' ', 5) << "Exit your current selection." << endl;

		color('b'); cout << endl << "Enter your selection: "; color('r'); cin >> choice;

		clear();
	}

	//if the choice is to return, then display the menu specified as the return menu and then return whatever value is resolved
	if (choice == (choices[0].size() + 1)) {
		//for the one case where there is no return menu, the main menu, then return with no data because the program will then end 
		if (!return_menu) {
			return "";
		}

		//if the null check passes and the Menu exists then display it
		return return_menu->display();
	}

	return choices[2][choice - 1];
}