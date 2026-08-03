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

struct DSU{
	int n;
    vi par, sz; 
    DSU (int n_) : n(n_) {
        par.resize(n); sz.assign(n, 1);
        for(int i = 0; i < n; i++) par[i] = i; 
    }

    int get(int a) { return par[a] == a ? a : par[a] = get(par[a]); }
    void unite(int a, int b) {
        a = get(a), b = get(b);
        if(a == b) return; 
        sz[a] += sz[b]; 
        par[b] = a; 
    }
    
};

void solve() {
    int n, m, k; cin >> n >> m >> k; 
    vector<tuple<int,int,int,int>> eds; 
    vector adj(n, vector<tuple<int,int,int>>()); 
    rep(i,1,m+1) { 
        int u, v, w; cin >> u >> v >> w; 
        u--, v--; 
        eds.emplace_back(w, u, v, i); 
        adj[u].emplace_back(v, w, i); 
        adj[v].emplace_back(u, w, i); 
    }

    sort(all(eds)); 
    vi lims;
    rep(_,0,2) { 
        DSU dsu(n); 
        int total = 0; 
        for(auto [w, u, v, i] : eds) { 
            if(dsu.get(u) != dsu.get(v)) { 
                dsu.unite(u, v); 
                total += w; 
            }
        }
        lims.push_back(total); 
        reverse(all(eds)); 
    }
    // cerr << "lims: " << lims[0] << " " << lims[1] << "\n"; 
    if(lims[0] > k || lims[1] < k) { 
        cout << "-1\n"; return; 
    }

    vi comp(n, -1);
    int cur_comp = 0;  
    rep(i,0,n) { 
        if(comp[i] != -1) continue; 
        queue<int> q; 
        q.push(i); 
        comp[i] = cur_comp; 
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            for(auto [v, w, idx] : adj[u]) { 
                if(comp[v] != -1 || w == 1) continue; 
                comp[v] = comp[u]; 
                q.push(v); 
            }
        }
        cur_comp++; 
    }   

    vector<bool> used(m + 1, false); 
    int cnt = 0;
    DSU comp_dsu(cur_comp);  
    DSU dsu(n); 
    for(auto [w, u, v, i] : eds) {
        int c_u = comp[u], c_v = comp[v];  
        if(comp_dsu.get(c_u) != comp_dsu.get(c_v) && dsu.get(u) != dsu.get(v)) { 
            cnt++; 
            used[i] = true; 
            comp_dsu.unite(c_u, c_v); 
            dsu.unite(u, v); 
        }
    }

    for(auto want : {1, 0}) { 
        for(auto [w, u, v, i] : eds) { 
            if(want == 1 && cnt == k) break; 
            if(w == want && dsu.get(u) != dsu.get(v)) { 
                cnt += w; 
                dsu.unite(u, v); 
                used[i] = true; 
            }
        }
    }
    assert(cnt == k); 
    rep(i,1,m+1) { 
        if(used[i]) cout << i << " " ; 
    }
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
