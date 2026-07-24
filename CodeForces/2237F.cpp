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


const int inf = 1'000'000; 
void solve() {
    int n, m; cin >> n >> m; 
    vi a(n); rep(i,0,n) cin >> a[i], a[i]--; 
    deque<int> dp(m, -inf); dp[0] = (a[0] == 0); 
    int mx = dp[0]; 
    rep(i,1,n) { 
        dp.push_front(mx);
        dp[m - 1] = max(dp[m - 1], dp[m]); 
        if(a[i] == 0) { 
            dp[0]++; 
            mx = max(mx, dp[0]); 
        }else{ 
            dp[a[i]] = max(dp[a[i]], dp[m]); 
            dp[a[i]]++; 
            mx = max(mx, dp[a[i]]); 
        }
        dp.pop_back(); 
    }
    cout << n - dp.back() << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
