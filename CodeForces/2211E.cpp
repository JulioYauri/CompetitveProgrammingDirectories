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
    vvi ch(n); 
    vector<vl> nums(n); 
    vl val(n), num(n); 
    vi dp(n); 
    for(int node = n - 1; node >= 0; node--) { 
        cin >> val[node]; 
        int k; cin >> k; 
        ch[node].resize(k); 
        for(auto &v : ch[node]) cin >> v, v--; 
        ll worst = 1; 
        bool found = false; 
        num[node] = 1; 
        for(auto v : ch[node]) { 
            worst += dp[v]; 
            ll my_g = gcd(val[node], num[v]); 
            if(my_g > 1) { 
                num[node] = num[node] / gcd(my_g, num[node]) * my_g; 
                found = true; 
            }
        }
        if(found) { 
            dp[node] = worst - 1; 
        }else { 
            dp[node] = worst; 
            num[node] = val[node]; 
        }
        cout << dp[node] << endl; 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
