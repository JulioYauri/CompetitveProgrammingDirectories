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

ll solve(ll n) {
    if(n == 0) return 0; 
    vi digs; 
    while(n) digs.push_back(n % 10), n /= 10 ; 
    reverse(all(digs)); 

    vector memo(sz(digs), vector(2, vector(2, vector<ll>(2, -1))));
    auto dp = [&](auto &&self, int i, bool pos, bool z, bool sm) -> ll { 
        if(i == sz(digs)) return pos && z; 
        ll &h = memo[i][pos][z][sm]; 
        if(h != -1) return h; 
        int mx = sm ? 9 : digs[i]; 
        h = 0 ; 
        rep(d,0,mx+1) { 
            h += self(self, i + 1, pos ? pos : d > 0, z ? z : (d == 0 && pos), sm ? sm : d < mx); 
        }
        return h; 
    };
    return dp(dp,0,0,0,0); 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    ll n; cin >> n; 
    cout << solve(n) - (n / 10 - solve(n / 10)) << "\n"; 
}
