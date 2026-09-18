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
int tin[N], tout[N], dep[N];
int up[N][LOG]; 
int timer = 0;  
bool anc(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }

void dfs1(int u, int p = -1) { 
    tin[u] = ++timer; 
    for(int v : adj[u]) if(v != p) { 
        dep[v] = dep[u] + 1; 
        up[v][0] = u; 
        dfs1(v, u); 
    }
    tout[u] = timer; 
}

int lift(int u, int len) { 
    while(len) u = up[u][__builtin_ctz(len)], len &= (len - 1); 
    return u ; 
}

int LCA(int a, int b) { 
    if(dep[a] < dep[b]) swap(a, b); 
    a = lift(a, dep[a] - dep[b]); 
    if(a == b) return a; 
    for(int lg = LOG - 1; lg >= 0; lg--) { 
        if(up[a][lg] != up[b][lg]) { 
            a = up[a][lg]; 
            b = up[b][lg]; 
        }
    }
    return up[a][0]; 
}
int dist(int a, int b) { 
    return dep[a] + dep[b] - 2 * dep[LCA(a, b)]; 
}

int special[N]; 
vii vt[N]; 
int scnt[N];
int total = 0;  

void dfs2(int u, int p = -1) { 
    scnt[u] = special[u]; 
    for(auto [v, w] : vt[u]) if(v != p) { 
        dfs2(v, u) ; 
        scnt[u] += scnt[v]; 
    }
}

int find_c(int u, int p = -1) { 
    for(auto [v, w] : vt[u]) if(v != p) { 
        if(scnt[v] > total / 2) return find_c(v, u); 
    }    
    return u; 
}

ll query(vi &v, int K) {
    total = sz(v); 
    for(int u : v) special[u] = 1; 
    sort(all(v), [](int i, int j) { return tin[i] < tin[j]; });
    int siz = sz(v); 
    rep(i,1,siz) v.push_back(LCA(v[i], v[i - 1])) ;

    sort(all(v), [](int i, int j) { return tin[i] < tin[j]; });
    v.erase(unique(v.begin(), v.end()), v.end()); 
    
    
    int root = v[0]; 
    vi st(1, root); 
    rep(i,1,sz(v)) { 
        while(st.size() && !anc(st.back(), v[i])) st.pop_back(); 
        int d = dist(st.back(), v[i]); 
        vt[st.back()].emplace_back(v[i], d);
        vt[v[i]].emplace_back(st.back(), d);  
        st.push_back(v[i]); 
    }

    for(int i : v) scnt[i] = 0 ; 
    dfs2(root); 
    int cen = find_c(root); 

    ll ans = 0 ; 
    for(int i : v) { 
        if(special[i]) ans += dist(i, cen); 
    }
    K--;
    // subs, cap, u, par
    dfs2(cen);  
    using data = tuple<int,int,int,int> ; 
    priority_queue<data> pq; 
    for(auto [v, w] : vt[cen]) pq.emplace(scnt[v], w, v, cen) ; 
    
    while(sz(pq) && K > 0) { 
        auto [subs, cap, u, par] = pq.top(); pq.pop(); 
        int take = min(K, cap); 
        ans -= 1LL * take * subs ; 
        K -= take; 
        if(K > 0) { 
            for(auto [v, w] : vt[u]) if(v != par) { 
                pq.emplace(scnt[v], w, v, u) ; 
            }
        }
    }

    // clear 
    for(int i : v) vt[i].clear(), special[i] = 0; 
    return ans; 
}

void solve() {
    int n; cin >> n; 
    timer = 0; 
    rep(i,0,n+1) { 
        adj[i].clear(); 
        dep[i] = tin[i] = tout[i] = 0; 
    } 


    vi c(n), ks(n); 
    vvi per_color(n); 
    rep(i,0,n) { 
        cin >> c[i]; 
        c[i]--; 
        per_color[c[i]].push_back(i); 
    } 
    rep(i,0,n) cin >> ks[i]; 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        u--; 
        v--; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    dfs1(0); 
    rep(lg,1,LOG) rep(i,0,n) up[i][lg] = up[up[i][lg - 1]][lg - 1]; 

    rep(i,0,n) { 
        if(per_color[i].empty()) { 
            cout << "-1 "; continue; 
        }
        cout << query(per_color[i], ks[i]) << " "; 
    }
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
