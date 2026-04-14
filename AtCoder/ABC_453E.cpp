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
const int N = 200000 + 3; 
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

void upd(int l, int r, vi& d) { 
    d[l]++; 
    if(r + 1 < sz(d)) d[r + 1]--; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    f[0] = 1;           
    rep(i,1,N) f[i] = mul(f[i - 1], i); 
    fi[N - 1] = bp(f[N - 1], mod - 2); 
    for(int i = N - 1; i; i--) fi[i - 1] = mul(fi[i], i); 

    int n; cin >> n; 
    vii v(n); rep(i,0,n) cin >> v[i].first >> v[i].second; 

    vi d(n + 1), d2(n + 1);
    int m1, m2; 
    if(n % 2 == 0) m1 = m2 = n / 2; 
    else m1 = n / 2, m2 = n / 2 + 1; 

    for(auto [l, r] : v) { 
        upd(l, r, d); 
        if(l <= m1 && m2 <= r) { 
            int mn = min(m1 - l, r - m2)  ;
            upd(m1 - mn, m2 + mn, d2); 
        }
    }
    rep(i,1,n+1) { 
        d[i] += d[i - 1] ; 
        d2[i] += d2[i - 1] ; 
    }
    
    int ans = 0; 
    rep(siz,1,n) { 
        int L = d[siz], R = d[n - siz], LR = d2[siz]; 
        L -= LR; 
        R -= LR;
        if(L + R + LR != n) continue; 
        int need = siz - L ; 
        ans = add(ans, C(LR, need)); 
    }
    cout << ans << "\n"; 

}
