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
    vi v(n); rep(i,0,n) cin >> v[i]; 
    vi c = v; 
    sort(all(c)); 
    c.erase(unique(all(c)), c.end()) ; 
    for(int &x : v) x = lower_bound(all(c), x) - c.begin(); 

    int m = sz(c); 
    vi mn(m, -1), mx(m, -1); 
    rep(i,0,n) { 
        if(mn[v[i]] == -1) mn[v[i]] = i; 
        mx[v[i]] = i; 
    }   
    
    int ans = m; 
    for(int l = 0, r = 0; l < m; l = r) { 
        while(r < m && (r == l || mn[r] > mx[r - 1])) r++; 
        ans = min(ans, m - (r - l)); 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
