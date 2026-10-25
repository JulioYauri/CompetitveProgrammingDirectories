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


void solve() {
    int n, m; cin >> n >> m; 
    vi a(n + 1), b(m + 1); 
    rep(i,1,n+1) cin >> a[i]; 
    rep(i,1,m+1) cin >> b[i]; 

    vector<bool> dp(n + 1, false); 
    dp[0] = 1; 
    rep(i,1,m+1) { 
        int x = b[i];
        vector<bool> ndp(n + 1, false);  
        rep(j,1,n+1) { 
            if(a[j] == x && dp[j - 1]) { 
                ndp[j] = true; 
            }
        }       
        if(x <= n) { 
            int min_pos = -1; 
            rep(i,0,n+1) { 
                if(dp[i]) { 
                    min_pos = i; 
                    break; 
                }
            }
            if(min_pos != -1) { 
                if(min_pos + x <= n) { 
                    rep(j,min_pos+x,n+1) ndp[j] = true; 
                }
            }
        }
        swap(dp, ndp); 
    }
    cout << (dp[n] ? "YES\n" : "NO\n") ; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
