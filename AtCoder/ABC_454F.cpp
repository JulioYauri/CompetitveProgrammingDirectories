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
    int n, mod; cin >> n >> mod; 
    vl v(n); rep(i,0,n) cin >> v[i]; 
    vl a; 
    for(int l = 0, r = n - 1; l < r; l++, r--) { 
        ll val = (v[l] - v[r] + mod) % mod; 
        a.push_back(val); 
    }

    
    a.insert(a.begin(), 0); 
    for(int i = sz(a) - 1; i; i--) { 
        a[i] -= a[i - 1];
        if(a[i] < 0) a[i] += mod; 
    } 

    ll ans = 1LL << 62; 
    rep(it,0,2) { 
        sort(all(a)) ; 
        ll sum = accumulate(all(a), 0LL), h = sum; 
        for(int i = sz(a) - 1; i >= 0; i--) { 
            if(sum - mod >= 0) sum -= mod, h -= a[i]; 
            else break ;
        }
        ans = min(ans, h); 
        for(auto &x : a) x = (mod - x) % mod; 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
