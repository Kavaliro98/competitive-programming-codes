#include <bits/stdc++.h>
using namespace std;
/*
 * This version use Priority-First Search (Dijkstra)
 * Complexity:
 *   O(E.Log|E|  2.E.Log|F|) ~ O(E^2.Log|F|) 
 * F: the final Maxflow value
 */

#define nax 1000
#define inf ((int)1e9)

vector<int> parent;
int res[nax][nax]; // adjMat for residual network
/* Initialize res as | res[u][v]= w(u,v)  : if (u-->v) exits
 *                   | res[u][v]= 0       : otherwise
 * IMPORTANT :: when using adjList method, rememeber to add the edge in both ways
 */

vector<vector<int>> adjList;

int dijkstra(int src, int dest) {
   vector<int> dist(nax, 0);
   priority_queue<pair<int,int>> pq;
   pq.push({inf, src}); dist[src]=inf;
   while(!pq.empty()) {
      auto [u, f] = pq.top(); pq.pop();
      if(u==dest) return dist[u];
      if(f<dist[u]) continue;
      for(auto v:adjList[u]) {
         if(min(res[u][v], dist[u]) > dist[v]) {
            dist[v] = min(res[u][v], dist[u]);
            parent[v]=u;
            pq.push({dist[v], v});
         }
      }
   }
   return 0;
}

int MaxFlow(int src, int dest){
   int max_flow=0;
   while(true) {
      fill(parent.begin(), parent.end(), -1);
      parent[src] = -2; 

      int inc_flow=dijkstra(src, dest);
      if(!inc_flow) break;
      
      max_flow += inc_flow;
      for(int u=dest ; u!=src ; u=parent[u]){
         res[parent[u]][u] -= inc_flow;
         res[u][parent[u]] += inc_flow;
      }
   }
   return max_flow;
}
