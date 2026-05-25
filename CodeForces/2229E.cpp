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

const int mod = 998244353; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
struct FT {
    vi s;
	FT(int n) : s(n) {}
	void update(int pos, int dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] = add(s[pos], dif);
	}
	int query(int pos) { // sum of values in [0, pos)
		int res = 0;
		for (; pos > 0; pos &= pos - 1) res = add(res, s[pos - 1]);
		return res;
	}
    int rq(int l, int r) { 
        if(l > r) return 0; 
        return sub(query(r + 1), query(l)); 
    }
};

void solve() {
    int n; cin >> n; 
    vvi adj(n + 1); 
    vi deg(n + 1, 0); 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        deg[u]++; 
        deg[v]++; 
    }
    if(deg[n] == 1) { 
        cout << "1\n"; return; 
    }
    vi mx(n + 1); 
    auto dfs = [&](auto &&self, int u, int p) -> void { 
        for(int v : adj[u]) { 
            if(v == p) continue; 
            self(self, v, u);
            mx[u] = max({mx[u], v, mx[v]});  
        }
    };
    dfs(dfs, n, -1); 
    FT ft(n + 1); 
    int big_leaf = -1; 
    rep(i,1,n+1) if(deg[i] == 1) big_leaf = i; 
    ft.update(big_leaf, 1); 
    rep(cur,big_leaf+1,n) { 
        int l = mx[cur] + 1; 
        ft.update(cur, ft.rq(l, cur)); 
    }
    vi sub_tree(n + 1), val(n + 1); 
    queue<int> q; 
    vector<bool> vis(n + 1); vis[n] = true; 
    for(int u : adj[n]) { 
        vis[u] = true; 
        sub_tree[u] = u; 
        val[u] = max(u, mx[u]); 
        q.push(u); 
    }
    while(sz(q)) { 
        int u = q.front(); q.pop(); 
        for(int v : adj[u]) { 
            if(vis[v]) continue ; 
            vis[v] = true; 
            sub_tree[v] = sub_tree[u]; 
            q.push(v); 
        }
    }
    vi excluding(n + 1); 
    set<pii> ss; 
    for(int u : adj[n]) ss.emplace(val[u], u); 
    for(int u : adj[n]) { 
        ss.erase({val[u], u}); 
        excluding[u] = ss.rbegin() -> first; 
        ss.emplace(val[u], u); 
    }
    int ans = 0; 
    rep(i,1,n) { 
        if(excluding[sub_tree[i]] < i) ans = add(ans, ft.rq(i, i)) ; 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
