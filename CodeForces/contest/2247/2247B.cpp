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
    int n, k, m; cin >> n >> k >> m; 
    if(k > m) { 
        cout << "NO\n"; return; 
    }
    cout << "YES\n"; 
    vi ans(n, 1); 
    for(int i = 0; i < n; i += k) ans[i] = m - (k - 1); 
    for(int i : ans) cout << i << " " ; cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
