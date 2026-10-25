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



signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    map<int,int> mp; 
    rep(i,0,n) { 
        int x; cin >> x; 
        mp[x]++; 
    }

    int ans = 0; 
    for(auto [f, s] : mp) { 
        if(f <= s) ans += s - f; 
        else ans += s; 
    }

    cout << ans << "\n"; 
}
