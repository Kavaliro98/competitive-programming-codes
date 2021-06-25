#include <bits/stdc++.h>
using namespace std;

/* NOTES :
 * 1) Number of different substrings is sum of all edges lengths
 * 2) To distingush suffixes from substrings append terminal $
 * 
 * Source : https://codeforces.com/blog/entry/16780
 */

struct SuffixTree {
#define inf 1e9
	int n, node, pos, sz;
	vector<int> s, len, fpos, lnk;
   vector<map<int, int>> nxt;
	SuffixTree(int N): nxt(N<<1) {
      s = len = fpos = lnk = vector<int>(N<<1);
      n=node=pos=sz=0;
      len[0]=inf;
      sz++;
	}
	int make_node(int _pos, int _len){
      fpos[sz] = _pos;
      len [sz] = _len;
      return sz++;
	}
	void go_edge(){
      while(pos > len[nxt[node][s[n - pos]]]){
         node = nxt[node][s[n - pos]];
         pos -= len[node];
      }
	}
	void extend(int c){
      s[n++] = c;
      pos++;
      int last = 0;
      while(pos > 0){
         go_edge();
         int edge = s[n-pos];
         int &v = nxt[node][edge];
         int t = s[fpos[v]+pos-1];
         if(v==0) {
            v = make_node(n-pos, inf);
            lnk[last] = node;
            last = 0;
         }
         else if(t==c) {
            lnk[last] = node;
            return;
         }
         else {
            int u = make_node(fpos[v], pos-1);
            nxt[u][c] = make_node(n-1, inf);
            nxt[u][t] = v;
            fpos[v] += pos-1;
            len [v] -= pos-1;
            last = lnk[last] = v = u;
         }
         if(node==0) pos--;
         else node = lnk[node];
      }
	}
   void debug(int u=0, int t=0) {
      cerr << "(" << u << ") : " << endl;
      for(auto [c,v]:nxt[u]) {
         int bg = fpos[v];
         int en = min(fpos[v]+len[v], n);
         string ss(s.begin()+bg, s.begin()+en);
         cerr << string(t+1, '\t') << ss;
         debug(v, t+1);
      }
   }
};

bool Search(SuffixTree& ukk, string t){
   auto len=ukk.len, s=ukk.s, fpos=ukk.fpos;
   auto nxt=ukk.nxt;
   int p = 0;
   int cur = 0;
   while(p < t.size()){
      int v = nxt[cur][t[p]];
      int l = min(len[v], (int)t.size()-p);
      if(!v || !equal(t.begin()+p, t.begin()+p+l, s.begin()+fpos[v])) return false;
      p+=l;
      cur=v;
   }
   return true;
}

int main() {

   string s = "banana";

   SuffixTree ukk(s.size());
   for(auto c:s) {
      ukk.extend(c);
   }

   bool f1 = Search(ukk, "ana");
   bool f2 = Search(ukk, "nab");
   
}


