#include<iostream>
#include<string>
using namespace std;


string category[4]={"","variable","number","operator"};
int main()
{
	string statement;
	cin>>statement;
	int currstate=0; // 0 next,1 variable,2 number,3 operator 
	int pre=0;
	statement.push_back(' ');
	for(int i=0;i<statement.length();i++)
	{
		char ch=statement[i];

		int newstate=0;
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
			newstate=1;
		else if(ch>='0'&&ch<='9')
			newstate=2;
		else if(ch==' ')
			newstate=0;
		else 
			newstate=3;

		if(newstate!=currstate)
		{
			if(currstate)
			{
				for(int j=pre;j<i;j++)
							cout<<statement[j];
				cout<<" : ";
				cout<<category[currstate]<<endl;
			}
			pre=i;
			currstate=newstate;
		}
	}
	// if(pre<statement.length())
	// {
	// 	for(int j=pre;j<statement.length();j++)
	// 		cout<<statement[j];
	// 	cout<<" : ";
	// 	cout<<category[currstate]<<endl;
	// }

	return 0;
}