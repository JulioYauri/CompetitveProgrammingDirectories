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

const int N = 20;
const int B = (1 << 18) + 10;  
int n;
double memo[B][N], p[N][N]; 
bool vis[B][N]; 

double dp(int mask, int won) { 
    if(vis[mask][won]) return memo[mask][won]; 
    if(mask == (1 << n) - 1) return won == 0; 
    double &h = memo[mask][won]; 
    rep(nxt,0,n) if(((mask >> nxt) & 1) == 0) { 
        double prob = dp(mask | (1 << nxt), won) * p[won][nxt]
                    + dp(mask | (1 << nxt), nxt) * p[nxt][won]; 
        h = max(h, prob);     
    }
    vis[mask][won] = true; 
    return h; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cin >> n; 
    rep(i,0,n) rep(j,0,n) cin >> p[i][j]; 
    cout << fixed << setprecision(12); 

    if(n == 1) { 
        cout << 1.0 << "\n"; return 0; 
    }

    double ans = 0; 
    rep(i,0,n) rep(j,i+1,n) { 
        int mask = (1 << i) | (1 << j); 
        ans = max(ans, dp(mask, i) * p[i][j] + dp(mask, j) * p[j][i]); 
    }
    cout << ans << "\n"; 
}
