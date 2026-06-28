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
    vi a(n); rep(i,0,n) cin >> a[i]; 

    int xr = 0; 
    rep(i,0,n) xr ^= a[i]; 

    if(xr == 0) { 
        cout << "1\n"; return; 
    }
    if(n == 1) { 
        cout << "0\n"; return; 
    }

    int ans = 0; 
    rep(i,0,n) { 
        int xr_without = (xr ^ a[i]); 
        if(xr_without <= a[i]) { 
            ans++; 
        }
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
