#include <bits/stdc++.h>
using namespace std;

/*
 * Persistent sum fenwick tree
 * Complexity : Log(N)^2 per rsq
 */

#define eb emplace_back
#define fr first
#define sc second

struct fenwick{
	int n, ver=0;
	vector<vector<pair<int,int>>> fn;
	fenwick(int n): n(n) {
		fn.resize(n, vector<pair<int,int>>({{0,0}}));
		ver++;
	}
	void upd(int i, int inc) {
		for(;i<=n;i+=i&-i) fn[i].eb(ver, fn[i].back().sc+inc); ver++;
	}
	int rsq(int i, int v){
		int sum=0;
		for(;i;i-=i&-i) sum+=(upper_bound(fn[i].begin(), fn[i].end(), make_pair(v,0))-1)->sc;
		return sum;
	}
};
