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
    rep(i,1,n) { 
        int u, v; cin >> u >> v;
        u--, v--;  
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }
    int root = 0;
    rep(i,0,n) if(sz(adj[i]) > 1) { 
        root = i; 
        break; 
    }

    vi lvs(n); 
    auto dfs = [&](auto &&self, int u, int p) -> void { 
        if(sz(adj[u]) == 1) { 
            lvs[u] = 1; 
            return ; 
        }
        for(int v : adj[u]) { 
            if(v == p) continue; 
            self(self, v, u); 
            lvs[u] += lvs[v]; 
        }
    };
    dfs(dfs, root, -1); 
    
    int cnt = 0; 
    rep(i,0,n) cnt += (sz(adj[i]) == 1); 

    if(cnt % 2 == 0) { 
        int ans = 0; 
        rep(i,0,n) ans += lvs[i] % 2; 
        cout << ans << "\n"; 
        return ; 
    }

    auto dfs2 = [&](auto &&self, int u, int p) -> pii { 
        if(sz(adj[u]) == 1) return {0, 1}; 
        vii ch; 
        for(int v : adj[u]) { 
            if(v == p) continue; 
            pii val = self(self, v, u); 
            ch.push_back(val); 
        }
        int take_all = 0; 
        for(auto [f, s] : ch) take_all += s; 
        
        int leave_one = 1 << 20; 
        for(auto [f, s] : ch) leave_one = min(leave_one, take_all - s + f); 
        return {leave_one + (lvs[u] % 2 == 0), take_all + (lvs[u] % 2)}; 
    };
    cout << dfs2(dfs2, root, -1).first << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
