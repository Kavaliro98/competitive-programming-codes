#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity : O(N)
 *
 * NOTES :
 * * All aphabet values must > 0
 * * Sequence must be extend with 3 zeros (done in build())
 * * Change the alphabet size according to the problem
 * * Make sure you convert strings to integer sequences
 * 
 * Source : https://www.cs.helsinki.fi/u/tpkarkka/publications/icalp03.pdf
 */

namespace SuffixArray{
   // stably sort a[0..n-1] to b[0..n-1] with keys in [0..K] from c
   void radixPass(int* a, int* b, int* c, int* cnt, int n, int K){ 
      memset(cnt, 0, ++K*sizeof(int));
      for(int i=0 ; i<n ; i++) cnt[c[a[i]]]++;
      for(int i=1 ; i<K ; i++) cnt[i]+=cnt[i-1];
      for(int i=n ; i-- ;    ) b[--cnt[c[a[i]]]]=a[i];
   }

   void Skew(int* s, int* SA, int* cnt, int n, int K) {
      int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2; 
      int* s12  = new int[n02 + 3];  s12[n02]= s12[n02+1]= s12[n02+2]=0; 
      int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
      int* s0   = new int[n0];
      int* SA0  = new int[n0];

      // generate positions of mod 1 and mod 2 suffixes
      // the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
      for(int i=0,j=0 ; i<n+(n0-n1) ; i++) if(i%3) s12[j++]=i;

      // lsb radix sort the mod 1 and mod 2 triples
      radixPass(s12 , SA12, s+2, cnt, n02, K);
      radixPass(SA12, s12 , s+1, cnt, n02, K);  
      radixPass(s12 , SA12, s  , cnt, n02, K); // SA12 now has all tripes sorted

      // find lexicographic names of triples
      int name=0, c0=-1, c1=-1, c2=-1;
      for(int i=0 ; i<n02 ; i++) {
         if(s[SA12[i]]!=c0 || s[SA12[i]+1]!=c1 || s[SA12[i]+2]!=c2) { // if not the same as previous triple
            name++; c0=s[SA12[i]]; c1=s[SA12[i]+1]; c2=s[SA12[i]+2];  // increase name
         }
         if(SA12[i]%3==1){ s12[SA12[i]/3]      = name; } // left  half (mod 1)
         else            { s12[SA12[i]/3 + n0] = name; } // right half (mod 2)
      }
      // s12[i] now represent the class of the i-th triple in (mod_1)_(mod_2) array
      // recurse if names are not yet unique
      if(name < n02) {
         Skew(s12, SA12, cnt, n02, name);
         // store unique names in s12 using the suffix array 
         for(int i=0 ; i<n02 ; i++) s12[SA12[i]]=i+1;
      }
      else // generate the suffix array of s12 directly
         for(int i=0 ; i<n02 ; i++) SA12[s12[i]-1]=i; 

      // s12 now represent the classes
      // SA12 now represent the suffix array of (mod_1)_(mod_2)

      // stably sort the mod 0 suffixes from SA12 by their first character
      for(int i=0, j=0 ; i<n02 ; i++) if(SA12[i]<n0) s0[j++]=3*SA12[i]; // = 1 + 3*SA12[i] - 1
      radixPass(s0, SA0, s, cnt, n0, K); 

      // merge sorted SA0 suffixes and sorted SA12 suffixes
#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
      for(int p=0, t=n0-n1, k=0 ; k<n ; k++) { // t=0 or 1 depending on whether we add "$$$" or not
         int i = GetI(); // pos of current offset 12 suffix
         int j = SA0[p]; // pos of current offset 0  suffix
         if(SA12[t] < n0 ?
            tie(s[i],       s12[SA12[t] + n0]) <= tie(s[j],       s12[j/3]) :
            tie(s[i],s[i+1],s12[SA12[t]-n0+1]) <= tie(s[j],s[j+1],s12[j/3+n0]))
         { // suffix from SA12 is smaller
            SA[k]=i; t++;
            if(t==n02) for(k++ ; p<n0 ; p++,k++) SA[k]=SA0[p]; // done --- only SA0 suffixes left   
         } 
         else { 
            SA[k]=j; p++; 
            if(p==n0) for(k++ ; t<n02 ; t++,k++) SA[k]=GetI(); // done --- only SA12 suffixes left
         }
      }
      delete [] s12;
      delete [] SA12;
      delete [] SA0;
      delete [] s0;
   }
   
   vector<int> build(vector<int>& str, int alphabet_size=256) {
      int n = str.size();
      int m = max(n, alphabet_size);
      vector<int> suf(n), cnt(m+3);  // +3 for null termiators
      str.resize(n+3); // IMPORTANT
      if(n>1) Skew(&str[0], &suf[0], &cnt[0], n, m); // specail case n=1
      str.resize(n);
      return suf; 
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
