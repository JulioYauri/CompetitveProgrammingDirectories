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

const int N = 10 + 2; 
int f[N][N][N]; 
int seq[200 + 10]; 

vi adj[N * N][N]; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n, m; cin >> n >> m; 
    rep(i,0,m) rep(j,0,m) rep(k,0,m) cin >> f[i][j][k]; 
    rep(i,0,n) cin >> seq[i]; 

    rep(i,0,m) rep(j,0,m) { 
        int u = i * m + j; 
        rep(k,0,m) { 
            int v = j * m + k; 
            adj[u][f[i][j][k]].push_back(v); 
        }
    }

    rep(src,0,m*m) { 
        vector<bool> vis(m * m, false); 
        vi cur = { src } ; 
        rep(i,0,n) { 
            vi nxt; 
            for(int x : cur) { 
                for(int v : adj[x][seq[i]]) { 
                    if(!vis[v]) { 
                        vis[v] = true; 
                        nxt.push_back(v); 
                    }
                }
            }
            for(int x : nxt) vis[x] = false; 
            swap(cur, nxt); 
        }
        for(int x : cur) { 
            if(x == src) { 
                cout << "YES\n"; 
                return 0; 
            }
        }
    }
    cout << "NO\n"; 
}
