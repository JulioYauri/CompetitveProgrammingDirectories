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
    int n, k; cin >> n >> k; 
    vl vals(n); rep(i,0,n) cin >> vals[i]; 
    sort(all(vals)); 
    n--; 
    ll lo = 0, hi = 3e10; 
    vector<pair<int,ll> > dp(1 << n); 
    while(hi - lo > 1) { 
        ll mi = (lo + hi) / 2; 
        fill(all(dp), make_pair(0,0));
        rep(msk,1,1<<n) { 
            rep(bit,0,n) if((msk >> bit) & 1) { 
                auto [gr, rem] = dp[msk ^ (1 << bit)]; 
                if(rem + vals[bit] >= mi) dp[msk] = max(dp[msk], {gr + 1, 0}); 
                else dp[msk] = max(dp[msk], {gr, rem + vals[bit]}); 
            }
        }
        if(dp[(1 << n) - 1].first >= k) lo = mi; 
        else hi = mi; 
    }  
    cout << lo + vals.back() << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
