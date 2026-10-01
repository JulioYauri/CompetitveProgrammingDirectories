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

const int N = 3000; 
int n, k; 
vi adj[N]; 
vector<double> dp[N]; 
int s[N], e[N], siz[N]; 
double val[N]; 
const double inf = 1e10; 
void dfs_siz(int u) { 
    siz[u] = 1; 
    for(int v : adj[u]) { 
        dfs_siz(v); 
        siz[u] += siz[v]; 
    }
}

double cur_dp[N]; 
void dfs(int u) { 
    dp[u].assign(siz[u] + 1, -inf);
    int cur_siz = 0; 
    dp[u][0] = 0; 
    for(int v : adj[u]) { 
        dfs(v); 
        int cur_dp_siz = cur_siz + siz[v]; 
        rep(i,0,cur_dp_siz + 1) cur_dp[i] = -inf; 
        rep(i,0,cur_siz+1) { 
            rep(j,0,siz[v]+1) { 
                cur_dp[i + j] = max(cur_dp[i + j], dp[u][i] + dp[v][j]); 
            }
        }
        rep(i,0,cur_dp_siz+1) dp[u][i] = cur_dp[i]; 
        cur_siz += siz[v]; 
    } 
    for(int i = siz[u]; i > 0; i--) { 
        dp[u][i] = dp[u][i - 1] + val[u]; 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cin >> n >> k; 
    rep(i,1,n+1) { 
        cin >> s[i] >> e[i]; 
        int p; cin >> p; 
        adj[p].push_back(i); 
    }
    k++; 

    double lo = 0, hi = 2750 * 100'000 + 10; 
    const double eps = 1e-5; 
    val[0] = 0; 
    dfs_siz(0); 
    while(abs(hi - lo) > eps) { 
        double mi = (lo + hi) / 2.0 ; 
        rep(i,1,n+1) val[i] = double(e[i]) - mi * s[i]; 
        dfs(0); 
        if(dp[0][k] > -1e-9) lo = mi; 
        else hi = mi ; 
    }

    cout << fixed << setprecision(4) << lo << "\n"; 
}
