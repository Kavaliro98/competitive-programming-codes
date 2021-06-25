#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

vector<vector<pair<int, int>>> adj;
vector<int> D;
#define node tuple<int,int>
void dijkstra(int src){
   priority_queue<node, vector<node>, greater<node>> q;
   fill(D.begin(), D.end(), inf);
   D[src]=0; q.push({0, src});
   while(!q.empty()) {
		auto [d, u] = q.top(); q.pop();
		if(d > D[u]) continue;
		for(auto [v, w]:adj[u]) {
			if(D[v] > D[u]+w) {
				D[v] = D[u]+w;
				q.push({D[v], v});
			}
		}
   }
}
