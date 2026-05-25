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

bool on(int s, int bit) { return (s >> bit) & 1; }
void solveFirst() {
    int n, s; cin >> n >> s; 
    s--;
    rep(i,1,n) { 
        int u, v; cin >> u >> v;
        if(u > v) swap(u, v);  
        if(on(s, u - 1) == on(s, v - 1)) cout << u << " " << v << endl ; 
        else cout << v << " " << u << endl; 
    }    
}

void solveSecond() { 
    int n, s = 0; cin >> n; 
    vvi adj(n);
    set<pii> special ; 
    vi val(n);  
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        u--, v--; 
        adj[u].push_back(v);
        adj[v].push_back(u); 
        if(u > v) special.emplace(v, u); 
    }   
    auto dfs = [&](auto &&self, int u, int p) -> void { 
        for(int v : adj[u]) { 
            if(v == p) continue; 
            if(special.count({u, v}) || special.count({v, u})) { 
                val[v] = val[u] ^ 1;
            }else{ 
                val[v] = val[u]; 
            }
            self(self, v, u); 
        }
    };
    dfs(dfs,n-1,-1); 
    rep(i,0,n) if(val[i]) s |= (1 << i); 
    cout << s + 1 << endl; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt, q; cin >> tt >> q;
    if(q == 1) while(tt--) solveFirst(); 
    else while(tt--) solveSecond(); 
}
