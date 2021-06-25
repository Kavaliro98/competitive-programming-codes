#include <bits/stdc++.h>
using namespace std;

/*
 * hilbertOrder is an alternative sorting order for Mo's algorithm
 * it usually runs faster than normal block order 
 * Source : https://codeforces.com/blog/entry/61203
 */


inline int64_t hilbertOrder(int x, int y, int pow=21, int rotate=0) {
	if (pow == 0) return 0;
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
} // TSP approximation

// NOTE: don't calculate block size in runtime, beacuse compilers make well optimization on dividing over constants
#define BLOCK 555 // ~ srqt(10^5)

struct query{
	int l, r, idx;
	int block;
	// int64_t h_order; (for hilber Order)
	query(int l, int r, int idx): l(l), r(r), idx(idx) {
		block = l/BLOCK;
		// h_order = hilbertOrder(l ,r);
	}
	bool operator<(const query& o) const{
		return tie(block, r) < tie(o.block, o.r);
		// return h_ordre < o.h_order;
	}
};

vector<int> A;
vector<int> cnt;
vector<query> Q;
vector<int> ans;
int res;

void inline add(int i) {
	cnt[A[i]]++;
	if (cnt[A[i]] == 1)
		res++;
}
void inline remove(int i) {
	cnt[A[i]]--;
	if (cnt[A[i]] == 0)
		res--;
}

void process() {
	sort(Q.begin(), Q.end());
	int curL = 1, curR = 0; // tricky initialization (Or make curL=0, curR=-1)
	for(auto [l,r,idx,_]:Q) { 
		while (curL < l) remove(curL++);
		while (curL > l) add(--curL);
		while (curR < r) add(++curR);
		while (curR > r) remove(curR--);
		ans[idx] = res;
	}
}


