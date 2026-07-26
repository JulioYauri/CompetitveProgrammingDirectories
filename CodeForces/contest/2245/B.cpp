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
    int n; cin >> n ; 
    ll c; cin >> c; 
    vl v(n); rep(i,0,n) cin >> v[i]; 
    sort(all(v)); 
    vl pr = v; rep(i,1,n) pr[i] += pr[i - 1]; 
    ll ans = -(1LL << 62), total = pr.back(); 
    for(int cc = 0; cc * 2 <= n; cc++) { 
        // hago cc "dobles"
        // me quito los cc menores 
        // cerr << "hago cc: " << cc << "\n"; 
        ll cur = total - (cc == 0 ? 0 : pr[cc - 1]) - (n - cc) * c ; 
        // cerr << " cur : " << cur << "\n"; 
        ans = max(ans, cur); 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
