#include <bits/stdc++.h>
using namespace std;

struct Centroid {
	vector<int> sz, par;
	vector<set<int>> g;
	Centroid(int n, vector<vector<int>> adj) {
		sz.resize(n);
		par.resize(n);
		for(auto &v:adj)
			g.push_back(set<int>(v.begin(), v.end()));
	}

	int dfsCentriod(int u, int p){
		sz[u]=1;
		for(auto v:g[u])
			if(v!=p) sz[u]+=dfsCentriod(v, u);
		return sz[u];
	}
 
	int nodes; // total nodes in current component
	int getCentriod(int u, int p){
		for(auto v:g[u])
			if(v!=p && sz[v]>nodes>>1)
				return getCentriod(v, u);
		return u;
	}
 
	void decompose(int u, int p){
		nodes=dfsCentriod(u, u);
		int c=getCentriod(u, u);
		par[c]=p;
		for(auto v:g[c]) {
			g[v].erase(c);
			decompose(v, c);
		}
	}
};

int main()
{
	int n = 10;
	vector<vector<int>> adj;
	// ...
	Centroid cen(n, adj);
	cen.decompose(0,-1);
	auto& parentCentroid = cen.par;
	// ...
}





