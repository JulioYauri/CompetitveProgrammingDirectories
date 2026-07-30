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
    vvi adj(n); 
    vi deg(n); 
    vii eds; 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        u--, v--; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        deg[u]++; 
        deg[v]++; 
        eds.emplace_back(u, v); 
    }
    ll ans = 0; 
    for(auto [u, v] : eds) ans += (deg[u] % 2) && (deg[v] % 2); 
    vector<bool> vis(n, false); 
    rep(i,0,n) { 
        if(vis[i] || deg[i] % 2) continue; 
        queue<int> q; 
        q.push(i); 
        vis[i] = true; 
        int total = 0; 
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            for(int v : adj[u]) { 
                if(vis[v]) continue; 
                if(deg[v] % 2) { 
                    total ++; 
                }else{ 
                    q.push(v); 
                    vis[v] = true; 
                }
            }
        }
        ans += 1LL * total * (total - 1) / 2; 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
