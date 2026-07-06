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



signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, c, k; cin >> n >> c >> k; 
    vl d(n); 
    rep(i,0,n) cin >> d[i]; 

    const ll inf = 1LL << 62; 
    vector<vl> dp(n, vl(2, inf)); 
    dp[0][0] = (-d[0] + 1) * c + k; 
    dp[0][1] = c + k; 

    rep(i,1,n) { 
        dp[i][1] = dp[i - 1][1] + c + k; 
        dp[i][1] = min(dp[i][1], dp[i - 1][0] + d[i] * c) ; 
        dp[i][0] = dp[i - 1][0] ; 
        dp[i][0] = min(dp[i][0], dp[i - 1][1] + (-d[i] + 1) * c + k); 
    }
    cout << dp.back()[1] << "\n"; 
}
