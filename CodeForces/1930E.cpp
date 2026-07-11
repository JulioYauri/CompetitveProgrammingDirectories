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
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(ll a, ll b) { return a * b % mod; }
int bp(int a, int e) { 
    int ans = 1; 
    while(e) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1 ; 
    }
    return ans; 
}
const int N = 1'000'000 + 10 ; 
int f[N], fi[N]; 
int C(int n, int k) { 
    if(n < k || k < 0) return 0; 
    return mul(f[n], mul(fi[k], fi[n - k]));
}

void solve() {
    int n; cin >> n;
    rep(k,1,(n-1)/2+1) { 
        int ans = 1; 
        for(int take = k * 2; take < n; take += 2 * k) { 
            int cur = take - 2 * (k - 1); 
            int h = C(n - cur + 1, 2 * (k - 1) + 1);
            ans = add(ans, sub(C(n, take), h)); 
        }
        cout << ans << " " ; 
    }
    cout << "\n"; 
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
