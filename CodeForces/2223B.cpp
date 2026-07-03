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
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int mul(ll a, ll b) { return a * b % mod; } 
int sub(int a, int b) { return  a < b ? a - b + mod : a - b; }
int bp(int a, int e) { 
    int ans = 1; 
    while(e) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1; 
    }
    return ans; 
}

const int N = 2000 + 10; 
int f[N], fi[N]; 

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};


void solve() {
	int n; cin >> n; 
    vl a(n); rep(i,0,n) cin >> a[i]; 
    vl b(n); rep(i,0,n) cin >> b[i]; 

    vl prods; prods.reserve(n * n) ; 
    rep(i,0,n) rep(j,0,n) prods.push_back(a[i] * b[j]); 
    sort(all(prods)); 
    prods.erase(unique(all(prods)), prods.end()) ; 
    auto gc = [&](ll x) { 
        return lower_bound(all(prods), x) - prods.begin(); 
    };


    FT ft(sz(prods) + 1) ; 
    int ans = 0; 
    for(int i = n - 1; i >= 0; i--) { 
        rep(j,0,n) { 
            ll p = a[i] * b[j]; 
            int id = gc(p); 
            ans = add(ans, mul(ft.query(id) % mod, f[n - 2])); 
        }
        rep(j,0,n) { 
            ll p = a[i] * b[j]; 
            int id = gc(p); 
            ft.update(id, 1); 
        }
    }
    FT ft2(n); 
    vl ac = a;
    int extra = 0 ; 
    sort(all(ac)); ac.erase(unique(all(ac)), ac.end()); 
    for(int i = n - 1; i >= 0; i--) { 
        int id = lower_bound(all(ac), a[i]) - ac.begin(); 
        extra = add(extra, ft2.query(id)); 
        ft2.update(id, 1); 
    } 
    extra = mul(extra, n); 
    extra = mul(extra, f[n - 2]); 
    ans = sub(ans, extra); 
    cout << mul(ans, fi[n]) << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    f[0] = 1; 
    rep(i,1,N) f[i] = mul(f[i - 1], i); 
    fi[N - 1] = bp(f[N - 1], mod - 2); 
    for(int i = N - 1; i; i--) fi[i - 1] = mul(fi[i], i); 

	int tt; cin >> tt; 
	while(tt--) solve();
}
