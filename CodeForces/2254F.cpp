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
    vi b(n); rep(i,0,n) cin >> b[i]; 

    sort(all(a)); 
    sort(all(b)); 
    if(a == b) { 
        cout << "YES\n"; 
        return; 
    }

    int xr_a = 0, xr_b = 0; 
    rep(i,0,n) { 
        xr_a ^= a[i];
        xr_b ^= b[i]; 
    }

    rep(i,0,n) { 
        if((xr_a ^ a[i]) == xr_b) { 
            rep(j,0,n) { 
                if(i == j) continue; 
                a[j] ^= a[i]; 
            }
            sort(all(a)); 
            if(a == b) { 
                cout << "YES\n"; 
                return; 
            }
        }
    }
    cout << "NO\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
