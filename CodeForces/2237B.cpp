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
    int ans = 0; 
    rep(i,0,n) { 
        int first = -1; 
        rep(j,i,n) { 
            if(a[j] <= b[i]) { 
                first = j;
                break; 
            }
        }
        if(first == -1) { 
            cout << "-1\n"; return; 
        }
        ans += first - i; 
        rotate(a.begin() + i, a.begin() + first, a.begin() + first + 1); 
    }
    cout << ans << "\n";
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
