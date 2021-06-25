#include <bits/stdc++.h>
using namespace std;

#define nax 100100

struct LiChao {
   typedef complex<int> Line;
   int dot(Line a, Line b) { return (conj(a)*b).real(); }
   int f(Line a, int x)    { return dot(a, {x, 1}); } 
   Line LiChao[nax<<2];

   // corresponde to range [L, R) ... R not included
   // add new Line (you can tweak it to add some other curves or line segments)
   void add(Line c, int p, int L, int R) {
      int m = L+R>>1;
      bool lef = f(c, L) < f(LiChao[p], L);
      bool mid = f(c, m) < f(LiChao[p], m);
      if(mid)      swap(LiChao[p], c);
      if(R-L==1)   return;
      if(lef!=mid) add(c, p<<1,   L, m);
      else         add(c, p<<1|1, m, R); 
   }
   
   int rmnq(int x, int p, int L, int R) {
      int m = L+R>>1;
      if(R-L==1) return f(LiChao[p], x);
      if(x<m)    return min( f(LiChao[p], x), rmnq(x, p<<1,   L, m) );
      else       return min( f(LiChao[p], x), rmnq(x, p<<1|1, m, R) );
   }
};
