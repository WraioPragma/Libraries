
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
		for(int y : temp){
			if(y == x) {
				temp.push_back(x);
				break;
			}
		}
	}
	for(int x : two){
		for(int y : temp){
			if(y == x) {
				temp.push_back(x);
				break;
			}
		}
	}
	return temp;
}


void printSlideShow(vector<pair<int,int>> &output)
{
	cout<< output.size() << "\n";
	for (int j=0; j<output.size(); j++)
	{
		cout << output[j].first ;
		if (output[j].second != -1) cout << " " << output[j].second << "\n";
		else cout << "\n";
	}
}
