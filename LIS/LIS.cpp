#include <bits/stdc++.h>
using namespace std;

vector<int> get_LIS(int n, int A[]){
	int len=0, last=0;
	vector<int> idx(n), pre(n), lis(n);
	for(int i=0 ; i<n ; i++) {
		// use upper_bound for longest non-decreasing sequence
		int pos = lower_bound(lis.begin(), lis.begin()+len, A[i]) - lis.begin();
		lis[pos] = A[i];
		idx[pos] = i;
		pre[i] = pos ? idx[pos -1] : -1;
		if(pos==len) len++, last=i;
	}
	stack<int> s;
	for( ; last!=-1 ; last=pre[last]) s.push(A[last]);
	for(int i=0 ; !s.empty() ; i++) lis[i]=s.top(), s.pop();
	lis.resize(len);
	return lis;
} 
