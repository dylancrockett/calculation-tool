#include <string>
#include <vector>
#include "File.h"

using namespace std;

//create a file - called when a File is created to set the variables
void File::createFile(const vector<string> content, const string fn, const string f) {
	contents = content;
	name = fn;
	folder = f;
};
