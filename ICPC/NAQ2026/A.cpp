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
int bp(int a, int e) { 
    int ans = 1; 
    while(e) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1; 
    }
    return ans; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    ll n; cin >> n; 
    n %= mod; 
    n = mul(n, mul(add(n, 1), add(n, 2))); 
    n = mul(n, bp(6, mod - 2)); 
    cout << n << "\n"; 
}
