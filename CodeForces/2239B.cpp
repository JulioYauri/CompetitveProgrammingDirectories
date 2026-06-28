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
    int n, d; cin >> n >> d; 
    vl a(n * 3); 
    rep(i,0,n) cin >> a[i]; 
    rep(i,n,sz(a)) a[i] = a[i - n];
    vl p = a; rep(i,1,sz(p)) p[i] += p[i - 1]; 
    ll ans = 0 ; 
    rep(i,n,2*n) { 
        ll h = 2LL * d * a[i] - (p[i + d] - p[i]) - (p[i - 1] - p[i - d - 1]) ; 
        ans += max(0LL, h); 
    }
    cout << ans << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
