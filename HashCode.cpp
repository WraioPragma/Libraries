#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

void start(string inputName) {
	ifstream input(inputName + ".in");
	ofstream output(inputName + ".txt");
	string in;
	while (getline(input,in)) {
		//Do: stuff
		output << "End!!" << endl;
	}
	
	
}

int main()
{
	string inputsArray[5];													// array with filenames to process
	string path = "D:\\Projects\\HashCode\\HashCode\\";						// working directory
	int counter = 0;														
	for (const auto & entry : fs::directory_iterator(path)) {				// iterate the list of files in working directory
		if (entry.path().extension() == ".in") {							// get only .in files
			string fullName = entry.path().filename().string();				// get filename (with extension)
			inputsArray[counter] = fullName.substr(0, fullName.size() - 3); // remove extension 
			counter++;														// increment counter			
		}
	}

	for (string inputName : inputsArray) {									
		start(inputName);													
	}
	return 0;
}
