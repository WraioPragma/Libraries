#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<algorithm>
#include<math.h>
#include<cstring>
#define forn for(int i=0;i<n;i++)
#define ll long long
#define pii pair<int,int>
#define pll pair<long,long>
#define f first
#define s second
using namespace std;
vector<int>freqV;
vector<int>lengh;
vector<int>freqs;
vector<pair<int,double> >score1;
vector<pair<int,double> >score2;
vector<pair<int,double> >score3;

bool mycomp(pair<int,double> a, pair<int, double> b)
{
    return a.second<b.second;
}

vector<pii>pairs;

void pairit()
{
    for(int i=0;i<photos.size();i++)
    {
        if(photos[i].horizontal)
        {
            continue;
        }
        lengh.push_back(photos[i].tags_int.size());
        int sum=0;
        for(int j=0;j<photos[i].tags_int.size();j++)
        {
            sum+=freqV[photos[i].tags_int[j]];
        }
        freqs.push_back(sum);
    }
    int count = 0;
    for(int i=0;i<photos.size();i++)
    {
        if(photos[i].horisontal)
        {
            continue;
        }
        score1.push_back(make_pair(photos[i].id,length[count]*1.0/freqs[count]));
        score2.push_back(make_pair(photos[i].id,length[count]*1.0));
        score3.push_back(make_pair(photos[i].id,freqs[count]*1.0));
    }
    sort(score1.begin(),score1.end(),mycomp);
    sort(score2.begin(),score2.end(),mycomp);
    sort(score3.begin(),score3.end(),mycomp);
    for(int i=0;i<score1.size()/2;i++);
    {
        pairs.push_back(make_pair(score1[i],score1[N-i]));
    }
}
int main()
{
    pairit();
}
