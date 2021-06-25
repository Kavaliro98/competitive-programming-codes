#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;


int id;
int SCC_Count;
vector<int> dsc, low, on_stack, comp; 
stack<int> stk;

void tarjan(int u){
   dsc[u] = low[u] = ++id;
   stk.push(u); on_stack[u] = 1;

   for(auto v:adj[u]) {
      if(!dsc[v]) { // un-visited
         tarjan(v);
         low[u] = min(low[u], low[v]);
      }
      else if(on_stack[v]) {
         low[u] = min(low[u], low[v]);
      }
   }
   
   if(dsc[u]==low[u]){
      int v;
      do {
         v=stk.top(); stk.pop();
         on_stack[v]=0;
         comp[v]=SCC_Count;
      } while(u!=v);
      SCC_Count++;
   }
}
