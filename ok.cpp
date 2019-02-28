#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <set>
#include <map>
#include <ctime>
#define forn for(int i=0;i<n;i++)

#define ll long long
#define pi pair<int,int>
#define pll pair<long,long>
#define f first
#define s second
#define vi vector<int>
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
vector<pair<int,int>> slsh;
void init(string inputName);
void pairPhotos();
void printSlideShow(vector<pair<int,int>> &output);
void initFreq();
double score(vector<pair<int,int>> &output);
double score_slide_trans(pi &one, pi &two);
vi tags_slide(int p1, int p2);
bool swap_slides_if_better(vector<pi> &output,int slide_one, int slide_two);
void optimize_outp(vector<pi> & output);
vi merge(vi &one, vi &two);
vector<int> tomh(vi &one, vi &two);

void init(string inputName) {
	freqH.clear();
	freqV.clear();
	photos.clear();
	uniqueTags.clear();
	vecUn.clear();
	slsh.clear();
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
	for (Photos &ph : photos) {
		for (string &str : ph.tags) {
			ph.tags_int.push_back(vecUn[str]);
		}
	}
	pairPhotos();
}

void initFreq() {
	freqV.resize(vecUn.size(), 0);
	freqH.resize(vecUn.size(), 0);
	for(Photos &ph : photos) {
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

void pairPhotos() {
	int lastV = -1;
	
	for (Photos &ph : photos) {
		if (!ph.horizontal) {
			if(lastV == -1) {
				lastV = ph.id;
			} else {
				slsh.push_back(make_pair(lastV,ph.id));
				lastV = -1;
			}
		} else {
			slsh.push_back(make_pair(ph.id, -1));
		}
	}
	optimize_outp(slsh);
	printSlideShow(slsh); 
	cerr << score(slsh) << endl;
}
double score(vector<pair<int,int>> &output)
{
	double sc = 0;
	for(int i = 0; i<output.size()-1;i++){
		pi one = output[i];
		pi two = output[i+1];
		int inc_val = score_slide_trans(one,two);
		sc = sc + inc_val;
	}
	return sc;
}


double score_slide_trans(pi &one, pi &two)
{
	if(one == make_pair(-1,-1)) return 0;
	if(two == make_pair(-1,-1)) return 0;
	int id1 = one.first;
		int id2 = one.second;
		int id3 = two.first;
		int id4 = two.second;
		vi sl1 = tags_slide(id1,id2);
		vi sl2 = tags_slide(id3,id4);

		vi common = tomh(sl1,sl2);

		int common_size = common.size();
		int unique1 = sl1.size() - common_size;
		int unique2 = sl2.size() - common_size;

		int inc_val = min(unique1,min(unique2,common_size));
		return inc_val;
}

vi tags_slide(int p1, int p2)
{
	vi temp = photos[p1].tags_int;
	if(p2 != -1){
			vi t2 = photos[p2].tags_int;
			vi temp3 = merge(temp,t2);
			temp = temp3;
	}
	return temp;
}


vector<int> tomh(vi &one, vi &two)
{
	vi temp;
	for(int x : one){
		for(int y : two){
			if(y == x) {
				temp.push_back(x);
				break;
			}
		}
	}
	return temp;
}


vi merge(vi &one, vi &two)
{
	vi temp;
	for(int x : one){
		bool ok = true;
		for(int y : temp){
			if(y == x) {
				ok = false;
			}
		}
		if(ok) temp.push_back(x);
	}
	for(int x : two){
		bool ok = true;
		for(int y : temp){
			if(y == x) {
				ok = false;
			}
		}
		if(ok) temp.push_back(x);
	}
	return temp;
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

bool swap_slides_if_better(vector<pi> &output,int slide_one, int slide_two)
{
	pi old1,curr1,next1;
	pi old2, curr2, next2;
	double score_beg = 0;
	double score_end = 0;

	old1 = (slide_one != 0)?output[slide_one-1]:make_pair(-1,-1);
	curr1 = output[slide_one];
	next1 = output[slide_one+1];

	old2 = (slide_two != 0)?output[slide_two-1]:make_pair(-1,-1);
	curr2 = output[slide_two];
	next2 = output[slide_two+1];

	score_beg = score_slide_trans(old1,curr1) + score_slide_trans(curr1,next1) + score_slide_trans(old2,curr2) + score_slide_trans(curr2,next2);
	score_end = score_slide_trans(old1,curr2) + score_slide_trans(curr2,next1) + score_slide_trans(old2,curr1) + score_slide_trans(curr1,next2);

	if(score_end > score_beg) {
		swap(output[slide_one],output[slide_two]);
		return true;
	}
	return false;
}

void optimize_outp(vector<pi> & output)
{
	int K = 1000000;
	while(K--){
		int h = rand()%output.size();
		for(int i=0; i<100;i++){
			int r = rand()%output.size();
			if(swap_slides_if_better(output,h,r)) break;
		}
	}
}

#pragma endregion main flow 

#pragma region main
int main()
{
	string inputsArray[5] = {"a_example","b_lovely_landscapes","c_memorable_moments","d_pet_pictures","e_shiny_selfies"};													// array with filenames to process
	std::srand(std::time(nullptr));
	
	for (string inputName : inputsArray) {									
		cout << inputName << endl;
		init(inputName);
	//	init(inputsArray[1]);													
	}
	return 0;
}
#pragma endregion end of main