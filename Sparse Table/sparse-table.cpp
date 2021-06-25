#include <bits/stdc++.h>
using namespace std;

/*
 * Customizable Sparse Table
 */

#define log(x) (31-__builtin_clz(x))
#define LOGMAXN log(MAXN)

struct SparseTable{
	int n;
	vector<vector<int>> M;
	function<int (int, int)> fun;
	function<bool (int, int)> op;
	SparseTable(int n, function<bool (int, int)> op): n(n), op(op) {
		M.resize(n, vector<int>(log(n)+1));
		fun = [op](int a, int b)->int{return op(a,b) ? a : b;};
		for(int i=0 ; i<n ; i++) M[i][0]=fun(i, i);
		for(int j=1 ; (1<<j)<=n ; j++)
			for(int i=0 ; i+(1<<j)<=n ; i++)
				M[i][j] = fun(M[i][j-1], M[i+(1<<j-1)][j-1]);
	}
	int inline get(int l, int r){
		int k = log(r-l+1);
		return fun(M[l][k], M[r-(1<<k)+1][k]);
	}
};

int main() {
	// minimum sparse table
	int A[] = {1, 2, 3, 2, 5};

	// Sparse Table to get the first minimum
	SparseTable sp(5, [A](int a, int b)->bool{
      return tie(A[a], a) < tie(A[b], b);
   });

	int idx = sp.get(1, 4);
	printf("The minimum element is %d at index %d\n", A[idx], idx);
}
