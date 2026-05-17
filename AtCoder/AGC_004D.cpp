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



signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, k; cin >> n >> k; 
    vi par(n + 1); rep(i,1,n+1) cin >> par[i]; 

    vvi adj(n + 1); 
    rep(i,2,n+1) { 
        adj[i].push_back(par[i]); 
        adj[par[i]].push_back(i); 
    }

    queue<int> q; 
    vi d(n + 1, -1); 
    q.push(1); 
    d[1] = 0; 
    int ans = (par[1] != 1); 

    auto dfs = [&](auto &&self, int u, int p) -> int { 
        int h = 0; 
        for(int v : adj[u]) { 
            if(v == p) continue; 
            h = max(h, self(self, v, u)) ; 
        }
        h++; 
        if(u == 1) return 0; 
        if(h == k) { 
            ans += (p != 1) ; 
            return 0; 
        }
        return h; 
    };
    dfs(dfs, 1, -1); 
    cout << ans << "\n"; 

}
