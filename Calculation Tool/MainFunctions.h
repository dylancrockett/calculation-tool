#pragma once

//declare functions used in main
void solveEquations(std::vector<std::string> * input, bool console_output = false, std::string * file_name = NULL, std::string * output_folder_name = NULL, bool do_output = false, bool debug = false);
std::vector<std::string> createEquations(int equations, int mode, int difficulty, bool debug = false);
void getSettings(std::string * input_file_name, std::string * output_file_name, bool * debug_setting, std::string * user_name);
std::string userInput(std::string question);
std::string cleanFloat(float input);
unsigned long s_hash(std::string str);
int random(int min, int max);