#include <bits/stdc++.h>
using namespace std;
/*
 * Customizable Segment Tree Template
 * Just change the node struct & operators
 */

struct node {
	struct lazy {
      int inc;
      lazy() {inc = 0;};
      lazy(int inc): inc(inc) {}
		operator bool() const { return inc!=0; } // cast to bool
	}lzy;
   int mx;
	node() { mx=0; }  // neutral node
	node(int mx): mx(mx) {} // constructor
};

void operator+=(node::lazy& lzy, const node::lazy& acc) { // accumulate lazy updates
   lzy.inc += acc.inc;
}

node operator+(const node& lft, const node& rgt) { // merge two relaxed nodes
   return node(max(lft.mx, rgt.mx));
}

node& operator<<=(node& p, const node::lazy& lzy) { // adjust value and accumulate
   p.mx += lzy.inc;
   p.lzy += lzy;
   return p;
}


template<typename T>
struct SegTree {
#define LFT p<<1, L, (L+R)>>1
#define RGT p<<1|1, ((L+R)>>1)+1, R
	typedef typename T::lazy lazy;
	int n;
	vector<T> seg;
	SegTree<T>(int n): n(n) {
		seg.resize(n<<2);
	}

	T& build(int p, int L, int R, function<T (int)> init){
		if(L==R) return seg[p] = init(L);
		return seg[p] = build(LFT, init) + build(RGT, init);
	}

	void push(int p) {
		if(!seg[p].lzy) return;
		seg[p<<1]   <<= seg[p].lzy;
		seg[p<<1|1] <<= seg[p].lzy;
		seg[p].lzy = typename T::lazy(); // reset lazy
	}

	T qry(int i, int j, int p, int L, int R){
		if(L> j || R< i) return T();
		if(L>=i && R<=j) return seg[p];
		return push(p), qry(i, j, LFT) + qry(i, j, RGT);
	}

	T upd(int i, int j, lazy lzy, int p, int L, int R){
		if(L> j || R< i) return seg[p];
		if(L>=i && R<=j) return seg[p]<<=lzy;
		return push(p), seg[p] = upd(i, j, lzy, LFT) + upd(i, j, lzy, RGT);
	}

	// driver-functions
	T build(function<T (int)> init) { return build(1,0,n-1,init); }
	T qry(int i, int j) { return qry(i,j,1,0,n-1); }
	T upd(int i, int j, lazy z) { return upd(i,j,z,1,0,n-1); }
};

int main() {
	int n = 10;
	SegTree<node> seg(n);
	vector<int> A(n, 7);
	// build the segment tree
	seg.build([A](int idx)->node{return node(A[idx]);});
	seg.upd(0, 1, node::lazy(1));
	seg.upd(1, 1, node::lazy(1));
	int mx = seg.qry(0, n-1).mx; // = 9
}
