#pragma once

//the File class only deals with .txt files, this is hard coded to avoid misuse
//the parent class for the Read and Write classes, has the base structure such as the contents and basic functions for the file class 
class File 
{
	//these are protected because they are not used outside of the class but are used in child classes
	protected:
		/* Protected Functions
			createFile - populate the variables of the File class with specified data
		*/
		void createFile(const std::vector<std::string> content, const std::string fn, const std::string f);

	//these are basic public functions that allow the user to update the contents of a File or get them as a vector
	public:
		/* Variables
			folder - the folder that the file is located in within refernce to the current location of the program
			file_name - the name of the file
			file_contents - a vector that has one string per line of the file (holds the file's contents)
		*/
		std::string folder;
		std::string name;
		std::vector<std::string> contents;
};