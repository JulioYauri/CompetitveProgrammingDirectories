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

const int N = 200000 + 4; 
vi adj[N];
int indeg[N], tin[N], tout[N], siz[N], col[N], cnt[N], ans[N], cur_max = -1;  
int timer = 0; 
vi tour ; 

void dfs1(int u) { 
    siz[u] = 1; 
    tin[u] = timer++; 
    tour.push_back(u); 
    for(int v : adj[u]) { 
        dfs1(v); 
        siz[u] += siz[v]; 
    }
    tout[u] = timer; 
}

void add(int color) { 
    cnt[color]++; 
    if(cnt[color] == cnt[cur_max]) cur_max = min(cur_max, color); 
    else if(cnt[color] > cnt[cur_max]) cur_max = color; 
}

void dfs2(int u, bool keep) { 
    int mx = -1, big_child = -1; 
    for(int v : adj[u]) { 
        if(siz[v] > mx) mx = siz[v], big_child = v; 
    }

    for(int v : adj[u]) { 
        if(v == big_child) continue; 
        dfs2(v, 0); 
    }

    if(big_child != -1) dfs2(big_child, 1); 
    add(col[u]); 
    for(int v : adj[u]) { 
        if(v != big_child) { 
            rep(i,tin[v], tout[v]) add(col[tour[i]]); 
        }
    }
    ans[u] = cur_max; 
    if(keep == 0) { 
        rep(i,tin[u], tout[u]) cnt[col[tour[i]]] -- ; 
        cur_max = -1; 
    }

}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    vi colors(n); rep(i,0,n) cin >> colors[i]; 
    vi coord = colors; 
    sort(all(coord)) ; 
    coord.erase(unique(all(coord)), coord.end()); 
    rep(i,0,n) col[i] = lower_bound(all(coord), colors[i]) - coord.begin(); 

    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        u--, v--; 
        indeg[v]++; 
        adj[u].push_back(v); 
    }

    int root = -1; 
    rep(i,0,n) if(indeg[i] == 0) root = i; 

    dfs1(root); 
    dfs2(root, 1); 
    rep(i,0,n) cout << coord[ans[i]] << " " ; cout << "\n"; 

}   
