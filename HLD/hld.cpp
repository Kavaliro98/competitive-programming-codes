#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back

vector<vector<int>> adj;

struct HLD {
	vector<int> parent, depth, heavy, head, pos, rpos;
	int cur_pos;
	int ON_EDGE=0;
	void init(int n){
		parent.resize(n); head.resize(n);
		depth.resize(n);   pos.resize(n);
		heavy.resize(n, -1);   cur_pos=0;
		rpos.resize(n);// reverse mapping
		dfs(0); decompose(0,0);
	}
	int dfs(int u){
		int sz = 1, mx = 0;
		for(auto v:adj[u])
			if(v!=parent[u]){
				parent[v]=u; depth[v]=depth[u]+1;
				int x = dfs(v);
				sz += x;
				if(x > mx) mx=x, heavy[u]=v;
			}
		return sz;
	}
	void decompose(int u, int h){
		head[u]=h; rpos[pos[u]=cur_pos++]=u;
		if(heavy[u]!=-1)
			decompose(heavy[u], h);
		for(auto v:adj[u])
			if(v!=parent[u] && v!=heavy[u])
				decompose(v, v);
	}
	vector<pair<int,int>> getRanges(int u, int v) { // in order, from u to v
		int swaps=0;
		vector<pair<int,int>> a, b;
		for( ; head[u]!=head[v] ; v=parent[head[v]]) {
			if(depth[head[u]] > depth[head[v]]) swap(u,v), swap(a, b), swaps++;
			b.eb(pos[head[v]], pos[v]);
		}
		if(depth[u] > depth[v]) swap(u,v), swap(a, b), swaps++;
		if(!(ON_EDGE && u==v)) {
			b.eb(pos[u]+ON_EDGE, pos[v]);
		}
		if(swaps%2) swap(a, b);
		a.insert(a.end(), b.rbegin(), b.rend());
		return a;
	}
}hld;


