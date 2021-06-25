#include <bits/stdc++.h>
using namespace std;

/* 
 * Offline query processing 
 * Complexity :
 * * O(N.Log^2(N)) for all queries
 */

vector<vector<int>> adj;

vector<set<int>> q;
vector<int> lca;

// special case : lca(u,u), handle it separately
void dfsLCA(int u, int p) { 
   for(auto v:adj[u])
      if(v!=p){
         dfsLCA(v, u);
         if(q[v].size() > q[u].size()) swap(q[u], q[v]);
         for(auto x:q[v])
            if(q[u].erase(x)) lca[x]=u;
            else q[u].insert(x);
      }
}

int main() {

   int root = 0;
   int u = 1;
   int v = 2;
   int queryNum = 10;
   
   q[u].insert(queryNum);
   q[v].insert(queryNum);
   dfsLCA(root, -1);

   int ans = lca[queryNum];
}
