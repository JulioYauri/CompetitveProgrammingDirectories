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

#define cerr if(false) cerr 
void solve() {
    int n; cin >> n; 
    vi a(n + 1), b(n + 1); 
    rep(i,1,n+1) cin >> a[i]; 
    rep(i,1,n+1) cin >> b[i]; 

    vi last_a(n + 1, n + 1), last_b(n + 1, n + 1), dp(n + 2); 
    ll ans = 0; 
    for(int i = n; i; i--) { 
        if(a[i] == b[i]) { 
            if(a[i] == n) dp[i] = n - i + 1; 
            else{ 
                int to = min(last_a[a[i] + 1], last_b[b[i] + 1]); 
                dp[i] = dp[to] + to - i; 
            }
            if(a[i] == 1) ans += dp[i];
            else { 
                int to = min(last_a[1], last_b[1]); 
                ans += dp[to] + to - i; 
            } 
        }else if(a[i] != 1 && b[i] != 1) { 
            int to = min(last_a[1], last_b[1]); 
            ans += dp[to] + to - i; 
        }
        last_a[a[i]] = i; 
        last_b[b[i]] = i; 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
