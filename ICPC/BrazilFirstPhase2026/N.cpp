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

const int N = 1000 + 10 ; 
vi adj[N]; 
int has[N][N * 2]; 

void dfs(int u, int val, int p = -1) { 
    has[u][val] = 1; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        dfs(v, val, u); 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    vii edges; 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        edges.emplace_back(u, v); 
    }
    rep(i,0,sz(edges)) { 
        int u = i + 1; 
        dfs(edges[i].first, u, edges[i].second); 
        dfs(edges[i].second, u + n, edges[i].first); 
    }

    cout << 2 * n << "\n"; 
    rep(i,1,n+1) { 
        int t = 0; 
        rep(j,1,2*n+1) t += has[i][j]; 
        cout << t << " "; 
        rep(j,1,2*n+1) { 
            if(has[i][j]) { 
                cout << j << " "; 
            }
        }
        cout << "\n"; 
    }

}
