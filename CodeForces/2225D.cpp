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
ll f0(ll a) { return (a + 1) / 4 + 1; }
ll f1(ll a) { return (a + 3) / 4; }
void solve() {
    ll n, x; cin >> n >> x; 
    ll l0 = f0(x - 1), r0 = f0(n) - l0; 
    ll l1 = f1(x - 1), r1 = f1(n) - l1; 
    l0 %= mod, r0 %= mod, l1 %= mod, r1 %= mod; 
    cout << (l0 * r0 + l1 * r1) % mod << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
