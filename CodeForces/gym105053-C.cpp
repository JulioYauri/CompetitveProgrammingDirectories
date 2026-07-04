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
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n, m; cin >> n >> m; 
    vector<string> grid(n); 
    rep(i,0,n) cin >> grid[i]; 

    int src = n * m, sink = n * m + 1; 
    Dinic solver(sink + 1) ; 
    // left odd   right even 
    vii d = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    auto ok = [&](int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }; 
    vi odd_ids, even_ids; 
    rep(i,0,n) { 
        rep(j,0,m) if(grid[i][j] != '#') { 
            if((i + j) % 2 == 1) { 
                int id = i * m + j ;
                for(auto [di, dj] : d) { 
                    int ni = i + di, nj = j + dj; 
                    if(!ok(ni, nj) || grid[ni][nj] == '#') continue; 
                    int id2 = ni * m + nj ; 
                    solver.addEdge(id, id2, 1); 
                }
                odd_ids.push_back(id); 
            }else{ 
                even_ids.push_back(i * m + j); 
            }
        }
    }  
    for(int i : odd_ids) solver.addEdge(src, i, 1); 
    for(int i : even_ids) solver.addEdge(i, sink, 1); 
    int mm = solver.calc(src, sink); 
    int todo = 0 ; 
    { 
        vvi adj(n * m); 
        vector<bool> freeL(n * m, true); 
        for(int i : odd_ids) { 
            for(auto e : solver.adj[i]) { 
                if(e.to == sink || e.to == src) continue; 
                if(e.flow() == 1) adj[e.to].push_back(i), freeL[i] = false; 
                else adj[i].push_back(e.to);
            }
        }
        queue<int> q; 
        vector<bool> vis(n * m, false); 
        for(int i : odd_ids) { 
            if(freeL[i]) { 
                q.push(i); 
                vis[i] = true; 
            }
        }
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            for(int v : adj[u]) { 
                if(vis[v]) continue; 
                vis[v] = true; 
                q.push(v); 
            }
        }
        for(int i : odd_ids) todo += (!vis[i]); 
    }
    { 
        
        vvi adj(n * m); 
        vector<bool> freeR(n * m, true); 
        for(int i : odd_ids) { 
            for(auto e : solver.adj[i]) { 
                if(e.to == sink || e.to == src) continue;
                if(e.flow() == 1) adj[i].push_back(e.to), freeR[e.to] = false; 
                else adj[e.to].push_back(i); 
            }
        }
        queue<int> q; 
        vector<bool> vis(n * m, false); 
        for(int i : even_ids) { 
            if(freeR[i]) { 
                q.push(i); 
                vis[i] = true; 
            }
        }
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            for(int v : adj[u]) { 
                if(vis[v]) continue; 
                vis[v] = true; 
                q.push(v); 
            }
        }
        for(int i : even_ids) todo += (!vis[i]); 
    }
    cout << sz(even_ids) + sz(odd_ids) - todo << "\n"; 
}
