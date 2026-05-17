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

const int N = 100000 + 2; 
const int mod = 1'000'000'000 + 7; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b ; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(ll a, ll b) { return a * b % mod; }

signed main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m; cin >> n >> m; 
    vvi a(n, vi(m)); 
    rep(i,0,n) rep(j,0,m) cin >> a[i][j]; 

    vi dp(N); 
    for(int i : a[0]) dp[i]++; 
    rep(_,1,n) { 
        vi here(N); for(int x : a[_]) here[x]++; 
        vi ndp(N); 
        rep(i,1,N) { 
            int a = 0, b = 0; 
            for(int mult = i; mult < N; mult += i) { 
                a = add(a, dp[mult]); 
                b = add(b, here[mult]); 
            }   
            ndp[i] = mul(a, b); 
        }
        for(int i = N - 1; i > 0; i--) { 
            for(int mult = i * 2; mult < N; mult += i) ndp[i] = sub(ndp[i], ndp[mult]); 
        }
        rep(i,1,N) dp[i] = add(dp[i], ndp[i]);
        rep(j,0,m) dp[a[_][j]] = add(dp[a[_][j]], 1);   
    }
    rep(i,0,n) rep(j,0,m) dp[a[i][j]] = sub(dp[a[i][j]], 1); 
    int ans = 0; 
    rep(i,1,N) ans = add(ans, mul(i, dp[i])); 
    cout << ans << "\n"; 
}
