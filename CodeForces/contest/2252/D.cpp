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


void solve() {
	int n; cin >> n; 
    vl v(n); rep(i,0,n) cin >> v[i]; 
    vector<bool> good(n, false); 
    rep(i,1,n-1) {
        int nxt = abs(v[i + 1]) % 2; 
        int prv = abs(v[i - 1]) % 2; 
        good[i] = (prv == nxt); 
    }

    vl d(n); 
    rep(i,1,n) d[i] = v[i] - v[i - 1]; 
    for(int l = 0, r; l < n; l = r) { 
        r = l + 1; 
        while(r < n && good[r]) r++; 
        if(r == n) break; 
        sort(d.begin() + l + 1, d.begin() + r + 1); 
        rep(i,l+1,r+1) v[i] = v[i - 1] + d[i];  
    }
    for(auto x : v) cout << x << " "; cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
