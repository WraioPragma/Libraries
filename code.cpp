class Assignment{
	public:
		void assign(int serverid, int service,int client);
		double score();
		void reassign(int server_orig, int server_dest,int serv, int client);


};






class Server{


	int id;
};


vector<int> serverloc;
vector<Server> server;

typedef bool (*Comp)(const Server &a, const Server &b);

void sort_servers(Comp f)
{
	sort(server.begin(),server.end(),f);
	for(int i=0; i<server.size();i++){
		serverloc[server[i].id] = i;
	}
}








