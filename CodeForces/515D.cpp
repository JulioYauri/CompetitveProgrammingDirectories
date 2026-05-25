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

const int N = 2000 + 3; 
int deg[N][N]; 
bool vis[N][N]; 
int val[N][N]; 
pii wh[N][N]; 
vii d = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}} ; 

int n, m, cur = 1; 
bool ok(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }
int id(int i, int j) { return i * m + j ; }

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cin >> n >> m; 
    vector<string> grid(n); rep(i,0,n) cin >> grid[i]; 
    rep(i,0,n) rep(j,0,m) if(grid[i][j] == '.') { 
        for(auto [di, dj] : d) { 
            int ni = di + i, nj = dj + j ; 
            if(ok(ni,nj) && grid[ni][nj] == '.') deg[i][j]++; 
        }
    }
    
    queue<pii> q; 
    rep(i,0,n) rep(j,0,m) if(grid[i][j] == '.') { 
        if(deg[i][j] == 1 && !vis[i][j]) { 
            int to_i = -1, to_j = -1;
            for(auto [di, dj] : d) { 
                int ni = i + di, nj = j + dj; 
                if(ok(ni, nj) && grid[ni][nj] == '.' && !vis[ni][nj]) { 
                    to_i = ni, to_j = nj; 
                    break; 
                }
            } 
            if(to_i == -1) { 
                cout << "Not unique\n"; return 0; 
            } 
            q.emplace(i, j); 
            vis[i][j] = vis[to_i][to_j] = true; 
            wh[i][j] = {to_i, to_j}; 
        }
    }
    rep(i,0,n) rep(j,0,m) if(grid[i][j] == '*') vis[i][j] = true; 
    
    while(sz(q)) { 
        auto [i, j] = q.front(); q.pop(); 
        auto [who_i, who_j] = wh[i][j]; 
        // cerr << "visito a u=" << i << " " << j << "  who=" << who_i << " " << who_j  << "\n"; 
        val[i][j] = val[who_i][who_j] = cur++; 
        for(auto [di, dj] : d) { 
            int ni = di + who_i, nj = dj + who_j; // u1 
            if(ok(ni, nj) && !vis[ni][nj]) { 
                deg[ni][nj]--; 
                if(deg[ni][nj] == 1) { 
                    int his_i = -1, his_j = -1; // u2 
                    for(auto [di2, dj2] : d) { 
                        int ni2 = ni + di2, nj2 = nj + dj2 ; 
                        if(ok(ni2, nj2) && !vis[ni2][nj2]) { 
                            his_i = ni2, his_j = nj2; 
                            break; 
                        }
                    }
                    if(his_i == -1) { 
                        cout << "Not unique\n"; return 0; 
                    }
                    vis[ni][nj] = vis[his_i][his_j] = true; 
                    wh[ni][nj] = {his_i, his_j}; 
                    q.emplace(ni, nj); 
                }
            }
        }
    }
    // rep(i,0,n) rep(j,0,m) cerr << val[i][j] << " \n"[j == m - 1]; 
    rep(i,0,n) rep(j,0,m) { 
        if(grid[i][j] == '.' && val[i][j] == 0) { 
            cout << "Not unique\n"; 
            return 0; 
        }
    }

    rep(i,0,n) rep(j,0,m) { 
        if(grid[i][j] == '.') { 
            if(ok(i + 1, j) && val[i + 1][j] == val[i][j]) { 
                grid[i][j] = '^'; 
                grid[i + 1][j] = 'v'; 
            }else{ 
                grid[i][j] = '<'; 
                grid[i][j + 1] = '>'; 
            }
        }
    }
    for(auto i : grid) cout << i << "\n"; 
}
