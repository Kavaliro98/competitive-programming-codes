#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

long long modinv(long long x) {
	long long r=1, y=MOD-2;
	for( ; y>0 ; y>>=1, x=x*x%MOD) if(y&1) r=r*x%MOD; return r;
}
