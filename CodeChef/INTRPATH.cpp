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

const int N = 300'000 + 5; 
const int LOG = 20; 
ll dp[N], up[N], dp2[N]; 
int jump[N][LOG], dep[N], siz[N]; 
vi adj[N]; 

void dfs1(int u, int p = -1) { 
    siz[u] = 1 ; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        jump[v][0] = u;
        dep[v] = dep[u] + 1;  
        dfs1(v, u);
        siz[u] += siz[v] ; 
    }
}

void dfs2(int u, int p = -1) { 
    if(p != -1) { 
        dp2[u] = dp2[p] - 1LL * siz[u] * (siz[p] - siz[u]);
        up[u] = dp2[u]; 
    } 
    dp2[u] += dp[u]; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        dfs2(v, u); 
    }
}

int lift(int u, int len) { 
    while(len) u = jump[u][__builtin_ctz(len)], len &= (len - 1); 
    return u; 
}

int lca(int u, int v) { 
    if(dep[v] > dep[u]) swap(u, v); 
    u = lift(u, dep[u] - dep[v]); 
    if(u == v) return u; 
    for(int lg = LOG - 1; lg >= 0; lg--) { 
        if(jump[u][lg] != jump[v][lg]) { 
            u = jump[u][lg]; 
            v = jump[v][lg]; 
        }
    }
    return jump[u][0]; 
}

ll query(int u, int v) { 
    if(u == v) return dp[u] + 1LL * (siz[1] - siz[u]) * siz[u]; 
    if(dep[v] < dep[u]) swap(u, v); 
    int LCA = lca(u, v); 
    if(LCA == u) { 
        ll ans = dp2[v] - up[u];
        int u2 = lift(v, dep[v] - dep[u] - 1); 
        ll extra = 1LL * (siz[u] - siz[u2]) * (siz[1] - siz[u]);
        return ans + extra; 
    }
    ll ans = dp2[u] + dp2[v] + dp[LCA], total = siz[LCA]; 
    
    int u2 = lift(u, dep[u] - dep[LCA] - 1); 
    ans -= 1LL * (total - siz[u2]) * siz[u2] + up[u2]; 
    total -= siz[u2]; 
    
    int v2 = lift(v, dep[v] - dep[LCA] - 1); 
    ans -= 1LL * (total - siz[v2]) * siz[v2] + up[v2]; 
    total -= siz[v2];    
    
    return ans + (siz[1] - siz[LCA]) * total; 
}

void solve() {
    int n, qq; cin >> n >> qq; 
    rep(i,0,n+1) { 
        adj[i].clear(); 
        dp[i] = up[i] = dep[i] = siz[i] = dp2[i] = 0; 
    }
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    dfs1(1); 
    rep(lg,1,LOG) rep(i,1,n+1) jump[i][lg] = jump[jump[i][lg - 1]][lg - 1];     
    rep(u,1,n+1) { 
        ll sum = 0; 
        for(int v : adj[u]) { 
            if(v == jump[u][0]) continue; 
            dp[u] += siz[v] * sum; 
            sum += siz[v]; 
        }
        dp[u] += siz[u]; 
    }
    dfs2(1); 
    while(qq--) { 
        int u, v; cin >> u >> v; 
        cout << query(u, v) << "\n"; 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
