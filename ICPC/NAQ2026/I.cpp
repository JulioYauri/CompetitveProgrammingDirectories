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
    int n, m; cin >> n >> m; 
    vi cnt(n); 
    vii v(m); 
    rep(i,0,m) cin >> v[i].first >> v[i].second;
    for(auto [f, s] : v) { 
        if(f > s) { 
            cout << "-1\n"; 
            return; 
        }
        if(f + 1 == s) cnt[f - 1]++; 
    }
    int ans = 0; 
    rep(i,0,n-1) { 
        if(cnt[i] == 0) { 
            ans++; 
        }
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
