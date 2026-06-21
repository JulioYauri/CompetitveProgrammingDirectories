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

struct STree {
    int n;
    vl t, vec, sum; 
    vector<bool> lazy;
    STree() { }
    void init(vl &vec_) { 
        n = sz(vec_);
        vec = vec_; 
        t.assign(4 * n + 5, 0); 
        lazy.assign(4 * n + 5, 0); 
        sum.assign(4 * n + 5, 0); 
        build(1, 0, n - 1) ; 
    }
    void build(int v, int tl, int tr) { 
        if(tl == tr) { 
            sum[v] = vec[tl]; 
            return; 
        }
        int tm = tl + tr >> 1; 
        build(v * 2, tl, tm); 
        build(v * 2 + 1, tm + 1, tr); 
        sum[v] = sum[v * 2] + sum[v * 2 + 1]; 
    }
    void push(int v) { 
        if(!lazy[v]) return; 
        t[v * 2] = sum[v * 2] - t[v * 2]; 
        t[v * 2 + 1] = sum[v * 2 + 1] - t[v * 2 + 1]; 
        lazy[v * 2] = !lazy[v * 2] ; 
        lazy[v * 2 + 1] = !lazy[v * 2 + 1];  
        lazy[v] = false; 
    }
    void upd(int v, int tl, int tr, int l, int r) { 
        if(l > r) return ;
        if(tl == l && tr == r) { 
            t[v] = sum[v] - t[v] ; 
            lazy[v] = !lazy[v]; 
            return; 
        }
        push(v); 
        int tm = tl + tr >> 1; 
        upd(v * 2, tl, tm, l, min(r, tm)); 
        upd(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r); 
        t[v] = t[v * 2] + t[v * 2 + 1]; 
    }
    ll query(int v, int tl, int tr, int l, int r) { 
        if(l > r) return 0; 
        if(tl == l && tr == r) return t[v]; 
        push(v); 
        int tm = tl + tr >> 1; 
        return query(v * 2, tl, tm, l, min(r, tm)) 
            + query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r) ; 
    }
    void upd(int l, int r) { upd(1, 0, n - 1, l, r); }
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

const int LOG = 18; 
struct HLD {
    vector<vii> adj; 
    vvi up; 
    vi siz, dep, chain, in, val, tour; 
    int timer ; 
    STree tree; 
    int n; 
    HLD(vector<vii>& adj_) : adj(adj_) { 
        n = sz(adj); 
        up.assign(n, vi(LOG)); 
        siz.resize(n);
        dep.resize(n); 
        chain.resize(n); iota(all(chain),0); 
        in.resize(n); 
        val.resize(n); 
        tour.resize(n); 
        timer = 0;  
        dfs(0); 
        rep(lg,1,LOG) rep(i,0,n) up[i][lg] = up[up[i][lg - 1]][lg - 1]; 
        dfsHLD(0); 
    }
    void init(vl &vec) { tree.init(vec);  }
    void dfs(int u, int p = -1) { 
        siz[u] = 1; 
        for(auto [v, w] : adj[u]) { 
            if(v == p) continue; 
            val[v] = w; 
            up[v][0] = u; 
            dep[v] = dep[u] + 1; 
            dfs(v, u); 
            siz[u] += siz[v]; 
        }
    }

    void dfsHLD(int u, int p = -1) { 
        in[u] = timer++; 
        tour[timer - 1] = u; 
        int heavy = -1, mx = 0; 
        for(auto [v, w] : adj[u]) { 
            if(v == p) continue; 
            if(siz[v] > mx) { 
                mx = siz[v] ; 
                heavy = v ; 
            }
        }
        if(heavy != -1) { 
            chain[heavy] = chain[u]; 
            dfsHLD(heavy, u); 
        }
        for(auto [v, w] : adj[u]) { 
            if(v == p || v == heavy) continue; 
            dfsHLD(v, u); 
        }
    }

    int jump(int u, int len) { 
        while(len) u = up[u][__builtin_ctz(len)], len &= (len - 1); 
        return u; 
    }

    int lca(int u, int v) { 
        if(dep[u] < dep[v]) swap(u, v); 
        u = jump(u, dep[u] - dep[v]); 
        if(u == v) return u; 
        for(int i = LOG - 1; i >= 0; i--) { 
            if(up[u][i] != up[v][i]) { 
                u = up[u][i]; 
                v = up[v][i]; 
            }
        }
        return up[u][0]; 
    }

    ll path_query(int u, int anc) { // [u, anc) 
        ll res = 0; 
        while(dep[u] > dep[anc]) { 
            int top = chain[u]; 
            if(dep[top] <= dep[anc]) top = jump(u, dep[u] - dep[anc] - 1); 
            res += tree.query(in[top], in[u]);
            u = up[top][0]; 
        }
        return res; 
    }

    void path_update(int u, int anc) { 
        while(dep[u] > dep[anc]){ 
            int top = chain[u]; 
            if(dep[top] <= dep[anc]) top = jump(u, dep[u] - dep[anc] - 1); 
            tree.upd(in[top], in[u]); 
            u = up[top][0]; 
        }
    }

    void update(int u, int v) { 
        int anc = lca(u, v); 
        path_update(u, anc); 
        path_update(v, anc); 
    }
};


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, qq; cin >> n >> qq; 
    vector<vii> adj(n); 
    rep(i,1,n) { 
        int u, v, w; cin >> u >> v >> w; 
        u--, v--; 
        adj[u].emplace_back(v, w); 
        adj[v].emplace_back(u, w); 
    }

    HLD hld(adj); 
    vl vals(n); 
    rep(i,0,n) vals[i] = hld.val[i]; { 
        vl vc = vals; 
        rep(i,0,n) vals[i] = vc[hld.tour[i]]; 
    }
    hld.init(vals); 

    while(qq--) { 
        int u, v; cin >> u >> v; 
        u--, v--;
        hld.update(u, v); 
        cout << hld.tree.query(0, n - 1) << "\n"; 
    }

}
