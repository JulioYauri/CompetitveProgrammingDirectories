#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll; 
typedef vector<ll> vl; 
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<pii> vii;

vi pf(const string &s) { 
	int n = sz(s); 
	vi pi(n); 
	rep(i,1,n) { 
		int j = pi[i - 1]; 
		while(j > 0 && s[i] != s[j]) j = pi[j - 1]; 
		if(s[i] == s[j]) j++; 
		pi[i] = j; 
	}
	return pi; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	string s; cin >> s; 
	int n; cin >> n; 
	vvi ps(2); 
	vi pref(sz(s)), suf(sz(s));
	int ans = 0;  
	rep(_,0,n) { 
		string t; cin >> t; 
		if(sz(t) == 1) continue; 
		rep(it,0,2) { 
			string tmp = t + '#' + s; 
			ps[it] = pf(tmp); 
			if(it == 0) { 
				rep(i,0,sz(s)) pref[i] = ps[it][i + sz(t) + 1]; 
			}else{ 
				rep(i,0,sz(s)) suf[i] = ps[it][i + sz(t) + 1]; 
			}
			reverse(all(s)); 
			reverse(all(t)); 
		}
		reverse(all(suf)); 
		int max_pref = 0; 
		rep(i,0,sz(s)) { 
			if(suf[i] + max_pref >= sz(t)) { 
				ans++; 
				break; 
			}
			max_pref = max(max_pref, pref[i]); 
		}
	}	
	cout << ans << "\n"; 
}
