#include<iostream>
#include<string>
using namespace std;
int t_table[3][2]={{0,1},{2,1},{2,2}};

int main()
{
	string str;
	cout<<"This will accept strings with  R.E 0*11* \n";
	cout<<"Enter your string\n";
	cin>>str;
	int state=0;
	for(char ch:str)
	{
		cout<<"f( "<<state<<","<<ch<<" ) = ";
		cout<<(state=t_table[state][ch-'0'])<<endl;
	}
	if(state==1)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
}