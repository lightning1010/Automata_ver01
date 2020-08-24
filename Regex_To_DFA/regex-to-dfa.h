#pragma once
#include"stdc++.h"


using namespace std;

struct nst
{
	vector<int> a[2], e;
	bool f = 0;
};

vector<nst> nfa;


struct dst
{
	int a[2] = { -1,-1 };
	bool f = 0;
};

vector<dst> dfa;

stack<int> st;

int nfa_size, dfa_size;
string dispregex;

struct nst init_nfa_state;

struct dst init_dfa_state;
// Line
void custom_clear();																						// 5
string insert_concat(string regexp);																// 11
void character(int i);																						// 31
void union_();																									// 42
void concatenation();																						// 60
void kleene_star();																							// 71
void postfix_to_nfa(string postfix);																// 89
void display_nfa();																							// 104
int priority(char c);																							// 126
string regexp_to_postfix(string regexp);															// 146
void print_dfa();																								// 181
void epsilon_closure(int state, set<int>&si);													// 193
set<int> state_change(int c, set<int>&si);														// 202
void nfa_to_dfa(set<int>&si, queue<set<int> >&que, int start_state);			// 230
pair<int, vector<tuple<int, int, bool> > > minimize_dfa(vector<dst> dfa);	// 293
void print_menu();																							// 383
void print(vector<tuple<int, int, bool> > min_dfa);										// 393
void simulate(int start_st, vector<tuple<int, int, bool> >min_dfa);				// 407

