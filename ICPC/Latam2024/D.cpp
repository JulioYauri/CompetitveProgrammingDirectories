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

const int N = 1000 + 10; 
int n; 
string g[N]; 

bool L[N * N]; 
int ct = 1; 
int new_l() { 
    L[ct] = true; 
    return ct++; 
}
int new_r() { 
    L[ct] = false; 
    return ct++; 
}


vi adj[N]; 
vi comp; 
bool vis[N];  
bool done[N][N];
void dfs(int i, int other) { 
    for(int j : adj[i]) { 
        if(!vis[j] && g[j][other] == '1') { 
            vis[j] = true; 
            comp.push_back(j); 
            dfs(j, other); 
        } 
    }
}
void get_clique(int src) { 
    comp = { src } ; 
    vis[src] = true; 
    for(int i : adj[src]) { 
        if(g[src][i] == '1' && !done[src][i]) { 
            comp.push_back(i);
            vis[i] = true;  
            dfs(i, src); 
            break;
        } 
    }
    for(int x : comp) for(int y : comp) done[x][y] = true; 
    for(int x : comp) vis[x] = false; 
}

int Lv[N], Rv[N];
vi cliques_with[N]; 
vvi cliques; 
bool solved[N]; 

void solve(int clique_idx, bool right) { 
    if(solved[clique_idx]) return; 
    auto &cur = cliques[clique_idx]; 
    if(right) { 
        int right_node = -1; 
        for(int x : cur) { 
            if(Rv[x] != -1) { 
                right_node = Rv[x]; 
                break; 
            }
        }    
        if(right_node == -1) { 
            right_node = new_r(); 
        }
        for(int x : cur) { 
            if(Lv[x] == -1) Lv[x] = new_l(); 
            Rv[x] = right_node; 
        }
    }else{ 
        int left_node = -1; 
        for(int x : cur) { 
            if(Lv[x] != -1) { 
                left_node = Lv[x]; 
                break;
            }
        }
        if(left_node == -1) { 
            left_node = new_l(); 
        }
        for(int x : cur) { 
            if(Rv[x] == -1) Rv[x] = new_r(); 
            Lv[x] = left_node; 
        }
    }
    solved[clique_idx] = true; 
    for(int x : cur) { 
        if(sz(cliques_with[x]) == 2) { 
            int other = (cliques_with[x][0] ^ cliques_with[x][1] ^ clique_idx); 
            solve(other, right ^ 1); 
        }
    }
}

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
    
    cin >> n;
    rep(i,0,n) cin >> g[i]; 

    rep(i,0,n) rep(j,i+1,n) if(g[i][j] == '1') adj[i].push_back(j), adj[j].push_back(i); 

    int ans = 0; 
    rep(i,0,n) { 
        if(count(all(g[i]), '1')) { 
            rep(it,0,2) { 
                get_clique(i); 
                if(sz(comp) > 1) { 
                    int id = sz(cliques); 
                    cliques.push_back(comp);
                    for(int x : comp) cliques_with[x].push_back(id);  
                }
            }
        }else{ 
            ans += (count(all(g[i]), '1') == 0) ; 
        }
    }

    memset(Lv, -1, sizeof(Lv)); 
    memset(Rv, -1, sizeof(Rv)); 
    rep(i,0,sz(cliques)) { 
        solve(i, 1); 
    }
    
    Dinic solver(ct + 1); 
    rep(i,0,n) { 
        if(Lv[i] != -1) { 
            solver.addEdge(Lv[i], Rv[i], 1); 
        }
    } 
    
    rep(i,1,ct) {  
        if(L[i]) solver.addEdge(0, i, 1); 
        else solver.addEdge(i, ct, 1); 
    }
    ans += solver.calc(0, ct); 
    cout << ans << "\n"; 
}
