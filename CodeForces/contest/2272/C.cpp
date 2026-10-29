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
    int n, x; cin >> n >> x; 
    vi a(n); 
    rep(i,0,n) cin >> a[i]; 

    int lo = 0, hi = 1'000'000'000 + 10; 
    // int lo = 0, hi = 10; 
    vector<bool> vis(n);
    while(hi - lo > 1) { 
        int mi = lo + (hi - lo) / 2; 
        fill(all(vis), false); 
        rep(i,1,n) { 
            if(a[i] - a[i - 1] <= mi) { 
                vis[i] = vis[i - 1] = true; 
            }
        }

        int total = 0; 
        rep(i,0,n) if(!vis[i]) { 
            if(i + 1 < n && a[i + 1] - a[i] <= 2LL * mi) { 
                total++; 
                vis[i + 1] = vis[i] = true; 
            }else { 
                total++; 
                vis[i] = true; 
            }
        }    
        if(total <= x) hi = mi; 
        else lo = mi; 
    }
    cout << hi << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
