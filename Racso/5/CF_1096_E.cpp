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
        e >>= 1; 
    }
    return ans; 
}


const int N = 5100 + 10 ; 
int f[N], fi[N]; 
int C(int n, int k) { 
    if(k < 0 || n < k) return 0; 
    return mul(f[n], mul(fi[n - k], fi[k])); 
}

// sp - 1  
// sum 

int g(int sum, int sp, int mx) { 
    if(sp == 0) return sum == 0; 
    vi v(sp + 1); 
    rep(i,0,sp+1) { 
        if(sum - i * mx < 0) break; 
        v[i] = mul(C(sum - i * mx + sp - 1, sp - 1), C(sp, i)); 
    }
    int total = 0; 
    rep(i,0,sp+1) { 
        if(i % 2 == 0) total = add(total, v[i]); 
        else total = sub(total, v[i]); 
    }
    return total; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    f[0] = 1; 
    rep(i,1,N) f[i] = mul(f[i - 1], i); 
    fi[N - 1] = bp(f[N - 1], mod - 2); 
    for(int i = N - 1; i; i--) fi[i - 1] = mul(fi[i], i); 
    int p, s, r; cin >> p >> s >> r; 
    if(p == 1) { 
        cout << "1\n"; 
        return 0; 
    }
    
    if(s == 0) { 
        cout << bp(p, mod - 2) << "\n"; 
        return 0; 
    }

    int ans = 0 ; 
    rep(my,r,s+1) { 
        rep(cnt,0,p) { 
            int have = s - (cnt + 1) * my; 
            if(have < 0) break; 
            int total = mul(C(p - 1, cnt), g(have, p - 1 - cnt, my)); 
            ans = add(ans, mul(total, bp(cnt + 1, mod - 2))); 
        }
    }   
    
    int total = C(p - 1 + s - r, p - 1); 
    cout << mul(ans, bp(total, mod - 2)) << "\n"; 
}
