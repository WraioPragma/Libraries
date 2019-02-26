#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <math.h>
#include <stack>
/*
akoma einai gtpk dont try to understand it
*/
template<class T, class S, class Q>
struct triada
{
    T first;
    S second;
    Q third;
};

class grid
{
public:
    grid(int n, int m, bool isvalpoints = true);

    void addpoint(int x, int y, int id = -1, double val = 1.0);//adds 1 point to the grid

    std::vector < std::vector<std::pair<int, double> > > retgrid();//returns grid
    std::vector < std::pair<int, std::pair<int,int> > > retpoints();//returns points
    std::pair <int,double> rpf_quordinates(int x,int y);//gets quordinates returns id and value
    triada <int, int, double> rpf_id(int id);//gets id returns quordinates and value

    void printpoints();//ektyupwse ola ta sumeia tou grid
    void printgrid();//ektupwse olo to grid me ta shmeia tou

private:
    std::vector < std::vector<std::pair<int, double> > > valpoints;//id value
    std::vector < std::pair<int, std::pair<int,int> > > nonvalpoints;//id <xcor, ycor>
    std::vector < std::pair<int, int> >index_matrix;//x,y
    int rows,columns;
    bool has_values;
};
//usefull functions
bool mycomp(std::pair<int, std::pair<int,int> > a, std::pair<int, std::pair<int,int> > b)
{
    if(a.second.first==b.second.first)
    {
        return a.second.second<b.second.second;
    }
    return a.second.first<b.second.first;
}
//actual functions
grid::grid(int n, int m, bool isvalpoints)
{
    has_values=isvalpoints;
    //std::cout<<has_values<<isvalpoints;
    rows=n;
    columns=m;
    if(isvalpoints)
    {
        for(int i=0;i<n;i++)
        {
            std::vector<std::pair<int,double> >tmp;
            for(int j=0;j<m;j++)
            {
                tmp.push_back(std::make_pair(-1,0.0));
            }
            valpoints.push_back(tmp);
        }
        index_matrix.resize(n*m,std::make_pair(-1,-1));
    }
    //std::cout<<rows<<' '<<columns<<'\n';
    //printgrid();
}

void grid::addpoint(int x, int y, int id , double val)
{
    if(id==-1)
    {
        id=nonvalpoints.size();
    }
    if(index_matrix[id].first!=-1)
    {
        std::cout<<"error that point already exists\n";
        return;
    }
    if(x>rows||y>columns||id>rows*columns-1)
    {
        std::cout<<"error wrong input in addpoint\n";
        return;
    }
    if(has_values)
    {
        valpoints[x-1][y-1].first=id;
        valpoints[x-1][y-1].second=val;
    }
    index_matrix[id].first=x-1;
    index_matrix[id].second=y-1;
    nonvalpoints.push_back(std::make_pair(id,std::make_pair(x-1,y-1)));
    std::sort(nonvalpoints.begin(),nonvalpoints.end(),mycomp);
}

std::vector < std::vector<std::pair<int, double> > > grid::retgrid()
{
    return valpoints;
}

std::vector < std::pair<int, std::pair<int,int> > > grid::retpoints()
{
    return nonvalpoints;
}

std::pair<int, double> grid::rpf_quordinates(int x, int y)
{
    x++;
    y++;
    if(valpoints[x][y].first==-1)
    {
        std::cout<<"there is no such point\n";
        return std::make_pair(-1,-1);
    }
    return valpoints[x][y];
}

triada<int,int,double> grid::rpf_id(int id)
{
     if(id>rows*columns||index_matrix[id].first==-1)
     {
            std::cout<<"no point with such index u asked for point"<< id<<'\n';
            triada<int,int,double> tmp;
            tmp.first = -1;
            tmp.second = -1;
            tmp.third = -1;
            return tmp;
     }
    triada<int,int,double>tmp;
    tmp.first = index_matrix[id].first;
    tmp.second = index_matrix[id].second;
    tmp.third = valpoints[tmp.first][tmp.second].second;
    return tmp;
}

void grid::printpoints()//not good
{
    for(int i=0;i<nonvalpoints.size();i++)
    {
        if(has_values)
        {
            std::cout<<valpoints[nonvalpoints[i].second.first][nonvalpoints[i].second.second].first<<"->"
                <<valpoints[nonvalpoints[i].second.first][nonvalpoints[i].second.second].second
                <<' '<<nonvalpoints[i].second.first+1<<' '<<nonvalpoints[i].second.second+1<<'\n';
        }
        else
        {
            std::cout<<nonvalpoints[i].first<<"-> 1"<<nonvalpoints[i].second.first<<' '<<nonvalpoints[i].second.second<<'\n';
        }
    }
}

void grid::printgrid()
{
    if(!has_values)
    {
        std::cout<<"there is no grid\n";
        return;
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            std::cout<<valpoints[i][j].first<<"->"<<valpoints[i][j].second<<' ';
        }
        std::cout<<'\n';
    }
}
/*
using namespace std;
int main()
{
    int n,m;
    bool val;
    cin>>n>>m>>val;
    //cout<<val;
    grid mygrid(n,m,val);
    int x,y,id;
    double w;
    mygrid.printgrid();
    for(int i=0;i<10;i++)
    {
        cin>>x>>y>>id>>w;
        mygrid.addpoint(x,y,id,w);
        mygrid.printpoints();
    }
    std::vector < std::vector<std::pair<int, double> > > a;//id value
    std::vector < std::pair<int, std::pair<int,int> > > b;//id <xcor, ycor>
    a = mygrid.retgrid();
    b = mygrid.retpoints();
    for(int i=0;i<a.size();i++)
    {
        for(int j=0;j<a[i].size();j++)
        {
            cout<<a[i][j].first<<"->"<<a[i][j].second<<' ';
        }
        cout<<'\n';
    }
    cout<<'\n';
    for(int i=0;i<b.size();i++)
    {
        cout<<b[i].first<<"-> "<<b[i].second.first+1<<' '<<b[i].second.second+1<<'\n';
    }
    cout<<'\n';
    pair<int,double>c;
    triada<int,int,double>d;
    c = mygrid.rpf_quordinates(2,3);
    cout<<c.first<<' '<<c.second<<'\n';
    c = mygrid.rpf_quordinates(2,1);
    cout<<c.first<<' '<<c.second<<'\n';
    d = mygrid.rpf_id(1);
    cout<<d.first<<' '<<d.second<<' '<<d.third<<'\n';
    d = mygrid.rpf_id(11);
    cout<<d.first<<' '<<d.second<<' '<<d.third<<'\n';
    d = mygrid.rpf_id(100);
    cout<<d.first<<' '<<d.second<<' '<<d.third<<'\n';
}
*/
