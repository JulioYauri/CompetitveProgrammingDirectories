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
    int c[3] = { }; 
    rep(i,0,n) { 
        int x; cin >> x; 
        c[x]++; 
    }
    int mn = min(c[1], c[2]), ans = c[0] + mn;
    c[1] -= mn; 
    c[2] -= mn; 
    ans += c[1] / 3; 
    ans += c[2] / 3; 
    cout << ans << "\n";  
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
