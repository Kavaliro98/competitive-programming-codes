#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity : 
 * * O(N . Log(N)) for building  
 * * O(Log(N)) for each query
 */

vector<vector<int>> adj;

#define log(x) (31^__builtin_clz(x))

struct LCA {
   int n, lg;
   vector<int> lev;
   vector<vector<int>> par;
   vector<vector<int>>& adj;
   LCA(int root, vector<vector<int>>& adj): n(adj.size()),
                                            lg(log(n)),
                                            adj(adj) {
      lev.resize(n);
      par.resize(n, vector<int>(lg+1, -1));
      dfs(root, root, 0);
   }

   void dfs(int u, int p, int d) {
      lev[u] = d;
      par[u][0] = p;
      for(int j=1 ; 1<<j<n ; j++)
         if(par[u][j-1]!=-1)
            par[u][j] = par[ par[u][j-1] ][ j-1 ];
      for(auto v:adj[u])
         if(v!=p) dfs(v,u,d+1);
   }
   
   int get(int u, int v) {
      if(lev[u]<lev[v]) swap(u,v);

      int diff = lev[u]-lev[v];
      for(int i=lg ; i>=0 ; i--)
         if(diff&1<<i) u=par[u][i];

      if(u==v) return u;

      for(int i=lg ; i>=0 ; i--)
         if(par[u][i]!=-1 && par[u][i]!=par[v][i])
            u=par[u][i], v=par[v][i];
      
      return par[u][0];
   }
   
};

int main()
{
   // Usage
   LCA lca(0, adj);
   int u = 1;
   int v = 2;
   int c = lca.get(u, v);
}
