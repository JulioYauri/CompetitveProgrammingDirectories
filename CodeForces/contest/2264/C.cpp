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

const int mod = 998244353; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b ; }
int mul(ll a, ll b) { return a * b % mod; }
int bp(int a, int e) { 
    int ans = 1; 
    while(e) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1; 
    }
    return ans; 
}
int inv(int a) { return bp(a, mod - 2); }

void solve() {
	int n; cin >> n; 
    int total = 1; 
    rep(i,1,n) total = mul(total, i); 

    vl v(n); rep(i,0,n) cin >> v[i]; 
    sort(all(v)); 
    reverse(all(v)); 

    ll sum = accumulate(all(v), 0LL); 
    int ans = 0 ; 
    for(int i = n - 1; i > 0; i--) { 
        sum -= v[i]; 
        ll x = sum - 1LL * v[i] * i; 
        ans = add(ans, mul(x % mod, mul(total, inv(i)))); 
    }       
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
