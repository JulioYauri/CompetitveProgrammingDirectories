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
    int n, c; cin >> n >> c; 
    vi a(n), b(n); 
    rep(i,0,n) cin >> a[i]; 
    rep(i,0,n) cin >> b[i]; 

    bool reorder = false;  
    rep(i,0,n) { 
        if(a[i] < b[i]) { 
            reorder = true; 
            break; 
        }
    }
    ll ans = 0 ;
    if(reorder) { 
        ans = c; 
        sort(all(a)); 
        sort(all(b)); 
        rep(i,0,n) { 
            if(a[i] < b[i]) { 
                cout << "-1\n"; return; 
            }
            ans += a[i] - b[i]; 
        }
    }else{ 
        rep(i,0,n) ans += a[i] - b[i]; 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
