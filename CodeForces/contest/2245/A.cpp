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
    int n, k; cin >> n >> k ;
    string s; cin >> s; 
    if(k > n / 2) { 
        cout << "-1\n"; return ;
    }
    int ans = 0; 
    rep(i,0,k) ans += (s[i] == 'L'); 
    for(int i = n - 1; i >= n - k; i--) ans += (s[i] == 'R') ; 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
