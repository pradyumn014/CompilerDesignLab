#include<iostream>
#include<cstdio>
#include<string>
#include<sstream>
#include<map>
#include<vector>
using namespace std;

map<string,pair<string,string> > token_table;
#define fi first
#define se second
#define pb push_back


map<string,int> symbol_table;
int last=0;

string tostring ( int number ){  stringstream ss; ss<< number; return ss.str();}

int main()
{
	freopen("sourcecode.txt","r",stdin);
	vector<string> tokens;
	token_table[" "]={"ws"," - "};
	token_table["<"]={"relop","LT"};
	token_table["<="]={"relop","LE"};
	token_table["<>"]={"relop","NQ"};
	token_table[">"]={"relop","GT"};
	token_table[">="]={"relop","GE"};
	token_table["="]={"relop","EQ"};
	token_table["if"]={"if"," - "};
	token_table["then"]={"then"," - "};
	token_table["else"]={"else"," - "};
	
	string line;
	while(getline(cin,line))
	{

		line.pb(' ');
		int pre=0;
		string state="ws";
		
		for(int i=0;i<line.length();i++)
		{	
			if(i<line.length()-1&&line[i]==92&&line[i+1]==92)
				break;

			string curr_state;
			if(token_table.count(string(1,line[i])))
				curr_state=token_table[string(1,line[i])].fi;
			else 
				curr_state="id_num_key";
			if(line[i]==' '||line[i]==9)
				curr_state="ws";
			if(curr_state!=state&&pre<=i-1)
			{
				string currtoken;
				for(int j=pre;j<=i-1;j++)
					currtoken.pb(line[j]);
				
				if(token_table.count(currtoken))
				{
					tokens.pb(currtoken+ " | < "+token_table[currtoken].fi+" , "+token_table[currtoken].se + " > ");
				}
				else
				{
					bool dig=true;
					for(auto ch:currtoken)
						dig&=(ch>='0'&&ch<='9');
					if(state=="ws")
						tokens.pb(" ws < - ,- >");

					else if(!dig)
					{
						int symb=0;
						if(symbol_table.count(currtoken))
							symb=symbol_table[currtoken];
						else 
							symb=symbol_table[currtoken]=++last;
						tokens.pb("id  | < "+currtoken+ " , "+tostring(symb)+" > ");
					}
					else if(dig)
					{
						int symb=0;
						if(symbol_table.count(currtoken))
							symb=symbol_table[currtoken];
						else 
							symb=symbol_table[currtoken]=++last;
						tokens.pb("number | <"+  currtoken + " , "+tostring(symb)+" > ");
					}
					
				}
			}
			if(curr_state!=state)
			{
				pre=i;
				state=curr_state;
			}
		}	
	}

	for(auto ss:tokens)
		cout<<ss<<endl;
}