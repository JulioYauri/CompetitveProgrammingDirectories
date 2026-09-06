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
    string s; cin >> s; 
    if(s == string(n, s[0])) { 
        cout << (n == 1 ? 0 : (n == 2 ? 1 : -1)) << "\n"; 
        return; 
    }
    int c1 = 0, c0 = 0 ; 
    for(int l = 0, r; l < n; l = r) { 
        r = l + 1; 
        while(r < n && s[l] == s[r]) r++; 
        if(s[l] == '0') c0 += (r - l - 1) ; 
        else c1 += (r - l - 1) ; 
    }
    
    int ans = 1 << 20;
    vii ps = {{1, 1}, {1, 0}, {0, 1}, {0, 0}};  
    for(auto [first, last] : ps) { 
        int cur0 = c0 + (s[0] == '0') * first + (s.back() == '0') * last; 
        int cur1 = c1 + (s[0] == '1') * first + (s.back() == '1') * last; 
        if(abs(cur1 - cur0) <= 1) ans = min(ans, cur0 + cur1); 
    }
    cout << (ans == (1 << 20) ? -1 : ans) << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
