#include <bits/stdc++.h>
using namespace std;

int A[20];
int F[1<<20];
int n;
//memory optimized, super easy to code.
int sos() {
	for(int i=0 ; i<(1<<n) ; i++) F[i] = A[i];
	for(int i=0 ; i<n ; i++)
		for(int mask=0 ; mask<(1<<n) ; mask++)
			if(mask&1<<i)
				F[mask] += F[mask^(1<<i)];
}
