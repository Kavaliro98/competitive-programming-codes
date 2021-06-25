#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;

tuple<int,int,int> getCenter() {
   int n = adj.size();
   vector<int> leaves, deg(n);
   for(int u=0 ; u<n ; u++) deg[u] = adj[u].size();
   for(int u=0 ; u<n ; u++) if(deg[u]==1) leaves.push_back(u);
   int rem = n;
   int dia = 0;
   while(rem>2) {
      rem -= leaves.size();
      vector<int> tmp;
      for(int u:leaves)
         for(int v:adj[u])
            if(--deg[v]==1) tmp.push_back(v);
      dia++;
      swap(tmp, leaves);
   }
   dia = 2*dia + rem==2;
   if(rem==1) return tuple(dia, leaves[0], leaves[0]);
   else return tuple(dia, leaves[0], leaves[1]); 
}


int main() {

   auto [d, c1, c2] = getCenter();
   if(c1 == c2) { // One Ceneter
      // ... 
   }
   else { // Two Ceneters
      // ...
   }
}
