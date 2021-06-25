/*
 * Complexity 
 *   O(V^2 E)
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Dinic {
  struct FlowEdge {
    int u, v; // from, to
    int cap, flow = 0;
    FlowEdge(int u, int v, int cap): u(u), v(v), cap(cap) {}
  };
   
  const int flow_inf = 1e18;
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  vector<int> lev, ptr;
  int n, m = 0;
  int src, snk;

  Dinic(int n, int src, int snk) : n(n), src(src), snk(snk) {
    adj.resize(n);
    lev.resize(n);
    ptr.resize(n);
  }

  void add_edge(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(m++);
    adj[v].push_back(m++);
  }

  void bfs(int src) {
    fill(lev.begin(), lev.end(), 0);
    queue<int> q; q.push(src); lev[src]=1;
    while(!q.empty()) {
       int u = q.front(); q.pop();
       for(int e:adj[u]) {
         auto [_,v,cap,flow] = edges[e];
         if(cap-flow && !lev[v]) {
           lev[v] = lev[u] + 1;
           q.push(v);
         }
       }
    }
  }
  int dfs(int u, int mxf) {
    if (u==snk) return mxf;
    for (int& i=ptr[u] ; i<(int)adj[u].size() ; i++) {
       int e = adj[u][i];
       auto [_,v,cap,flow] = edges[e];
       if(lev[u]+1==lev[v] && cap-flow) {
         int f = dfs(v, min(mxf, cap-flow));
         if(!f) continue;
         edges[e].flow += f;
         edges[e^1].flow -= f;
         return f;
       }
    }
    return 0;
  }

  int maxflow() {
    int fmax = 0;
    while (true) {
       bfs(src);
       if(!lev[snk]) break;
       fill(ptr.begin(), ptr.end(), 0);
       while (int finc=dfs(src, flow_inf)) 
         fmax += finc;
    }
    return fmax;
  }
};
