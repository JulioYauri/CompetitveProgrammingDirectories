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
    int n; cin >> n; 
    vl v(n); rep(i,0,n) cin >> v[i]; 
    vl ans(n); 
    rep(i,0,n) { 
        fill(all(ans), 0); 
        int l = (i - 1 + n) % n, r = (i + 1) % n; 
        rep(_,1,n) { 
            ll l_val = max(v[l], ans[(l + 1) % n]); 
            ll r_val = max(ans[(r - 1 + n) % n], v[(r - 1 + n) % n]); 
            if(l_val < r_val) { 
                ans[l] = l_val ; 
                l = (l - 1 + n) % n; 
            }else{ 
                ans[r] = r_val; 
                r = (r + 1) % n; 
            }
        }
        cout << accumulate(all(ans), 0LL) << " "; 
    }
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
