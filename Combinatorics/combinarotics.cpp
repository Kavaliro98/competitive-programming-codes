#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

// avoid overflow
#define int long long

namespace Combinatorics
{
   vector<int> fct, inv; 

   int addmod(int  a, int b) {return (a+=b)>=MOD ? a-=MOD : a;}
   int submod(int  a, int b) {return (a-=b) < 0  ? a+=MOD : a;}
   int modadd(int& a, int b) {return (a+=b)>=MOD ? a-=MOD : a;}
   int modsub(int& a, int b) {return (a-=b) < 0  ? a+=MOD : a;}

   int fpow(int x, int p) {int r=1; for(;p;p>>=1, x=x*x%MOD) if(p&1) r=r*x%MOD; return r;}
   int modinv(int x) {return fpow(x, MOD-2);}
   
   auto CombTable(int n, int m) {
      vector<vector<int>> C(n, vector<int>(m));
      for(int i=0 ; i<n ; i++)  C[i][0]=1;
      for(int i=1 ; i<n ; i++) for(int j=1 ; j<m ; j++) C[i][j] = addmod(C[i-1][j-1], C[i-1][j]);
      return C;
   }
   
   void setup(int n) {
      fct = inv = vector<int>(n, 1);
      for(int i=2 ; i<n ; i++) fct[i] = fct[i-1]*i %MOD;
      for(int i=2 ; i<n ; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] %MOD;
   }
   
   int F(int i) { return fct[i]; }
   int C(int i, int j, auto inv = modinv) { return F(i) * inv(F(j)) %MOD * inv(F(i-j)) %MOD; }
   int I(int i) { return inv[i]; }
}

using namespace Combinatorics;

int32_t main()
{
   Combinatorics::setup(100100);

   int five_factorial = F(5);
   int five_choose_3  = C(5, 3);
   int two_inv = I(2);
   int big_num_inv = modinv(200200); // bigger than what we pre-calculated

   auto Comb = CombTable(1000, 1000);
   int x = Comb[10][5];
}
