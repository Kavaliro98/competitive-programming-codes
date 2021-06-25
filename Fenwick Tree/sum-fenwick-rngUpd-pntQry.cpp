#include <bits/stdc++.h>
using namespace std;

/*
 * Sum fenwick tree supporting range update & point query
 */

struct Fenwick{
	int n;
	vector<int> fn;
	Fenwick(int n): n(n){
		fn.resize(n+1);
	}
	void _upd(int i, int v){
		for( ; i<=n ; i+=i&-i) fn[i]+=v;
	}
	// Range update: Adds v to each element in [L...R] in the array
	void upd(int L, int R, int v){
		_upd(L, v);
		_upd(R+1, -v);
	}
	// Point query: Returns the total increments at position i in the array
	int qry(int i){
		int ret=0;
		for( ; i ; i-=i&-i) ret+=fn[i];
		return ret;
	}
};
