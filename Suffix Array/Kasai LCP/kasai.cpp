#include <bits/stdc++.h>
using namespace std;

namespace SuffixArray {
   vector<int> kasaiLcp(vector<int>& str, vector<int>& suf){
      int n = suf.size();
      vector<int> rnk(n), lcp(n);
      int k=0;
      for(int i=0 ; i<n ; i++) rnk[suf[i]]=i;
      for(int i=0 ; i<n ; i++)
         if(rnk[i]==n-1) k=0;
         else {
            int j = suf[rnk[i]+1];
            while( i+k<n && j+k<n && str[i+k]==str[j+k] ) k++;
            lcp[rnk[i]]=k;
            if(k) k--;
         }
      return lcp;
   }
}

int main()
{
	string s = "banana";
   // You need to append terminal if you want to use BWT
   // s += "$"; 
   vector<int> v(s.begin(), s.end());
	// auto suf = SuffixArray::build(v);
   auto lcp = SuffixArray::kasaiLcp(v, suf);
	// ...
}
