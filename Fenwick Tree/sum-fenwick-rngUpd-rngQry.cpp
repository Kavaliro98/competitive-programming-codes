#include <bits/stdc++.h>
using namespace std;

/*
 * Sum fenwick tree supporting range update & range query
 * source : https://kartikkukreja.wordpress.com/2013/12/02/range-updates-with-bit-fenwick-tree/
 */

struct Fenwick{
	int n;
	vector<int> fn1,fn2;
	Fenwick(int n): n(n){
		fn1.resize(n+1);
		fn2.resize(n+1);
	}
	void upd(int i, int inc, vector<int>& fn){
		for(;i<=n;i+=i&-i) fn[i]+=inc;
	}
	void upd(int i, int j, int inc){
		upd(i, inc, fn1); upd(j+1, -inc, fn1);
		upd(i, inc*(i-1), fn2); upd(j+1, -inc*j, fn2);
	}
	int rsq(int i){
		int ret=0;
		for(int j=i;j;j-=j&-j) ret+=fn1[j]; ret*=i;
		for(int j=i;j;j-=j&-j) ret-=fn2[j]; return ret;
	}
	int rsq(int i, int j){
		return rsq(j) - (i?rsq(i-1):0);
	}
};
