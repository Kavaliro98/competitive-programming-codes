#include <bits/stdc++.h>
using namespace std;

/*
 * Used for Divide and Conqure Problems 
 * query for mid point is in O(1)
 */
#define Log2(x) (31-__builtin_clz(x))
vector<int> A;
struct DST{
	int n,h;
	vector<vector<int>> M;
	DST(int n): n(n){
		M.resize(Log2(n)+1, vector<int>(n, 0));
	}
	void build(){
		h = Log2(n); h += 1<<h != n;
		int N = 1<<h;
		for(int i=0 ; i<N ; i++) M[0][i]=A[i]; // special case for l==r
		for(int j=1 ; j <= h ; j++)
			for(int m=N>>j ; m<n ; m+=N>>j-1) // m : middle point | N>>j : half's length
			{
				int sumR=0;
				for(int i=0 ; i<(N>>j) ; i++)
				   M[j][m+i] = sumR+=A[m+i];
				
				int sumL=0;
				for(int i=0 ; i<(N>>j) ; i++)
				   M[j][m-i-1] = sumL+=A[m-i-1];
			}
	}
	int qry(int l, int r){
		int j = l==r ? 0 : h-Log2(l^r);
		if(l==r) return A[l];
		return M[j][l]+M[j][r];
	}
};
