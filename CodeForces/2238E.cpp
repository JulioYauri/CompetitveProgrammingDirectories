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


const int inf = 1LL << 20; 
void solve() {
	int n; cin >> n; 
    string s; cin >> s; 
    vvi dp(n + 1, vi(n + 1, inf)); 
    dp[0][0] = 0; 
    vi vals; 
    for(char c : s) { 
        vvi ndp(n + 1, vi(n + 1, inf)); 
        if(c != 'T') { //  f
            rep(i,0,n) { 
                rep(j,0,n) if(dp[i][j] != inf) { 
                    ndp[i + 1][j + 1] = min(ndp[i + 1][j + 1], max(j + 1, dp[i][j]));        
                }
            }
        } 
        if(c != 'F') { 
            rep(i,0,n+1) { 
                rep(j,0,n+1) if(dp[i][j] != inf) { 
                    int mx = max(0, j - 1); 
                    ndp[i][mx] = min(ndp[i][mx], max(mx, dp[i][j]));
                }
            }
        }
        swap(dp,ndp); 
    }   
    int ans = 0; 
    rep(f,0,n+1) { 
        rep(s,0,n+1) if(dp[f][s] != inf)    
            ans = max(ans, f - dp[f][s]);        
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
