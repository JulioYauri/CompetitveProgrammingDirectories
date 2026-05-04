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

const int N = 30000 + 10 ;
const int LOG = 17;  
vi adj[N];
int tin[N], tout[N], timer, up[N][LOG], dep[N]; 

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
};


void dfs(int u, int p = -1) { 
    tin[u] = timer++; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        up[v][0] = u; 
        dep[v] = dep[u] + 1; 
        dfs(v, u); 
    }
    tout[u] = timer; 
}

int lift(int a, int len) { 
    while(len) a = up[a][__builtin_ctz(len)], len &= (len - 1); 
    return a; 
}

int lca(int a, int b) { 
    if(dep[a] < dep[b]) swap(a, b); 
    // dep[a] >= dep[b] -> levanto a 
    a = lift(a, dep[a] - dep[b]); 
    if(a == b) return a; 
    for(int lg = LOG - 1; lg >= 0; lg--) { 
        if(up[a][lg] != up[b][lg]) { 
            a = up[a][lg]; 
            b = up[b][lg]; 
        }
    }
    return up[a][0] ; 
}

void solve() { 
    int n; cin >> n; 
    rep(i,0,n+1) { 
        adj[i].clear(); 
        dep[i] = 0; 
    }
    vi a(n); rep(i,0,n) cin >> a[i]; 
    
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }
    
    FT ft(n + 4); 
    timer = 0; 
    dfs(0); 
    rep(i,0,n) { 
        ft.update(tin[i], a[i]); 
        ft.update(tout[i], -a[i]); 
    }

    rep(lg,1,LOG) rep(i,0,n) up[i][lg] = up[up[i][lg - 1]][lg - 1] ; 

    int qq; cin >> qq;
    
    auto path = [&](int x) { 
        return ft.query(tin[x] + 1); 
    };

    auto upd = [&](int x, int nv) { 
        int diff = nv - a[x]; 
        ft.update(tin[x], diff); 
        ft.update(tout[x], -diff); 
        a[x] = nv; 
    };

    while(qq--) { 
        int tp ; cin >> tp; 
        if(tp == 0) { 
            int u, v; cin >> u >> v; 
            int w = lca(u, v); 
            cout << path(u) + path(v) - path(w) * 2 + a[w] << "\n"; 
        }else{ 
            int i, nv; cin >> i >> nv; 
            upd(i, nv); 
        }
    }

}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int tt; cin >> tt; 
    rep(c,1,tt+1) { 
        cout << "Case " << c << ":\n"; 
        solve() ; 
    }
}
