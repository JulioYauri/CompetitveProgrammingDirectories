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

ll sq(ll n) { return n * n; }

void solve() {
    int n; cin >> n;
    vi a(2 * n + 1); 
    rep(i,1,2*n+1) cin >> a[i]; 
    vl dp(2 * n + 1); 
    vi pos(n + 1); 
    rep(i,1,2*n+1) { 
        dp[i] = dp[i - 1] + 1; 
        if(pos[a[i]] != 0) { 
            dp[i] = max(dp[pos[a[i]] - 1] + sq(i - pos[a[i]] + 1), dp[i]); 
        } 
        pos[a[i]] = i; 
    }
    cout << dp[n * 2] << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
