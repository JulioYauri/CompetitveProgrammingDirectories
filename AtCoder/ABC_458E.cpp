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

const int N = 3'000'000 + 5; 
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

int f[N], fi[N]; 
int C(int n, int k) { 
    if(n < k || k < 0) return 0; 
    return mul(f[n], mul(fi[n - k], fi[k])); 
}
int cn(int n, int k)  { return C(n + k - 1, n); }

int solve(int first, vi cnt) { 
    int ans = 0, cur = first, used = 0, f_used = 0, q = cnt[0] + cnt[2]; 
    while(true) {
        if(cnt[cur] == 0) break ;
        cnt[cur]--; 
        used++; 
        if(cur == first) f_used++; 
        int two = used - 1; 
        if(cnt[1] < two) break; 
        int c1 = cn(cnt[first], f_used), c2 = cn(cnt[2 - first], used - f_used), cm = cn(cnt[1] - two, q + 1); 
        ans = add(ans, mul(c1, mul(c2, cm))); 
        cur = 2 - cur; 
    }
    return ans; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    f[0] = 1; 
    rep(i,1,N) f[i] = mul(f[i - 1], i) ; 
    fi[N - 1] = bp(f[N - 1], mod - 2); 
    for(int i = N - 1; i; i--) fi[i - 1] = mul(fi[i], i); 

    vi cnt(3); rep(i,0,3) cin >> cnt[i];
    cout << add(solve(0, cnt), solve(2, cnt)) << "\n"; 
}
