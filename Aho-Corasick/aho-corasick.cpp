 #include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
   vector<map<char, int>> nxt;
   vector<int> lnk, leaf;
   int sz=0;

   AhoCorasick(int n) { // n : total length of patterns
      nxt.resize(n);
      lnk.resize(n);
      leaf.resize(n);
      sz++;
   }

   int add_str(string s){
      int v = 0;
      for(auto c:s) {
         if(!nxt[v][c]) nxt[v][c] = sz++;
         v = nxt[v][c];
      }
      leaf[v]=1;
      return v;
   }

   void push_links(){
      lnk[0] = -1;
      queue<int> q;
      q.push(0);
      while(!q.empty()) { // bfs
         int u = q.front(); q.pop();
         for(auto [c, v]:nxt[u]){
            int j=lnk[u];
            while(j != -1 && !nxt[j].count(c)) j = lnk[j];
            if(j != -1) lnk[v] = nxt[j][c];
            else lnk[v] = 0;
            q.push(v);
         }
      }
   }

   int go(int u, char c){ // memoize queries
      if(u==-1) return 0;
      if(nxt[u].count(c)) return nxt[u][c];
      return nxt[u][c] = nxt[u].count(c) ? nxt[u][c] : go(lnk[u], c);
   }
};


int main() {
   
   vector<string> patterns;
   AhoCorasick aho(1e5); // total length of patterns
   
   for(auto s:patterns) {
      aho.add_str(s);
   }
   aho.push_links();

   // ... 
}
