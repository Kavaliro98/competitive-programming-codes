#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomata {
#define state(x) tie(len[x], lnk[x], org[x], nxt[x])
   vector<int> len, lnk, org;
   vector<map<char,int>> nxt;
   int sz, last;

   SuffixAutomata(int n) {
      sz = last = 0;
      len = lnk = org = vector<int>(n<<1);
      nxt.resize(n<<1);
      state(0) = tuple(0, -1, 0, map<char,int>());
      sz++;
   }
   int extend(int c) {
      int cur = sz++;
      state(cur) = tuple(len[last]+1, 0, 1, map<char,int>());
      int p = last;
      for( ; p!=-1 && !nxt[p].count(c) ; p=lnk[p]) nxt[p][c]=cur;
      if(p == -1) lnk[cur] = 0;
      else {
         int q = nxt[p][c];
         if(len[p]+1 == len[q]) lnk[cur] = q;
         else {
            int cpy = sz++;
            state(cpy) = tuple(len[p]+1, lnk[q], 0, nxt[q]);
            for( ; p!=-1 && nxt[p][c]==q ; p=lnk[p]) nxt[p][c]=cpy;
            lnk[q] = lnk[cur] = cpy;
         }
      }
      return last = cur;
   }
};

int main() {
   string s = "banana";

   SuffixAutomata sa(s.size());

   for(auto c:s) {
      sa.extend(c);
   }
}
