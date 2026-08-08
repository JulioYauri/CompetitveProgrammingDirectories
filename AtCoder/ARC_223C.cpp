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

int bp(int a, int e, int mod) { 
	int ans = 1; 
	while(e) { 
		if(e & 1) ans = 1LL * ans * a % mod; 
		a = 1LL * a * a % mod; 
		e >>= 1; 
	}
	return ans; 
}

ll go(vi &v, int l, int r) { 
    if(l >= r) return 0; 
    int m = l + r >> 1; 
    ll ans = 0; 
    ans += go(v, l, m) ; 
    ans += go(v, m + 1, r); 
    rep(i,l,m+1) ans += upper_bound(v.begin() + m + 1, v.begin() + r + 1, v[i]) - (v.begin() + m + 1); 
    inplace_merge(v.begin() + l, v.begin() + m + 1, v.begin() + r + 1); 
    return ans; 
}


void solve() {
    int n; cin >> n; 
    vi c(n), a(n); 
    rep(i,0,n) { 
		cin >> a[i]; 
		c[a[i] % n]++; 
    }
    rep(i,0,n) if(c[i] > 1) { 
        cout << "0\n"; return; 
    }

	sort(all(a), [&](int l, int r) { 
		return l % n < r % n; 
	});

    ll invs = go(a, 0, n - 1) ; 
    ll ans = 1; 
    rep(diff,1,n) { 
        int total = n - diff; 
        ans = ans * bp(diff, total, n) % n; 
    }
    cout << (invs % 2 ? (n - ans) % n : ans) << "\n"; 
}  


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
