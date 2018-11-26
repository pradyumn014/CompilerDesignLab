#include<bits/stdc++.h>
using namespace std;

set<char> nont;


/*
4
S E T A
4
id = + num 
- - - - A:num
- - - E:T+A -
- - - S:id=E -
- - - T:id -
S
5
id + id + num
*/


set<string> non_terminals;
map<string,vector<vector<string> > > productions;
map<string,int> terminals;
map<int,string> id_to_terminals;
int cnt=0;
map<string,int> first_set;
map<string,int> follow_set;
map<string,vector<vector<string> > > sym_production;
map<string,map<string,vector<string> > > table;
string start;



#define pb push_back

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

	// cout<<"Enter the number of productions"<<endl;
	// int p;
	// cin>>p;
	// vector<string> temp;
	// string aux;
	
	// cout<<"Enter all the productions "<<endl;
	// for(int i=1;i<=p;i++)
	// {
		
	// 	temp.clear();aux.clear();
	// 	cin>>str;
	// 	string left_symbol;
	// 	vector<string> curr;
	// 	for(char &ch:str)
	// 	{
	// 		if(ch=='=')
	// 			continue;
	// 		else
	// 		{
	// 			aux.pb(ch);
	// 			if((terminals.find(aux)!=terminals.end()||non_terminals.find(aux)!=non_terminals.end()))
	// 			{
	// 				if(left_symbol.empty())
	// 					left_symbol=aux;
	// 				else 
	// 					temp.pb(aux);
	// 				curr.pb(aux);
	// 				aux.clear();
	// 			}
	// 		}
	// 	}
	// 	productions[left_symbol].pb(temp);


	// 	for(auto & sym:temp)
	// 		sym_production[sym].pb(curr);

	// }

	vector<string> temp;
	string aux;
	for(string const & nterm:non_terminals)
	{
		cout<<nterm<<" : ";
		for(auto const & term: terminals)
		{
			// cout<<term.first<<" -> "<<endl;
			temp.clear();aux.clear();
			cin>>str;
			if(str=="-")
			{
				continue;
				cout<<"-"<<" ";
			}
			string left_symbol;
			vector<string> curr;
			for(char &ch:str)
			{
				if(ch==':')
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
						curr.pb(aux);
						aux.clear();
					}
				}
			}
			// productions[left_symbol].pb(temp);
			table[nterm][term.first]=temp;
		}
	}

	cout<<"Enter the start non-terminal"<<endl;
	cin>>start;

	// for(string const & nterm:non_terminals)
	// {
	// 	for(auto const & term: terminals)
	// 	{
	// 		if(table.count(nterm) && table[nterm].count(term.first))
	// 		{
	// 			vector<string> const & temp=table[nterm][term.first];
	// 			for(string const & str:temp)
	// 				cout<<str;
	// 		}
	// 		else
	// 			cout<<"-";
	// 		cout<<" ";
	// 	}	
	// 	cout<<endl;
	// }

	cout<<"Enter the string to be parsed in terms of tokens"<<endl;
	int len;
	cout<<"Enter its length"<<endl;
	cin>>len;
	vector<string> inp;
	for(int i=1;i<=len;i++)
	{
		string str;
		cin>>str;
		inp.pb(str);
	}
	inp.pb("$");
	reverse(inp.begin(),inp.end());

	vector<string> st;
	st.pb("$");
	st.pb(start);

	while(inp.back()!="$" && st.back()!="$")
	{
		string symbol=st.back();
		string token=inp.back();

		for(auto const &item:st)
			cout<<item<<" ";
		cout<<",";
		for(auto const &item:inp)
			cout<<item<<" ";
		cout<<endl;

		if(terminals.count(symbol))
		{
			if(symbol==token)
				{
					st.pop_back();
					inp.pop_back();
				}
			else
				break;
		}
		else
		{
			if(table.count(symbol) &&  table[symbol].count(token) )
			{
				st.pop_back();
				vector<string> const &prod = table[symbol][token];
				for(int i=prod.size()-1;i>=0;i--)
					st.push_back(prod[i]);
			}
			else
				break;
		}
	}

	if(st.back()=="$" && inp.back()=="$")
		printf("ACCEPTED\n");
	else
		printf("NOT ACCEPTED\n");

}