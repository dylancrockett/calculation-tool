#pragma once
#include "File.h"

//child class of the File class that has the ability to read a file given its name and folder location
class Read : public File
{	
	private:
		/* Functions
			readFile - called when a Read object is created and grabs the directed file's contents-
		*/
		void readFile();

	public:
		/* Functions
			Read - on creation of a Read object it will create a File that will be populated with the body of a specified file
		*/
		Read(const std::string file_name, const std::string input_folder = "input");
};