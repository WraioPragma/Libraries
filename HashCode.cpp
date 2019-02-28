#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <set>
#include <map>
#define forn for(int i=0;i<n;i++)

using namespace std;


template<class T, class S, class Q>
struct triada
{
	T first;
	S second;
	Q third;
};


class Photos {
public:
	Photos(int id, bool hol) {
		this->id = id;
		horizontal = hol;
	}

	int id;
	bool horizontal;
	vector<string> tags;
	vector<int> tags_int;
};

#pragma region main flow
string cur = "";
vector<int> freqH;
vector<int> freqV;
vector<Photos> photos;
set<string> uniqueTags;
map<string,int> vecUn;
void init(string inputName);
void execAlg();
void printSlideShow(vector<pair<int,int>> &output);
void initFreq();

void init(string inputName) {
	cur = inputName;
	ifstream input(inputName + ".txt");
	string in;
	int n;
	input >> n;
	forn {
		string horizontal;
		input >> horizontal;
		int numTags;
		input >> numTags;
		vector<string> arrTags;
		for (int j = 0; j < numTags; j++){
			string buffer;
			input >> buffer;
			arrTags.push_back(buffer);
			uniqueTags.insert(buffer);
		}
		photos.push_back(Photos(i, horizontal == "H"));
		photos[i].tags = arrTags;
	}

	int coun = 0;
	for (string str : uniqueTags) {
		vecUn[str] = coun;
		coun++;
	}
	for (Photos ph : photos) {
		for (string str : ph.tags) {
			ph.tags_int.push_back(vecUn[str]);
		}
	}
	
	execAlg();
}

void initFreq() {
	freqV.resize(vecUn.size(), 0)
	freqH.resize(vecUn.size(), 0)
	for(Photos ph : photos) {
		if (ph.horizontal) {
			for(int tgd: ph.tags_int)
				freqH[tgd]++;
		}
		else {
			for(int tgd: ph.tags_int)
				freqV[tgd]++;
		}
	}
}

void execAlg() {
	
}

void printSlideShow(vector<pair<int,int>> &output)
{
	ofstream out(cur + "_out.out");
	out << output.size() << "\n";
	for (int j=0; j<output.size(); j++)
	{
		out << output[j].first ;
		if (output[j].second != -1) out << " " << output[j].second << "\n";
		else out << "\n";
	}
}
#pragma endregion main flow 

#pragma region main
int main()
{
	string inputsArray[5] = {"a_example","b_lovely_landscapes","c_memorable_moments","d_pet_pictures","e_shiny_selfies"};													// array with filenames to process
	
	
	//for (string inputName : inputsArray) {									
	//	cout << inputName << endl;
	//	init(inputName);
		init(inputsArray[1]);													
	//}
	return 0;
}
#pragma endregion end of main