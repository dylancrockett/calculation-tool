#include <vector>
#include <string>
#include <fstream>
#include "Write.h"

using namespace std;

//called when a Write is created
Write::Write(const vector<string> content, const string file_name, const string input_folder) {
	//since the Write object writes the input to the file as soon as it is created there is no need to coppy the vector to the file object, rather reference it using pointers to save memory
	createFile(content, file_name, input_folder);
};

void Write::output(bool use_external_content, vector<string> * input) {
	//create a file path based on output folder
	string temp_name;

	temp_name = folder + "\\" + name + ".txt";

	//open a new file
	ofstream new_file(temp_name);

	//if the output is going to use external contents then use the referenced vector, otherwise use the vector native to the file class 'contents'
	if (use_external_content) {
		for (int i = 0; i < input->size(); i++) {
			new_file << input->at(i) << endl;
		}
	}
	else {
		for (int i = 0; i < contents.size(); i++) {
			new_file << contents.at(i) << endl;
		}
	}

};