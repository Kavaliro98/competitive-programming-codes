#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;


vector<int> dfs_num, dfs_low;
int id;
int artic_cnt, bridge_cnt;

void artic(int u, int par=-1){
   int isArtic = 0;
   int children = 0;
   dfs_num[u]=dfs_low[u]=++id;
   for(auto v:adj[u])
   {
      if(v==par) continue; // bi-directional edge
      if(!dfs_num[v]) // un-visited
      {
         children++;
         artic(v, u);
		 
         if(dfs_low[v] >= dfs_num[u]) // Articulation Point
            isArtic = 1;
         if(dfs_low[v] > dfs_num[u]) // Bridge
            bridge_cnt++;
		 
         dfs_low[u] = min(dfs_low[u], dfs_low[v]);
      }
      else // (back/cross/forward) edge
         dfs_low[u] = min(dfs_low[u], dfs_low[v]);
   }
   if((par==-1 && children>1) || (par!=-1 && isArtic))
      artic_cnt++;
}
