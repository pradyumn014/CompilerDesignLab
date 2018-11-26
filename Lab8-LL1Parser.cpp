/*
Pradyumn Sinha
*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define fi first
// 3
// E T F
// 5
// id + * ( )
// 4
// E=E+T
// T=F
// F=(E)
// F=id

// 		4
// S E T A
// 4
// id = + num 
// S
// 2
// 4
// S:id=E
// E:T+A
// T:id
// A:num
// 5
// id = id + num

// 		4
// S E T A
// 4
// id = + num 
// 1
// - - - - A:num
// - - - E:T+A -
// - - - S:id=E -
// - - - T:id -
// S
// 5
// id = id + num


// S-*>aAaB
// a is in follow(A)
// S-*> aA
// $ in FOLLOW(A)

//RULES
//Put $ in FOLLOW(S)
// A->aBb put First(B)-{eps} in FOLLOW(B)
// A->aBC and FIRST(C) has epsilon put Follow(A) in FOLLOW(B)

set<string> non_terminals;
map<string,vector<vector<string> > > productions;
map<string,int> terminals;
map<int,string> id_to_terminals;
int cnt=0;
map<string,int> first_set;
map<string,int> follow_set;
map<string,vector<vector<string> > > sym_production;
string start;
map<string,map<int,vector<string> > > table;
int follow_calc(string const & nont)
{
	if(follow_set.count(nont))
		return follow_set[nont];

	int final_mask=nont==start;
	for(auto const & prod:sym_production[nont])
	{ 

		int curr_mask=1;
		const string & begin=prod[0];
		int j;
		for(j=1;j<prod.size()&&prod[j]!=nont;j++);
		j++;
		
		for(;j<prod.size()&&(curr_mask&1);j++)
		{
			const string & child=prod[j];
			int child_mask=0;
			if(terminals.find(child)!=terminals.end())
				child_mask=1<<terminals[child];
			else
				child_mask=first_set[child];
			curr_mask^=1;
			curr_mask|=child_mask;
		}

		if(curr_mask&1)
		{
			curr_mask^=1;
			curr_mask|=follow_calc(begin);
		}

		final_mask|=curr_mask;
	}

	return follow_set[nont]=final_mask;
}	

int calc(string const & nont)
{
	if(first_set.count(nont))
		return first_set[nont];
	if(terminals.find(nont)!=terminals.end())
		return first_set[nont]=1<<terminals[nont];
	int final_mask=0;
	for(auto & prod:productions[nont])
	{
		int curr_mask=1;

		for(string & child:prod)
		{
			if(!(curr_mask&1))
				break;
			curr_mask^=1;
			if(child==nont)
				continue;
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
	return first_set[nont]=final_mask;

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
	cout<<"Enter the start non-terminal"<<endl;
	cin>>start;
	
		cout<<" Enter your choice "<<endl;
		cout<<" 1. Provide LL(1) table as input "<<endl;
		cout<<" 2. Provide LL(1) grammar as input "<<endl;
		
		int choice;
		cin>>choice;
		if(choice == 2)
		{
				int p;
				cout<<"Enter the number of productions"<<endl;
				cin>>p;
				vector<string> temp;
				string aux;
				
				cout<<"Enter all the productions "<<endl;
				for(int i=1;i<=p;i++)
				{
					
					temp.clear();aux.clear();
					cin>>str;
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
					productions[left_symbol].pb(temp);
			
			
					for(auto & sym:temp)
						sym_production[sym].pb(curr);
			
				}
			
				
			
				for(const string &nont:non_terminals)
				{
					if(first_set.count(nont))
						continue;
					calc(nont);	
				}
			
				for(const string &nont:non_terminals)
					follow_calc(nont);
			
			
				// Compute The LR Table
			
				
			
			
				for(const string &nont:non_terminals)
				{
					for(auto const & prod:productions[nont])
					{
						int curr=1;
						for(const string &ch:prod)
						{
							if(!(curr&1))
								break;
							curr^=1;
							curr|=calc(ch);
						}
						if(curr&1)
						{
							curr^=1;
							curr|=follow_set[nont];
						}
						for(int i=0;i<=t;i++)
							if(curr&(1<<i))
								table[nont][i]=prod;
					}
				}


				cout<<"The LL(1) Parsing Table is "<<endl;
				for(auto const & te:terminals)
					cout<<"   "<<te.first<<" |";
				cout<<endl;
				for(const string &nont:non_terminals)
				{
					cout<<nont<<" : ";
					for(auto const & te:terminals)
					{
						if(!table[nont].count(te.second))
							cout<<" - ";
						else
						{
							vector<string> const & prod=table[nont][te.second];
							for(int i=0;i<prod.size();i++)
								cout<<prod[i]<<" ";
						}
						cout<<" | ";
					}
			
					cout<<endl;
				}

		}
		else
		{
			vector<string> temp;
			string aux;
			for(string const & nterm:non_terminals)
			{
				cout<<nterm<<" : ";
				for(auto const & term: terminals)
				{
	
					temp.clear();aux.clear();
					cin>>str;
					if(str=="-")
						continue;
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
					table[nterm][term.second]=temp;
				}
			}
		}
		
	
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
		cout<<" STACK : ";
		for(auto const &item:st)
			cout<<item<<" ";
		cout<<" , STRING :";
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
			if(table.count(symbol) &&  table[symbol].count(terminals[token]) )
			{
				st.pop_back();
				vector<string> const &prod = table[symbol][terminals[token]];
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

	return 0;
}