#include <bits/stdc++.h>
using namespace std;


/* 
 * BWT can be used to get the range in the suffix array 
 * that has a prefix equal to some patter t in O(|t|)
 *
 * NOTES :
 * 1) You will need to append terminal ('$') to the string
 * 2) All s[i] must be less K
 * Source : https://codeforces.com/blog/entry/58991?#comment-425858
 */

struct BWT {
   int n;
   vector<int> cnt;
   vector<vector<int>> occ;
   BWT(vector<int>& str, vector<int>& suf, int K) {
      n = str.size();
      occ = vector<vector<int>>(n+1, vector<int>(K));
      cnt = vector<int>(K+1);
      for(int i=0 ; i<n ; i++) {
         int t = str[suf[i]==0 ? n-1 : suf[i]-1];
         if(t>=0) { // not terminal '$'
            occ[i][t]++;
            cnt[t+1]++;
         }
         occ[i+1] = occ[i];
      }
      partial_sum(cnt.begin(), cnt.end(), cnt.begin());
   }

   pair<int,int> getRange(vector<int>& t) {
      int l=0, r=n-1;
      for(int i=t.size() ; i-- ; ) {
         int ch = t[i];
         l = cnt[ch] + (l ? occ[l-1][ch] : 0) + 1;
         r = cnt[ch] + occ[r][ch];
      }
      return pair(l, r);
   }
};

int main()
{
	string s = "banana";
   // You need to append terminal if you want to use BWT
   s += "$"; 
   vector<int> v(s.begin(), s.end());
	// auto suf = SuffixArray::build(v);
   // auto lcp = SuffixArray::kasaiLcp(v, suf);

   for(auto& x:v) x-='a'; // compress the alphabet for better performance 
   BWT bwt(v, suf, 26);

   string t = "ana";
   vector<int> w(t.begin(),  t.end());
   for(auto& x:w) x-='a';
   auto [l, r] = bwt.getRange(w);
	// ...
}
