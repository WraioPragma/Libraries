// HashCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void start(string inputName) {
	ifstream input(inputName + ".in");
	ofstream output(inputName + ".txt");
	string in;
	while (getline(input,in)) {
		//Do: stuff
		output << in << endl;
	}
	
	
}

int main()
{
	string inputsArray[5] = { "a_example", "b_should_be_easy", "c_no_hurry","d_metropolis","e_high_bonus"};
	for (string inputName : inputsArray) {
		start(inputName);

	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
