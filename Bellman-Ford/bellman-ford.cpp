#include <bits/stdc++.h>
using namespace std;
/*
 * Complexity: 
 *   O(VE)
 */

#define fr first
#define sc second
#define inf ((int)1e9)
#define nax 100

int n;
vector<int> dist;
vector<vector<pair<int,int>>> adj;

int BellmanFord(int src) {
   fill(dist.begin(), dist.end(), inf);
   dist[src] = 0;
   // (V-1 iteration to calculate shortest path) + 1 iteration to check Neg-Cycle
	for(int i=0 ; i<n ; i++) {
		bool change=false;
		for(int u=0 ; u<n ; u++)
			for(auto [v, w]:adj[u]) {
				if(dist[v] > dist[u]+w) {
					dist[v] = dist[u]+w;
					change=true;
				}
			}
		if(!change) return 0; // early exit 
	}
	return -1; // negative cycle
}

