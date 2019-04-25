#pragma once

//this class was created to make my life easier but I think I made simple problem a lot more complex, granted this saved so much repetitive code that the complexity is #worth
//this class HAD the intention to reduce the amount of hard coded menu code
class Menu {
private:
	/* Variables
		title - the title displayed by the menu
		choices - a 2d vector that has 3 vectors contained within the main vector
			vector 1 - option
			vector 2 - option description
			vector 3 - output text
		return_menu - a pointer to a referenced Menu that will be used to go back to the previous Menu
	*/
	std::string title;
	std::vector<std::vector<std::string>> choices{ {""}, {""}, {""} };
	Menu * return_menu;

	/* Functions
		createMenu - populate the Menu object based on the input
	*/
	void createMenu(std::string t, std::vector<std::vector<std::string>> c, Menu * r_m);

public: 
	/* Functions
		Menu - called when a Menu object is created
		display - display the menu
	*/
	Menu(std::string title, std::vector<std::vector<std::string>> choices, Menu * return_menu = NULL);
	std::string display();
};
