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
	int n, k, src; 
    cin >> n >> k >> src; src--;  
    
    vvi adj(n); 
    rep(i,1,n) { 
        int u, v; cin >> u >> v;
        u--, v--; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    int inf = 4 * n ; 
    auto dfs = [&](auto &&self, int u, int p) -> int { 
        if(sz(adj[u]) == 1) return 0; 
        vi mins(2, inf); 
        for(int v : adj[u]) { 
            if(v == p) continue; 
            int val = self(self, v, u) + 1; 
            mins.push_back(val); 
            sort(all(mins)) ; 
            mins.pop_back(); 
        }
        if(mins[1] + mins[0] <= k + 1) return 0;  
        return mins[0]; 
    };
    cout << (dfs(dfs, src, -1) == 0 ? "YES\n" : "NO\n"); 

}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
