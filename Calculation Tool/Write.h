#pragma once
#include "File.h"

//child class of the File class that has the ability to "write" a file by creating a new file in a specified location with a specified name and body
class Write : public File
{
	public:
		/* Public Functions
			Write - will be called when the write class is created, will also call outputFile to create a file in the specified location
			output - will output a file based on the File's contents and name OR can take external input <- this option exists to save time by referencing 
					 an existing array rather than copping it, to save memory
		*/
		Write(const std::vector<std::string> content, const std::string file_name, const std::string input_folder = "output");
		void output(bool use_external_content = false, std::vector<std::string> * input = NULL);
};