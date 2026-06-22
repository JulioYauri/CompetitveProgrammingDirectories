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

// RMQ rmq(v) 
// query = [l, r) , indexa en 0  
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) const {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA { 
    int T = 0; 
    vi time, path, ret, dep; 
    RMQ<int> rmq; 

    LCA(vvi &adj) : time(sz(adj)), rmq((dfs(adj,0,-1), ret)), dep(sz(adj), 0) {} 
    void dfs(vvi &adj, int u, int par) { 
        time[u] = T++; 
        for(int v : adj[u]) if(v != par) { 
            dep[v] = dep[u] + 1 ; 
            path.push_back(u); 
            ret.push_back(time[u]); 
            dfs(adj, v, u); 
        } 
    }
    int lca(int a, int b) const { 
        if(a == b) return a; 
        tie(a, b) = minmax(time[a], time[b]); 
        return path[rmq.query(a, b)]; 
    }
    int dist(int a, int b) const { 
        return dep[a] + dep[b] - 2 * dep[lca(a, b)]; 
    }
};  

struct SegTree { 
    LCA lca; 
    struct node {
        int u, v, d;  
        node() : u(-1), v(-1), d(-1) { }
        node(int u) : u(u), v(u), d(0) { }
    };
    node merge(const node& lhs, const node& rhs) const { 
        node res; 
        if(lhs.u == -1) return rhs; 
        if(rhs.u == -1) return lhs; 
        if(lhs.d > rhs.d) res = lhs; 
        else res = rhs ; 
        for(int a : {lhs.u, lhs.v}) { 
            for(int b : {rhs.u, rhs.v}) { 
                int d = lca.dist(a, b);
                if(d > res.d) { 
                    res.d = d; 
                    res.u = a; 
                    res.v = b; 
                }
            }
        }
        return res; 
    }
    vector<node> t; 
    SegTree(int n, const LCA& lca) : lca(lca) {
        t.resize(4 * n + 5); 
        rep(i,0,n) update(1,0,n-1,i); 
    }
    void update(int v, int l, int r, int pos) { 
        if(l == r) { 
            if(t[v].u == -1) t[v] = node(l); 
            else t[v].u = t[v].v = -1; 
            return ;
        }
        int m = l + r >> 1; 
        if(pos <= m) update(v * 2, l, m, pos); 
        else update(v * 2 + 1, m + 1, r, pos); 
        t[v] = merge(t[v * 2], t[v * 2 + 1]); 
    }
    int answer() { 
        auto root = t[1];
        return lca.dist(root.u, root.v); 
    }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n;
    vvi adj(n); 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        u--, v--; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }
    LCA lca(adj); 
    SegTree solver(n, lca); 
    int qq; cin >> qq;
    while(qq--) { 
        int u; cin >> u; u--; 
        solver.update(1,0,n-1,u);
        cout << solver.answer() << "\n"; 
    }
}
