/* Input

6
S C1 A1 F T E1 
3
+ id int
9
S=C1A1
A1=FTE1
T=+T
T=F
F=id
E1=+id
E1=$
C1=$
C1=int+

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
set<string> non_terminals;
map<string,vector<vector<string> > > productions;
map<string,int> terminals;
map<int,string> id_to_terminals;
int cnt=0;
map<string,int> first_set;


void calc(string const & nont)
{
	if(first_set.count(nont))
		return ;
	int final_mask=0;
	cout<<nont<<endl;
	for(auto & prod:productions[nont])
	{
		int curr_mask=1;

		for(string & child:prod)
		{
			if(!(curr_mask&1))
				break;
			
			curr_mask^=1;
			if(terminals.find(child)!=terminals.end())
			{
				int id=terminals[child];
				curr_mask|=(1<<id);
			}
			else
			{
				if(!first_set.count(child))
					calc(child);
				curr_mask|=first_set[child];
			}
		}
		final_mask|=curr_mask;
	}
	first_set[nont]=final_mask;
}


int main()
{
	string str;
	cout<<"Enter the number of non-terminals"<<endl;
	int nt;
	cin>>nt;
	cout<<"Enter the non-terminals"<<endl;
	for(int i=1;i<=nt;i++)
	{
		cin>>str;
		non_terminals.insert(str);
	}
	terminals["$"]=0;
	id_to_terminals[0]="$";
	cout<<"Enter the number of terminals"<<endl;
	int t;
	cin>>t;
	cout<<"Enter the terminals"<<endl;

	for(int i=1;i<=t;i++)
	{
		cin>>str;
		terminals[str]=++cnt;
		id_to_terminals[cnt]=str;
	}
	
	cout<<"Enter the number of productions"<<endl;
	int p;
	cin>>p;
	vector<string> temp;
	string aux;
	cout<<"Enter all the productions "<<endl;
	for(int i=1;i<=p;i++)
	{
		temp.clear();aux.clear();
		cin>>str;
		string left_symbol;
		for(char &ch:str)
		{
			if(ch=='=')
				continue;
			else
			{
				aux.pb(ch);
				if((terminals.find(aux)!=terminals.end()||non_terminals.find(aux)!=non_terminals.end()))
				{
					if(left_symbol.empty())
						left_symbol=aux;
					else 
						temp.pb(aux);
					aux.clear();
				}

			}
		}
		productions[left_symbol].pb(temp);
	}

	for(const string &nont:non_terminals)
	{
		if(first_set.count(nont))
			continue;
		calc(nont);	
	}

	cout<<"FIRST  for each non-terminal "<<endl;
	for(const string &nont:non_terminals)
	{
		cout<<nont<<" : { ";
		int mask=first_set[nont];
		for(int i=0;i<=t;i++)
			if(mask&(1<<i))
				cout<<id_to_terminals[i]<<" , ";
		cout<<" } "<<endl;
	}

	cout<<"FIRST for each production "<<endl;

	for(const string & nont:non_terminals)
	{
		for(auto & prod:productions[nont])
		{
			cout<<"( "<<nont<<" = ";
			int curr_mask=1;
			for(string & child:prod)
			{
				cout<<child;
				if(!(curr_mask&1))
					continue;
				curr_mask^=1;
				if(terminals.find(child)!=terminals.end())
				{
					int id=terminals[child];
					curr_mask|=(1<<id);
				}
				else
					curr_mask|=first_set[child];
			}
			cout<<" ) : {";  
			for(int i=0;i<=t;i++)
				if(curr_mask&(1<<i))
					cout<<id_to_terminals[i]<<" , ";
			cout<<" } "<<endl;
		}
	}

	return 0;
}