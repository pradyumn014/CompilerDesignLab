/*

Pradyumn Sinha
Limitations
 
None ,it can check for any grammar and any text.

*/

/*
Input 1 
3  
S E T
3
id 
+ 
*
4
S=E+E
E=T*T
T=id
E=id
id+id+id

Input 2 
2 
S A
3 
a b *
4 
S=A*S
A=A*S
A=a
S=b
a*a


*/

#include<bits/stdc++.h>
using namespace std;
#define pb push_back
set<string> non_terminals,terminals;
map<string,vector<vector<string> > > productions;
string text;

set<int> rec_descent(int ptr,string symbol,int tot=1)
{
	set<int> ptrs;
	if(tot>text.length())
		return ptrs;
	if(terminals.find(symbol)!=terminals.end())
	{
		if(symbol==text.substr(ptr,symbol.length()))
			ptrs.insert(ptr+symbol.length());
		return ptrs;
	}


	for(auto & prod:productions[symbol])
	{
		set<int> optrs,nptrs;
		optrs.insert(ptr);
		for(string & child_symbol:prod)
		{	
			nptrs.clear();
			for(const int &optr:optrs)
			{
				set<int> curr=rec_descent(optr,child_symbol,tot+prod.size()-1);
				for(const int &nptr:curr)
					nptrs.insert(nptr);
			}
			if(nptrs.empty())
				break;
			optrs=nptrs;
			nptrs.clear();
		}

		for(const int &optr:optrs)
			ptrs.insert(optr);
	}

	return ptrs;
}


int main()
{
	cout<<"Enter the number of non-terminals"<<endl;
	int nt;
	cin>>nt;
	cout<<"Enter the non-terminals"<<endl;
	string str;
	for(int i=1;i<=nt;i++)
	{
		cin>>str;
		non_terminals.insert(str);
	}
	cout<<"Enter the number of terminals"<<endl;
	int t;
	cin>>t;
	cout<<"Enter the terminals"<<endl;
	for(int i=1;i<=t;i++)
	{
		cin>>str;
		terminals.insert(str);
	}

	cout<<"Enter the number of productions"<<endl;
	int p;
	cin>>p;
	vector<string> temp;
	string aux;
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
				if(terminals.find(aux)!=terminals.end()||non_terminals.find(aux)!=non_terminals.end())
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

	cout<<"Enter the start symbol"<<endl;
	string start;
	cin>>start;

	cout<<"Enter the text to be parsed"<<endl;
	cin>>text;

	set<int> ptrs=rec_descent(0,start);

	if(ptrs.find(text.length())!=ptrs.end())
		printf("ACCEPTED\n");
	else 
		printf("REJECTED\n");

	return 0;

}