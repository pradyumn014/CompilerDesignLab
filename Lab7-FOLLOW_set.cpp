/*
Pradyumn Sinha
*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back

// 3
// E T F
// 5
// id + * ( )
// 4
// E=E+T
// T=F
// F=(E)
// F=id

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

void calc(string const & nont)
{
	if(first_set.count(nont))
		return ;
	
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
		vector<string> curr;
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
					curr.pb(aux);
					aux.clear();
				}
			}
		}
		productions[left_symbol].pb(temp);


		for(auto & sym:temp)
			sym_production[sym].pb(curr);

	}

	cout<<"Enter the start non-terminal"<<endl;
	cin>>start;

	for(const string &nont:non_terminals)
	{
		if(first_set.count(nont))
			continue;
		calc(nont);	
	}

	for(const string &nont:non_terminals)
		follow_calc(nont);


	cout<<"FIRST SET for each non-terminal "<<endl;
	for(const string &nont:non_terminals)
	{
		cout<<nont<<" : { ";
		int mask=first_set[nont];
		for(int i=0;i<=t;i++)
			if(mask&(1<<i))
				cout<<id_to_terminals[i]<<", ";
		cout<<"}"<<endl;
	}
	
	cout<<"FOLLOW SET for each non-terminal "<<endl;
	for(const string &nont:non_terminals)
	{
		cout<<nont<<" : { ";
		int mask=follow_set[nont];
		for(int i=0;i<=t;i++)
			if(mask&(1<<i))
				cout<<id_to_terminals[i]<<", ";
		cout<<"}"<<endl;
	}
	return 0;
}