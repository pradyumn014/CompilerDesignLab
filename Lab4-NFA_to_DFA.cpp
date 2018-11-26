#include<iostream>
#include<queue>
#include<map>
#include<vector>
using namespace std;
int dfa_table[200][5];
int nfa_table[200][5];
map<int,int> id_to_new_state;
map<int,int> id_to_mask;
bool mark[200];
int cnt=0;
int max_state=10;

int closure(int mask)
{
	queue<int> q;
	for(int j=0;j<=max_state;j++)
		if((1<<j)&mask)
			q.push(j);
	int cl=0;
	while(!q.empty())
	{
		int state=q.front();
		q.pop();
		if((1<<state)&cl)
			continue;
		cl|=(1<<state);
		for(int j=0;j<=max_state;j++)
			if((1<<j)&dfa_table[state][2])
				q.push(j);
	}
	return cl;

}

int nfa_accepting_states;
vector<int> dfs_accepting_states;

int main()
{
	cout<<"Enter the NDFA Table"<<endl;
	cout<<"Enter the number of entries"<<endl;
	int n;
	cin>>n;
	cout<<" Enter each entry as initial state, symbol,final state"<<endl;
	cout<<"Enter 0 for a ,1 for b and 2 for epsilon"<<endl;

	for(int i=1;i<=n;i++)
	{
		int start,symbol,final;
		cin>>start>>symbol>>final;
		dfa_table[start][symbol]|=(1<<final);
		max_state=max(max_state,start);
		max_state=max(max_state,final);
	}	
	int F;
	cout<<"Enter the number of accepting states of the NFA"<<endl;
	cin>>F;
	cout<<"Enter the accepting states"<<endl;
	for(int i=1;i<=F;i++)
	{
		int no;
		cin>>no;
		nfa_accepting_states|=(1<<no);
	}

	queue<int > q; // 1 for new state, 0 for ndfa
	int zero_cl=closure(1);
	id_to_new_state[zero_cl]=++cnt;
	q.push(zero_cl);
	id_to_mask[cnt]=zero_cl;

	while(!q.empty())
	{
		int mask=q.front();
		q.pop();

		int id=id_to_new_state[mask];
		if(mark[id])
			continue;
		mark[id]=1;

		for(int i=0;i<=1;i++)
		{
			int send_mask=0;
			for(int j=0;j<=max_state;j++)
				if((1<<j)&mask)
					send_mask|=dfa_table[j][i];
			send_mask=closure(send_mask);
			if(!id_to_new_state[send_mask])
			{
				id_to_new_state[send_mask]=++cnt;
				id_to_mask[cnt]=send_mask;
			}
			int ch_id=id_to_new_state[send_mask];
			nfa_table[id][i]=ch_id;
			q.push(send_mask);
		}
	} 

	for(int i=1;i<=cnt;i++)
	{
		int mask_of_id=id_to_mask[i];
		if(nfa_accepting_states&mask_of_id)
			dfs_accepting_states.push_back(i);
	}

	cout<<endl;
	cout<<"The DFA transition table in terms of subset is "<<endl;
	cout<<"-----------------------------------"<<endl;
	cout<<"    State  |    a      |     b     "<<endl;
	cout<<"-----------------------------------"<<endl;
	for(int i=1;i<=cnt;i++)
		cout<<bitset<11>(id_to_mask[i])<<" "<<bitset<11>(id_to_mask[nfa_table[i][0]])<<" "<<bitset<11>(id_to_mask[nfa_table[i][1]])<<endl;
	cout<<endl;
	

	cout<<"The DFA transition table is "<<endl;
	cout<<"-----------------"<<endl;
	cout<<"  State | a | b"<<endl;
	cout<<"-----------------"<<endl;
	for(int i=1;i<=cnt;i++)
		cout<<"    "<<i<<"   | "<<nfa_table[i][0]<<" | "<<nfa_table[i][1]<<endl;

	cout<<"Initial state : "<<1<<endl;
	cout<<"Accepting states : ";
	for(int id:dfs_accepting_states)
		cout<<id<<" ";
	cout<<endl;

	return 0;
}