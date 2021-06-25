#include <bits/stdc++.h>
using namespace std;
/*
 * Complexity 
 *	  O(MaxFlow  .  BFS)
 *	  O(V.E/2    .  (V+E))  ~  O(V.E^2)
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

int bfs(int src, int dest) {
   queue<pair<int,int>> q; q.push({src, inf});
   while(!q.empty()){
      auto [u, f] = q.front(); q.pop();
      for(auto v:adjList[u]){
         if(parent[v]==-1 && res[u][v]>0){
            parent[v]=u;
            int nf = min(f, res[u][v]);
            if(v==dest) return nf;
            q.push({v, nf});
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

      int inc_flow=bfs(src, dest);
      if(!inc_flow) break;
      
      max_flow += inc_flow;
      for(int u=dest ; u!=src ; u=parent[u]){
         res[parent[u]][u] -= inc_flow;
         res[u][parent[u]] += inc_flow;
      }
   }
   return max_flow;
}
