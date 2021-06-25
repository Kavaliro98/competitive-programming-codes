#include <bits/stdc++.h>
using namespace std;

namespace SuffixArray {
   vector<int> build(vector<int>& s, int alphabet_size=256){
      s.push_back(0);
      int n = s.size();
      int m = max(n, alphabet_size); // First iteration hash range
      vector<int> p(n), c(n), pn(n), cn(n), cnt(m);

      for(int i=0 ; i<n ; i++) cnt[s[i]]++;
      for(int i=1 ; i<m ; i++) cnt[i]+=cnt[i-1];
      for(int i=0 ; i<n ; i++) p[--cnt[s[i]]] = i;

      c[p[0]]=0; m=1;
      for(int i=1 ; i<n ; i++)
         if(s[p[i]] != s[p[i-1]]) c[p[i]] = m++;
         else c[p[i]] = m-1;

      for(int j=0 ; 1<<j < n ; j++){
         fill(cnt.begin(), cnt.begin()+m, 0);
         for(int i=0 ; i<n ; i++) pn[i]=p[i]-(1<<j)+(1<<j>p[i]?n:0);
         for(int i=0 ; i<n ; i++) cnt[c[pn[i]]]++;
         for(int i=1 ; i<m ; i++) cnt[i]+=cnt[i-1];
         for(int i=n ; i-- ;    ) p[--cnt[c[pn[i]]]] = pn[i]; 
         cn[p[0]] = 0; m = 1;
         for(int i=1 ; i<n ; i++)
            if(c[p[i]]!=c[p[i-1]] || c[(p[i]+(1<<j))%n]!=c[(p[i-1]+(1<<j))%n]) cn[p[i]]=m++;
            else cn[p[i]] = m-1;
         swap(c, cn);
      }
      p.erase(p.begin());
      s.pop_back();
      return p;
   }
}

int main()
{
	string s = "banana";
   // You need to append terminal if you want to use BWT
   // s += "$"; 
   vector<int> v(s.begin(), s.end());
	auto suf = SuffixArray::build(v);
   // auto lcp = SuffixArray::kasaiLcp(v, suf);
	// ...
}
