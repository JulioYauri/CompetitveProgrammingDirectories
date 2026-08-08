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

const int N = 2000 + 10; 
int memo[N][N]; 
vi adj[N]; 
int n, k; 

int dp(int, int); 
int get_all(int u, int p) { 
    int xr = 0 ; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        xr ^= dp(v, u); 
    }
    return xr; 
}

int dp(int u, int p) { 
    int &h = memo[u][p]; 
    if(h != -1) return h; 
    set<int> vals; 
    int cur_xor = get_all(u, p); 
    vals.insert(cur_xor); 
    auto dfs = [&](auto &&self, int cur, int par, int dep) -> void { 
        if(dep < k) { 
            for(auto v : adj[cur]) { 
                if(v == par) continue; 
                cur_xor ^= dp(v, cur); 
                cur_xor ^= get_all(v, cur);
                vals.insert(cur_xor);  
                self(self, v, cur, dep + 1); 
                cur_xor ^= dp(v, cur); 
                cur_xor ^= get_all(v, cur); 
            }
        }
    };
    dfs(dfs,u,p,1) ; 
    int mex = 0; 
    for(auto x : vals) { 
        if(mex == x) mex++; 
        else break; 
    }
    return h = mex; 
}

void solve() {
    cin >> n >> k;
    rep(i,0,n+1) { 
        rep(j,0,n+1) memo[i][j] = -1; 
        adj[i].clear(); 
    } 
    
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    string ans(n, '1'); 
    rep(u,1,n+1) { 
        int xr = 0 ; 
        for(int v : adj[u]) xr ^= dp(v, u); 
        ans[u - 1] = (xr == 0 ? '0' : '1'); 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
