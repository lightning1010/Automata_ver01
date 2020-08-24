
#include "regex-to-dfa.h"

void print_struct(nst temp)
{
	cout << "###################### print_struct " << endl;
	cout << "########## struct_name.a[0]" << endl;
	for (int i = 0; i < temp.a[0].size(); i++)
	{
		cout << "###### temp.a[0][" << i << "] = " << temp.a[0][i] << endl;
	}
	cout << "########## struct_name.a[1]" << endl;
	for (int i = 0; i < temp.a[1].size(); i++)
	{
		cout << "###### temp.a[1][" << i << "] = " << temp.a[1][i] << endl;
	}
	cout << "########## struct_name.e" << endl;
	for (int i = 0; i < temp.e.size(); i++)
	{
		cout << "###### temp.e[" << i << "] = " << temp.e[i] << endl;
	}
	cout << "bool f = " << temp.f << endl;
}

void print_vector_struct(vector<nst> temp)
{
	cout << "############################### print_vector_struct " << endl;
	for (int i = 0; i < temp.size(); i++)
	{
		cout << "			############ struct vector temp[" << i << "] : " << endl;
		for (int j = 0; j < temp[i].a[0].size(); j++)
		{
			cout << "########### temp[" << i << "].a[0][" << j << "] = " << temp[i].a[0][j] << endl;
		}
		for (int k = 0; k < temp[i].a[1].size(); k++)
		{
			cout << "########### temp[" << i << "].a[1][" << k << "] = " << temp[i].a[1][k] << endl;
		}
		for (int l = 0; l < temp[i].e.size(); l++)
		{
			cout << "########### temp[" << i << "].e[" << l << "] = " << temp[i].e[l] << endl;
		}
		cout << "########### temp[" << i << "].bool f = " << temp[i].f << endl;
	}
}

void PrintStack(stack<int> s)
{
	// If stack is empty then return 
	if (s.empty())
		return;


	int x = s.top();

	// Pop the top element of the stack 
	s.pop();

	// Recursively call the function PrintStack 
	PrintStack(s);

	// Print the stack element starting 
	// from the bottom 
	cout << x << " ";

	// Push the same element onto the stack 
	// to preserve the order 
	s.push(x);
}

void custom_clear() {
	for (int i = 0; i<100; i++) cout << endl;
}

/***************************** regex to nfa ****************************/

string insert_concat(string regexp) {
	//cout << "######################### regex to nfa ######################" << endl;
	//cout << "############ insert_concat function " << endl;
	//cout << "############ regexp tring = " << regexp << endl;
	string ret = "";
	char c, c2;
	for (unsigned int i = 0; i<regexp.size(); i++) {
		c = regexp[i];
		//cout << "########### c = regexp[" << i << "] = " << regexp[i] << endl;
		if (i + 1<regexp.size()) {
			c2 = regexp[i + 1];
			//cout << "########### c2 = regexp[" << i + 1 << "] = " << regexp[i + 1] << endl;
			ret += c;
			if (c != '('&&c2 != ')'&&c != '+'&&c2 != '+'&&c2 != '*') {
				ret += '.';
			}
		}
	}
	ret += regexp[regexp.size() - 1];
	//cout << "############ ret = " << ret << endl;
	return ret;
}

void character(int i)
{
	//cout << "################################## character ###################### " << endl;
	//cout << "############ i = " << i << endl;
	nfa.push_back(init_nfa_state);   //cout << "############ i = " << i << " init_nfa_state.a[0][0] = " << init_nfa_state.a[0][0] << endl;
	nfa.push_back(init_nfa_state);	//cout << "############ i = " << i << " init_nfa_state.a[0][0] = " << init_nfa_state.a[0][0] << endl;
	nfa[nfa_size].a[i].push_back(nfa_size + 1);	//cout << "############ nfa_size + 1 = " << nfa_size + 1 << endl;
	st.push(nfa_size);
	nfa_size++;
	st.push(nfa_size);
	nfa_size++;				//cout << "############ nfa_size  = " << nfa_size << endl;

	//print_struct(init_nfa_state);
	//print_vector_struct(nfa);

	//cout << "##################################### Print Stack st ###################" << endl;
	//PrintStack(st);
	//cout << endl;
}

void union_()
{
	//cout << "#################################### union ###################### " << endl;

	nfa.push_back(init_nfa_state);
	nfa.push_back(init_nfa_state);
	int d = st.top(); st.pop();	//cout << "############ d = " << d << endl;
	int c = st.top(); st.pop();	//cout << "############ c = " << c << endl;
	int b = st.top(); st.pop();	//cout << "############ b = " << b << endl;
	int a = st.top(); st.pop();	//cout << "############ a = " << a << endl;
	nfa[nfa_size].e.push_back(a);
	nfa[nfa_size].e.push_back(c);
	nfa[b].e.push_back(nfa_size + 1);
	nfa[d].e.push_back(nfa_size + 1);
	st.push(nfa_size);
	nfa_size++;
	st.push(nfa_size);
	nfa_size++;

	//print_struct(init_nfa_state);
	//print_vector_struct(nfa);

	//cout << "##################################### Print Stack st ###################" << endl;
	//PrintStack(st);
	//cout << endl;
}

void concatenation()
{
	//cout << "################################# concatenation ###################### " << endl;

	int d = st.top(); st.pop();	//cout << "############ d = " << d << endl;
	int c = st.top(); st.pop();	//cout << "############ c = " << c << endl;
	int b = st.top(); st.pop();	//cout << "############ b = " << b << endl;
	int a = st.top(); st.pop();	//cout << "############ a = " << a << endl;
	nfa[b].e.push_back(c);
	st.push(a);
	st.push(d);

	//print_struct(init_nfa_state);
	//print_vector_struct(nfa);

	//cout << "##################################### Print Stack st ###################" << endl;
	//PrintStack(st);
	//cout << endl;
}

void kleene_star()
{
	//cout << "################################### kleene_star ###################### " << endl;

	nfa.push_back(init_nfa_state);
	nfa.push_back(init_nfa_state);
	int b = st.top();	//cout << "############ b = " << b << endl;
	st.pop();
	int a = st.top();		//cout << "############ a = " << a << endl;
	st.pop();
	nfa[nfa_size].e.push_back(a);							//cout << "############ nfa_size = " << nfa_size << endl;
	nfa[nfa_size].e.push_back(nfa_size + 1);		//cout << "############ nfa_size + 1 = " << nfa_size + 1 << endl;
	nfa[b].e.push_back(a);
	nfa[b].e.push_back(nfa_size + 1);
	st.push(nfa_size);
	nfa_size++;
	st.push(nfa_size);
	nfa_size++;

	//print_struct(init_nfa_state);
	//print_vector_struct(nfa);

	//cout << "##################################### Print Stack st ###################" << endl;
	//PrintStack(st);
	//cout << endl;

}

void postfix_to_nfa(string postfix)
{
	//cout << "#################### postfix_to_nfa ###################### " << endl;
	//cout << "############# postfix = " << postfix << endl;

	for (unsigned int i = 0; i<postfix.size(); i++)
	{
		switch (postfix[i])
		{
		case 'a':
		case 'b': character(postfix[i] - 'a'); break;
		case '*': kleene_star(); break;
		case '.': concatenation(); break;
		case '+': union_();
		}
	}
}

void display_nfa()
{
	cout << endl << endl;
	cout << "Phase 1: regex to nfa conversion using thompson's construction algorithm\n";
	cout << "------------------------------------------------------------------------\n";
	cout << "State\t|\ta\t|\tb\t|\teps\t|accepting state|" << endl;
	cout << "------------------------------------------------------------------------\n";
	for (unsigned int i = 0; i<nfa.size(); i++)
	{
		cout << i << "\t|\t";
		for (unsigned int j = 0; j<nfa[i].a[0].size(); j++)cout << nfa[i].a[0][j] << ' ';
		cout << "\t|\t";
		for (unsigned int j = 0; j<nfa[i].a[1].size(); j++)cout << nfa[i].a[1][j] << ' ';
		cout << "\t|\t";
		for (unsigned int j = 0; j<nfa[i].e.size(); j++)cout << nfa[i].e[j] << ' ';
		cout << "\t|\t";
		if (nfa[i].f)cout << "Yes"; else cout << "No";
		cout << "\t|\n";
	}
	cout << "------------------------------------------------------------------------\n";
}

int priority(char c) {
	switch (c) {
	case '*': return 3;
	case '.': return 2;
	case '+': return 1;
	default: return 0;
	}
}

string regexp_to_postfix(string regexp)
{
	//cout << "########################## regexp_to_postfix " << endl;
	string postfix = "";
	stack<char> op;
	char c;
	for (unsigned int i = 0; i<regexp.size(); i++)
	{
		switch (regexp[i])
		{
		case 'a':
		case 'b':
			postfix += regexp[i]; break;
		case '(':
			op.push(regexp[i]); break;
		case ')':
			while (op.top() != '(') {
				postfix += op.top();
				op.pop();
			}
			op.pop();
			break;
		default:
			while (!op.empty()) {
				c = op.top();
				if (priority(c) >= priority(regexp[i])) {
					postfix += op.top();
					op.pop();
				}
				else break;
			}
			op.push(regexp[i]);
		}
		//cout << "###############" << regexp[i] << ' ' << postfix << endl;
	}
	while (!op.empty())
	{
		postfix += op.top();
		op.pop();
	}
	//cout << "############ postfix = " << postfix << endl;
	return postfix;
}

/***************************** nfa to dfa ****************************/

void print_dfa() {
	cout << endl;
	cout << "############################ DFA #################################" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "STATE\t|\t" << "a" << "\t|\t" << "b" << "\t|\t" << "FINAL" << "\t|" << endl;
	cout << "---------------------------------------------------------" << endl;
	for (int i = 0; i<dfa.size(); i++) {
		cout << i << "\t|\t" << dfa[i].a[0] << "\t|\t" << dfa[i].a[1] << "\t|\t" << dfa[i].f << "\t|" << endl;
	}
	cout << "---------------------------------------------------------" << endl;
}


void epsilon_closure(int state, set<int>&si) {
	//cout << "############################ epsilon_closure ##################### " << endl;
	for (unsigned int i = 0; i<nfa[state].e.size(); i++) {
		if (si.count(nfa[state].e[i]) == 0) {
			si.insert(nfa[state].e[i]);
			//cout << "############### nfa[" << state << "].e[" << i << "] = " << nfa[state].e[i] << endl;
			epsilon_closure(nfa[state].e[i], si);
		}
	}
}

set<int> state_change(int c, set<int>&si) {
	set<int> temp;
	if (c == 1) {
		for (std::set<int>::iterator it = si.begin(); it != si.end(); ++it) {
			for (unsigned int j = 0; j<nfa[*it].a[0].size(); j++) {
				temp.insert(nfa[*it].a[0][j]);
			}
		}
	}
	else {
		for (std::set<int>::iterator it = si.begin(); it != si.end(); ++it) {
			for (unsigned int j = 0; j<nfa[*it].a[1].size(); j++) {
				temp.insert(nfa[*it].a[1][j]);
			}
		}
	}
	return temp;
}


void nfa_to_dfa(set<int>&si, queue<set<int> >&que, int start_state) {
	//cout << "######################################### nfa_to_dfa ###################" << endl;

	map<set<int>, int> mp;
	mp[si] = -1;
	set<int> temp1;
	set<int> temp2;
	int ct = 0;
	si.clear();
	si.insert(0);
	epsilon_closure(start_state, si);
	if (mp.count(si) == 0) {
		mp[si] = ct++;
		que.push(si);
	}
	int p = 0;
	bool f1 = false;
	while (que.size() != 0) {
		dfa.push_back(init_dfa_state);
		si.empty();
		si = que.front();
		f1 = false;
		for (set<int>::iterator it = si.begin(); it != si.end(); ++it) {
			if (nfa[*it].f == true)
				f1 = true;
		}
		dfa[p].f = f1;
		temp1 = state_change(1, si);
		si = temp1;
		for (set<int>::iterator it = si.begin(); it != si.end(); ++it) {
			epsilon_closure(*it, si);
		}
		if (mp.count(si) == 0) {
			mp[si] = ct++;
			que.push(si);
			dfa[p].a[0] = ct - 1;
		}
		else {
			dfa[p].a[0] = mp.find(si)->second;
		}
		temp1.clear();

		si = que.front();
		temp2 = state_change(2, si);
		si = temp2;
		for (set<int>::iterator it = si.begin(); it != si.end(); ++it) {
			epsilon_closure(*it, si);
		}
		if (mp.count(si) == 0) {
			mp[si] = ct++;
			que.push(si);
			dfa[p].a[1] = ct - 1;
		}
		else {
			dfa[p].a[1] = mp.find(si)->second;
		}
		temp2.clear();
		que.pop();
		p++;
	}
	for (int i = 0; i<p; i++) {
		if (dfa[i].a[0] == -1)dfa[i].a[0] = p;
		if (dfa[i].a[1] == -1)dfa[i].a[1] = p;
	}
	dfa.push_back(init_dfa_state);
	dfa[p].a[0] = p;
	dfa[p].a[1] = p;
	//cout<<"######################### p = "<<p<<endl;
}

/***************************** min dfa ****************************/

/// Function to minimize DFA
pair<int, vector<tuple<int, int, bool> > > minimize_dfa(vector<dst> dfa) {
	//cout<<dfa.size()<<endl;
	vector<int> grp(dfa.size());    /// Group number for states
	vector<vector<int> > part(2, vector<int>());   /// Partition for groups

												   /// Initializing the groups
	part[0].push_back(0);
	for (int i = 1; i<(int)grp.size(); i++) {
		if (dfa[i].f == dfa[0].f) {
			grp[i] = 0;
			part[0].push_back(i);
		}
		else {
			grp[i] = 1;
			part[1].push_back(i);
		}
	}

	if (!part[1].size()) part.erase(part.end());

	/// Loop until no new partition is created
	bool chk = true;  /// Check if any new partition is created
	int strt = 0;   /// Starting State
	while (chk) {
		chk = false;

		/*for(int i=0; i<part.size(); i++) {
		cout<<i<<":";
		for(int j=0; j<part[i].size(); j++) {
		cout<<part[i][j]<<" ";
		} cout<<endl;
		} cout<<endl;*/
		/// Iterate over partitions and alphabets
		for (int i = 0; i<part.size(); i++) {
			for (int j = 0; j<2; j++) {
				vector<pair<int, int> > trans(part[i].size());   /// Transitions for the states of partitions
																 /// Iterate over states of partitions and find transition groups
				for (int k = 0; k<part[i].size(); k++) {
					if (dfa[part[i][k]].a[j] >= 0)
						trans[k] = make_pair(grp[dfa[part[i][k]].a[j]], part[i][k]);
					else
						trans[k] = make_pair(-1, part[i][k]);
				}
				sort(trans.begin(), trans.end());

				/// Break partition in case of different transitions
				if (trans[0].first != trans[trans.size() - 1].first) {
					chk = true;

					int k, m = part.size() - 1;

					part[i].clear();
					part[i].push_back(trans[0].second);
					for (k = 1; k<trans.size() and (trans[k].first == trans[k - 1].first); k++) {
						part[i].push_back(trans[k].second);
					}

					while (k<trans.size()) {
						if (trans[k].first != trans[k - 1].first) {
							part.push_back(vector<int>());
							m++;
						}
						grp[trans[k].second] = m;
						part[m].push_back(trans[k].second);
						k++;
					}
				}
			}
		}
	}

	for (int i = 0; i<part.size(); i++) {
		for (int j = 0; j<part[i].size(); j++) {
			if (part[i][j] == 0) strt = i;
		}
	}

	vector<tuple<int, int, bool> > ret(part.size());
	//cout<<part.size()<<endl;
	//sort(part.begin(), part.end());
	for (int i = 0; i<(int)part.size(); i++) {
		//cout<<grp[part[i][0]]<<endl;
		get<0>(ret[i]) = (dfa[part[i][0]].a[0] >= 0) ? grp[dfa[part[i][0]].a[0]] : -1;
		get<1>(ret[i]) = (dfa[part[i][0]].a[1] >= 0) ? grp[dfa[part[i][0]].a[1]] : -1;
		get<2>(ret[i]) = dfa[part[i][0]].f;
	}

	return make_pair(strt, ret);
}

void print(vector<tuple<int, int, bool> > min_dfa) {
	cout << "---------------------------------------------------------" << endl;
	cout << "State\t|\tA\t|\tB\t|\tFinal\t|" << endl;
	cout << "---------------------------------------------------------" << endl;
	for (int i = 0; i<(int)min_dfa.size(); i++) {
		cout << i << "\t|\t";
		cout << get<0>(min_dfa[i]) << "\t|\t";
		cout << get<1>(min_dfa[i]) << "\t|\t";
		if (get<2>(min_dfa[i])) cout << "Yes\t|"; else cout << "No\t|";
		cout << endl;
	}
	cout << "---------------------------------------------------------" << endl;
}


int main()
{
	//custom_clear();
	cout << endl << endl;

	string regexp, postfix;
	cout << "Regular Expression Example : ab* " << endl;
	cout << "Enter Regular Expression (w = {a,b}* ) : ";
	cin >> regexp;
	dispregex = regexp;
	regexp = insert_concat(regexp);
	postfix = regexp_to_postfix(regexp);
	//cout << "############### Postfix Expression: " << postfix << endl;
	postfix_to_nfa(postfix);

	int final_state = st.top(); st.pop();
	int start_state = st.top(); st.pop();
	//cout << "######### start_state : " << start_state << ' ' << " final_state : " << final_state << endl;
	nfa[final_state].f = 1;

	set<int> si;
	queue<set<int> > que;
	nfa_to_dfa(si, que, start_state);

	cout << endl << endl;

	pair<int, vector<tuple<int, int, bool> > > min_dfa_tmp = minimize_dfa(dfa);

	vector<tuple<int, int, bool> >  min_dfa = min_dfa_tmp.second;
	int start_st = min_dfa_tmp.first;

	getchar();
	//custom_clear();


	print_dfa();
	getchar();

	return 0;
}