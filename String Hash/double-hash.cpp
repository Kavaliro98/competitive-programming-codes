#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct DoubleHash{
	const int p1=31, p2=1337;// 53, 1331
	const int m1=1e9+9, m2=1e9+7; // 1e9+7
	vector<ll> pow1, pow2, h1, h2;
	void build(string s) {
		int n = s.size();

		pow1.resize(n);
		h1.resize(n);
		pow1[0]=1;
		for(int i=1 ; i<n ; i++) pow1[i] = pow1[i-1]*p1%m1;
		h1[0]=s[0]-'a'+1;
		for(int i=1 ; i<n ; i++) h1[i] = (h1[i-1]*p1 + s[i]-'a'+1)%m1;


		pow2.resize(n);
		h2.resize(n);
		pow2[0]=1;
		for(int i=1 ; i<n ; i++) pow2[i] = pow2[i-1]*p2%m2;
		h2[0]=s[0]-'a'+1;
		for(int i=1 ; i<n ; i++) h2[i] = (h2[i-1]*p2 + s[i]-'a'+1)%m2;
	}
	
	pair<int, int> getHash(int i, int j){
		ll a = h1[j];
		if(i) a -= h1[i-1] * pow1[j-i+1];
		a = (a%m1 + m1)%m1;

		ll b = h2[j];
		if(i) b -= h2[i-1] * pow2[j-i+1];
		b = (b%m2 + m2)%m2;

		return make_pair(a,b);
	}
};
