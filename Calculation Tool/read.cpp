#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Read.h"

using namespace std;

Read::Read(const string file_name, const string input_folder) {
	//create a file with no body and a name + file
	createFile({""}, file_name, input_folder);

	//populate the file's body by reading the body of the target file
	readFile();
}

void Read::readFile() {
	ifstream input;

	//open the file (change to a relative file path later)
	if (folder == "") {
		input.open(name + ".txt");
	}
	else {
		input.open(folder + "\\" + name + ".txt");
	}

	if (input) {
		//do nothing
	}
	else {
		//give error and exit function (this should already be a solved issue by a seperate function checking if the file exits before the readFile function is even called)
		cout << "File '" << name << ".txt' not found within folder " << folder << "." << endl;
		return;
	}

	//this string stores the value of the line which is read then stored to the contents vector
	string line;

	while (getline(input, line)) {
		//read the line of the file then save it to the tempory vector which stores the data
		contents.push_back(line);
	}

	//close the file
	input.close();
}