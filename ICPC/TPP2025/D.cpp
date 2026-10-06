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

const int N = 200'000 + 10; 
const int LOG = 18; 
int to[N], par[N], indeg[N], dep[N]; 
bool cycle[N];
int cyc_len[N];  
int up[N][LOG]; 
vi adj[N]; 
int n; 


void dfs(int u) { 
    for(int v : adj[u]) {
        dep[v] = dep[u] + 1; 
        up[v][0] = u; 
        dfs(v); 
    }
}

int lift(int a, int len) { 
    while(len) a = up[a][__builtin_ctz(len)], len &= (len - 1); 
    return a; 
}

int get_lca(int a, int b) { 
    if(dep[a] > dep[b]) swap(a, b); 
    b = lift(b, dep[b] - dep[a]); 
    if(a == b) return a; 
    for(int i = LOG - 1; i >= 0; i--) { 
        if(up[a][i] != up[b][i]) { 
            a = up[a][i]; 
            b = up[b][i]; 
        }
    }
    return par[a]; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cin >> n; 
    rep(i,1,n+1) { 
        cin >> to[i]; 
        indeg[to[i]]++; 
    } 

    rep(i,0,n+1) cycle[i] = true; 
    queue<int> q; 
    rep(i,1,n+1) { 
        if(indeg[i] == 0) { 
            q.push(i); 
            cycle[i] = false; 
        }
    }

    while(sz(q)) { 
        int u = q.front(); q.pop(); 
        indeg[to[u]]--; 
        par[u] = to[u]; 
        if(indeg[to[u]] == 0) { 
            q.push(to[u]); 
            cycle[to[u]] = false; 
        }
    }

    rep(i,1,n+1) { 
        if(par[i] == 0) { 
            int u = to[i]; 
            vi path(1, u); 
            while(u != i) { 
                par[u] = to[u]; 
                u = to[u]; 
                path.push_back(u); 
            }
            for(int x : path) { 
                cyc_len[x] = sz(path); 
            }
        }
    }
    rep(i,1,n+1) adj[par[i]].push_back(i); 
    dfs(0); 
    rep(lg,1,LOG) rep(i,1,n+1) up[i][lg] = up[up[i][lg - 1]][lg - 1]; 
    int qq; cin >> qq; 
    while(qq--) { 
        int u, v; cin >> u >> v; 
        int lca = get_lca(u, v); 
        if(lca == 0) { 
            cout << "-1\n"; 
            continue; 
        }
        int ans = dep[u] + dep[v] - 2 * dep[lca]; 
        int cyc_ans = 0; 
        if(!cycle[u]) { 
            cyc_ans++; 
            for(int i = LOG - 1; i >= 0; i--) { 
                if(cycle[up[u][i]]) continue; 
                u = up[u][i]; 
                cyc_ans += (1 << i); 
            }
            u = par[u]; 
        }
        if(!cycle[v]) { 
            cyc_ans++; 
            for(int i = LOG - 1; i >= 0; i--) { 
                if(cycle[up[v][i]]) continue; 
                v = up[v][i]; 
                cyc_ans += (1 << i); 
            }
            v = par[v]; 
        }
        if(dep[u] < dep[v]) swap(u, v); 
        cyc_ans += min(dep[u] - dep[v], cyc_len[u] - (dep[u] - dep[v])); 
        cout << min(ans, cyc_ans) << "\n"; 
    }

}
