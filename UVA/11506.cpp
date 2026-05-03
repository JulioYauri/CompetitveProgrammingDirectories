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

struct Dinic { 
    struct Edge { 
        int to, rev; 
        ll c, oc; 
        ll flow() { return max(oc - c, 0LL); }
    };
    vi lvl, ptr, q; 
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) { }
    void addEdge(int a, int b, ll c, ll rcap = 0) { 
        adj[a].push_back({b, sz(adj[b]), c, c}); 
        adj[b].push_back({a, sz(adj[a]) -1, rcap, rcap}); 
    }
    ll dfs(int v, int t, ll f) { 
        if(v == t || !f) return f; 
        for(int &i = ptr[v]; i < sz(adj[v]); i++) { 
            Edge& e = adj[v][i]; 
            if(lvl[e.to] == lvl[v] + 1) { 
                if(ll p = dfs(e.to, t, min(f, e.c))) { 
                    e.c -= p, adj[e.to][e.rev].c += p; 
                    return p; 
                }
            }
        }
        return 0; 
    }
    ll calc(int s, int t) { 
        ll flow = 0; q[0] = s; 
        rep(L,0,31) do { 
            lvl = ptr = vi(sz(q)); 
            int qi = 0, qe = lvl[s] = 1; 
            while(qi < qe && !lvl[t]) { 
                int v = q[qi++]; 
                for(Edge e : adj[v]) { 
                    if(!lvl[e.to] && e.c >> (30 - L)) 
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1; 
                }
            }
            while(ll p = dfs(s, t, LLONG_MAX)) flow += p; 
        } while(lvl[t]); 
        return flow; 
    }
};

void solve(int m, int w) { 
    Dinic solver(2 * m);
    int src = 1, sink = 2 * (m - 1) ;  
    rep(i,0,m-2) { 
        int id, cost; cin >> id >> cost; 
        id--; 
        solver.addEdge(2 * id, 2 * id + 1, cost); 
    }       
    rep(i,0,w) { 
        int u, v, cost; cin >> u >> v >> cost; 
        u--, v--; 
        solver.addEdge(2 * u + 1, 2 * v, cost); 
        solver.addEdge(2 * v + 1, 2 * u, cost); 
    }
    cout << solver.calc(src, sink) << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    int m, w; 
    while(cin >> m >> w) { 
        if(m == 0 && w == 0) return 0; 
        solve(m, w); 
    }

}
