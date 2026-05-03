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

int n, l; 
const int MAXX = 3; 
const int MAXY = 4; 
const int PTS = 12; 

ll ans = 0; 
bool forbidden[MAXX + 2][MAXY + 2], vis[MAXX + 2][MAXY + 2], fb[PTS + 2], fbm[(1 << PTS) + 2]; 
int ID[MAXX + 2][MAXY + 2]; 
int X[PTS], Y[PTS]; 

const int MAXLEN = 60; 
ll dp[(1 << PTS) + 2][MAXLEN + 2][PTS]; 

bool ok(int x, int y) { 
    return x >= 1 && y >= 1 && x <= MAXX && y <= MAXY; 
}

bool valid(int sx, int sy, int tx, int ty, int mask) { 
    int dx = tx - sx; 
    int dy = ty - sy; 
    int g = abs(gcd(dx, dy)); 
    if(g == 1) return true; 
    dx /= g; 
    dy /= g; 
    rep(i,0,10) { 
        sx += dx;
        sy += dy; 
        if(!ok(sx, sy) || (sx == tx && sy == ty)) break; 
        if(forbidden[sx][sy]) return false; 
        if(((mask >> ID[sx][sy]) & 1) == 0) return false; 
    }
    return true; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    cin >> l >> n; 
    rep(i,0,n) { 
        int x, y; cin >> x >> y; 
        forbidden[x][y] = true; 
    }

    if(l >= MAXLEN) { 
        cout << "BAD MEMORY\n"; return 0; 
    }

    int cur_id = 0; 
    rep(x,1,4) rep(y,1,5) { 
        ID[x][y] = cur_id++; 
        X[ID[x][y]] = x; 
        Y[ID[x][y]] = y; 
    } 

    rep(x,1,4) rep(y,1,5) {
        if(forbidden[x][y]) { 
            fb[ID[x][y]] = true; 
            continue; 
        } 
        int id = ID[x][y];
        dp[1 << id][0][id] = 1;
    }

    rep(bit,0,PTS) if(fb[bit]) { 
        rep(mask,1,1<<PTS) if((mask >> bit) & 1) fbm[mask] = true; 
    }

    rep(mask,1,1<<PTS) if(!fbm[mask]) { 
        int cmask = mask; 
        while(cmask) { 
            int last = __builtin_ctz(cmask); 
            if(!fb[last]) { 
                rep(len,0,l) if(dp[mask][len][last]) { 
                    rep(nxt,0,PTS) if((!((mask >> nxt) & 1)) && !fb[nxt] && valid(X[last], Y[last], X[nxt], Y[nxt], mask)) { 
                        int add = abs(X[last] - X[nxt]) + abs(Y[last] - Y[nxt]) ; 
                        if(len + add <= l) dp[mask | (1 << nxt)][len + add][nxt] += dp[mask][len][last]; 
                    }
                }
            }
            cmask &= (cmask - 1); 
        }        
    }

    rep(mask,1,1<<PTS) rep(last,0,PTS) ans += dp[mask][l][last]; 

    if(ans == 0) cout << "BAD MEMORY\n"; 
    else cout << ans << "\n"; 

}
