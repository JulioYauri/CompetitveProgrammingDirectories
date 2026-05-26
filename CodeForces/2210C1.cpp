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
    vl a(n), b(n); 
    rep(i,0,n) cin >> a[i]; 
    rep(i,0,n) cin >> b[i]; 

    int ans = 0; 
    rep(i,0,n) { 
        if(i == 0) { 
            ans += (gcd(a[i], a[i + 1]) != a[i]); 
        }else if(i == n - 1) { 
            ans += (gcd(a[i], a[i - 1]) != a[i]); 
        }else{ 
            ll g1 = gcd(a[i], a[i - 1]), g2 = gcd(a[i], a[i + 1]); 
            ll c = g1 / gcd(g1, g2) * g2; 
            if(c != a[i]) ans++; 
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
