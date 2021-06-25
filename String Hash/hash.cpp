#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Hash{
	const int p = 31; // 53, 1331
	const int m = 1e9+9; // 1e9+7
	vector<ll> pow, h;
	
	void build(string s) {
		int n = s.size();

		pow.resize(n);
		h.resize(n);
		
		pow[0]=1;
		for(int i=1 ; i<n ; i++) pow[i] = pow[i-1]*p%m;
		h[0]=s[0]-'a'+1;
		for(int i=1 ; i<n ; i++) h[i] = (h[i-1]*p + s[i]-'a'+1)%m;
	}
	
	ll getHash(int i, int j) {
		ll ret = h[j];
		if(i) ret -= h[i-1] * pow[j-i+1];
		return (ret%m + m)%m;
	}
};
