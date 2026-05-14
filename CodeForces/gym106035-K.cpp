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


const int mod = 1'000'000'000 + 9; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    ll n; cin >> n; 
    ll ans = 1, e = n + 1, p = 2; 
    while(e) { 
        if(e % 2) ans = ans * p % mod; 
        p = p * p % mod; 
        e >>= 1; 
    }
    ans = ans - (n + 2) + mod; 
    ans = (ans % mod) + mod; 
    cout << ans % mod << "\n"; 
}
