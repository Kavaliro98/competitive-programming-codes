#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity :
 * * O(N. Log(N)) for building 
 * * O(1) for each query
 */

#define nax 100100
#define Log2(x) (31^__builtin_clz(x))

vector<vector<int>> adj;
vector<int> euler, depth, fIdx; // fIdx : first index

int M[2*nax][Log2(2*nax)+1];  // Euler tour size = 2*n-1

void dfs(int u, int p, int d){
   if(fIdx[u]==-1) fIdx[u]=euler.size();
   depth[u]=d;
   euler.push_back(u);
   for(auto v:adj[u])
      if(v!=p) {
         dfs(v,u,d+1);
         euler.push_back(u);
      }
}

void build(){
   int n = euler.size();
   for(int i=0 ; i<n ; i++) M[i][0]=euler[i];
   for(int j=1 ; 1<<j<=n ; j++)
      for(int i=0 ; i+(1<<j)-1<n ; i++)
         M[i][j] = depth[M[i][j-1]] < depth[M[i+(1<<j-1)][j-1]] ?
            M[i][j-1] :
            M[i+(1<<j-1)][j-1];
}


int lca(int u, int v){
   int l = fIdx[u];
   int r = fIdx[v];
   if(l>r) swap(l,r);
   int k = Log2(r-l+1);
   return depth[M[l][k]] < depth[M[r-(1<<k)+1][k]] ?
      M[l][k] :
      M[r-(1<<k)+1][k];
}
