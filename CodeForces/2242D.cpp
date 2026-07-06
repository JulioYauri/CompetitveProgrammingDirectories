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
	string a, b; cin >> a >> b; 
    int n = sz(a), m = sz(b); 
    vi pa(n), pb(m); 
    rep(i,0,n) { 
        pa[i] = a[i] - '0'; 
        if(i) pa[i] = (pa[i] + pa[i - 1]) % 10; 
    }
    rep(i,0,m) { 
        pb[i] = b[i] - '0'; 
        if(i) pb[i] = (pb[i] + pb[i - 1]) % 10; 
    }

    if(pa.back() != pb.back()) { 
        cout << "-1\n"; return; 
    }
    vvi dp(n + 1, vi(m + 1, 0)) ; 
    rep(i,1,n+1) { 
        rep(j,1,m+1) { 
            if(pa[i - 1] == pb[j - 1]) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1); 
            dp[i][j] = max({dp[i][j], dp[i - 1][j], dp[i][j - 1]});
        }
    }   
    cout << dp[n][m] << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
