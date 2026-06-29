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
    vvi adj(n + 1); 
    rep(i,2,n+1) { 
        int p; cin >> p; 
        adj[p].push_back(i); 
    }

    vi h(n + 1); 
    ll ans = 0; 
    auto dfs = [&](auto &&self, int u) {
        if(adj[u].empty()) { 
            h[u] = 1; 
            ans++; 
            return ;
        }
        vi hs; 
        for(auto v : adj[u]) { 
            self(self, v); 
            hs.push_back(h[v]); 
        }
        sort(all(hs)); 
        h[u] = hs.back() + 1; 
        if(sz(hs) == 1) ans++; 
        else ans += hs.end()[-2] + 1; 
    };  
    dfs(dfs, 1); 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
