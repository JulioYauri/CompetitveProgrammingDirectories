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
	
    int n, t; cin >> n >> t; 
    vii v(n); rep(i,0,n) cin >> v[i].first >> v[i].second; 

    sort(all(v)); 
    vi dp(t, -1) ; dp[0] = 0; 
    int ans = 0; 
    for(auto [a, b] : v) { 
        rep(i,0,t) if(dp[i] != -1) ans = max(ans, dp[i] + b); 
        for(int i = t - 1; i >= a; i--) if(dp[i - a] != -1) dp[i] = max(dp[i], dp[i - a] + b); 
    }
    ans = max(ans, *max_element(all(dp))); 
    cout << ans << "\n"; 
}
