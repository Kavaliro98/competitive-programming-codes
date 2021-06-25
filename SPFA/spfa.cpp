#include <bits/stdc++.h>
using namespace std;

#define inf ((int)1e9)

vector<int> dist, vis, inQ;
int n;
vector<vector<pair<int,int>>> adj;

int spfa(int src){
   fill(inQ.begin(), inQ.end(), 0);
	fill(vis.begin(), vis.end(), 0);
   fill(dist.begin(), dist.end(), inf);

	queue<int> q;
	q.push(src); dist[src]=0; inQ[src]=true; vis[0]=-1;
	while(!q.empty()) {
		int u=q.front(); q.pop();
      inQ[u]=0;
		if(++vis[u]==n) return -1; //Neg-Cycle
		for(auto [v, w]:adj[u]) {
			if(dist[v] > dist[u]+w) {
				dist[v] = dist[u]+w;
				if(!inQ[v]) q.push(v), inQ[v]=1;
			}
		}
	}
	return 0;
}
