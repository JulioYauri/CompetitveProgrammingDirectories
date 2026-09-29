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
vi adj[N]; 
int up[N][LOG], par[N], dep[N], tin[N], tout[N], val[N], timer = 0; 

int lso(int x) { return (x & (-x)); }
struct FT { 
    int n; 
    vi v; 
    FT() { }
    void build(int n_) { 
        n = n_; 
        v.resize(n + 1); 
    }
    void upd(int pos, int x) { 
        for(int i = pos; i < sz(v); i += lso(i)) v[i] += x; 
    }
    int rsq(int pos) { 
        int total = 0; 
        for(int i = pos; i; i -= lso(i)) total += v[i]; 
        return total; 
    }
} ft;



void dfs(int u, int p = -1) { 
    tin[u] = ++timer; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        dep[v] = dep[u] + 1; 
        par[v] = up[v][0] = u; 
        dfs(v, u); 
    }
    tout[u] = timer; 
}

int lift(int a, int len) { 
    while(len) a = up[a][__builtin_ctz(len)], len &= (len - 1); 
    return a; 
}

int get_lca(int a, int b) { 
    if(dep[a] < dep[b]) swap(a, b); 
    a = lift(a, dep[a] - dep[b]) ; 
    if(a == b) return a; 
    for(int lg = LOG - 1; lg >= 0; lg--) { 
        if(up[a][lg] != up[b][lg]) { 
            a = up[a][lg]; 
            b = up[b][lg]; 
        }
    }
    return par[a]; 
}

int dist(int a, int b) { 
    return dep[a] + dep[b] - 2 * dep[get_lca(a, b)]; 
}

int que(int a) { 
    return ft.rsq(tin[a]); 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    int n; cin >> n; 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    dfs(1); 
    rep(lg,1,LOG) rep(i,1,n+1) up[i][lg] = up[up[i][lg - 1]][lg - 1]; 
    ft.build(n); 


    int qq; cin >> qq; 
    while(qq--) { 
        char t; cin >> t; 
        if(t == 'd') { 
            int u, v; cin >> u >> v; 
            if(dep[u] > dep[v]) swap(u, v); 
            // u deberia ser par[v], v deberia estar limpio 
            if(par[v] != u || val[v] == 1) continue; 
            ft.upd(tin[v], 1); 
            ft.upd(tout[v]+1, -1);
            val[v] = 1;  
        }else if(t == 'c') { 
            int u, v; cin >> u >> v; 
            if(dep[u] > dep[v]) swap(u, v); 
            if(par[v] != u || val[v] == 0) continue; 
            ft.upd(tin[v], -1); 
            ft.upd(tout[v]+1, 1); 
            val[v] = 0; 
        }else{ 
            int u, v; cin >> u >> v; 
            if(u == v) { 
                cout << "0\n"; 
                continue; 
            }
            int lca = get_lca(u, v);    
            int total = que(v) + que(u) - 2 * que(lca);
            if(total > 0) { 
                cout << "Impossible\n"; 
            }else{ 
                cout << dist(u, v) << "\n"; 
            }
        }
    }

}
