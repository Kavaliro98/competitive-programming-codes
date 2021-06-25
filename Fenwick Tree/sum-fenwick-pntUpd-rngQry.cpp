#include <bits/stdc++.h>
using namespace std;

/*
 * Sum fenwick tree supporting point update & range query
 * Also support binary search in case of non-decreasing sequences
 */

struct Fenwick{
	int n;
	vector<int> fn;
	Fenwick(int n): n(n) {
		fn.resize(n+1, 0);
	}
   // O(n) build
   void build() { 
      for(int i=1 ; i<=n ; i++) {
         int j = i+(i&-i);
         if(j<=n) fn[j]+=fn[i];
      }
   }
   int& operator[](int i) {return fn[i];}
   
	void upd(int i, int inc) {
		for(;i<=n;i+=i&-i) fn[i]+=inc;
	}
	int rsq(int i) {
		int sum=0; for(;i;i-=i&-i) sum+=fn[i]; return sum;
	}
	int rsq(int i, int j) {
		return rsq(j) - (i==1?0:rsq(i-1));
	}
	int frsq(int i, int j) { // faster rsq
		int sum=0;
      while(i!=j) i>j ? (sum-=fn[i], i-=i&-i) : (sum+=fn[j], j-=j&-j);
		return sum;
	}
	int findG(int CumFreq){ // greatest index leq CumFreq
		int idx=0;
		int mask=1<<(31-__builtin_clz(n));
		while(mask){
			int tIdx=idx+mask;
			mask>>=1;
			if(tIdx>n) continue;
			if(CumFreq>=fn[tIdx]){
				CumFreq-=fn[tIdx];
				idx = tIdx;
			}
		}
		return idx;
	}
};
