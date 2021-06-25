#include <bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> par, rnk, siz;
	int compCnt;
	DSU(int n){
		siz.resize(n, 1);
		rnk.resize(n, 0);
		par.resize(n, 0);
		iota(par.begin(), par.end(), 0);
		compCnt=n;
	}
	int find(int x){
		return par[x]==x ? x : par[x]=find(par[x]);
	}
	void merge(int u, int v){
		int a = find(u);
		int b = find(v);
		if(a==b) return;
		compCnt--;
		if(rnk[a]>rnk[b]) swap(a, b);
		siz[b] += siz[a];
		rnk[b] += (rnk[a]==rnk[b]);
		par[a] = b;
	}
};
