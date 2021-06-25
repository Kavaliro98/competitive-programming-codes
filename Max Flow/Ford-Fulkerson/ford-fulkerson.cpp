#include <bits/stdc++.h>
using namespace std;
/*
 * Complexity: O(E.F)
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

int dfs(int u, int dest, int mxf){
   if(u==dest) return mxf;
   for(auto v:adjList[u]){
      if(!parent[v] && res[u][v]>0){
         parent[v] = u;
         int f = dfs(v, dest, min(mxf, res[u][v]));
         if(f) return f;
      }
   }
   return 0;
}

int MaxFlow(int src, int dest){
   int max_flow=0;
   while(true) {
      fill(parent.begin(), parent.end(), -1);
      parent[src] = -2; 

      int inc_flow=dfs(src, dest, inf);
      if(!inc_flow) break;
      
      max_flow += inc_flow;
      for(int u=dest ; u!=src ; u=parent[u]){
         res[parent[u]][u] -= inc_flow;
         res[u][parent[u]] += inc_flow;
      }
   }
   return max_flow;
}
