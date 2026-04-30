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
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int bp(int a, int e) { 
    int ans = 1; 
    while(e > 0) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1; 
    }
    return ans; 
}

const int N = 500000 + 10; 
int f[N], p2[N], fi[N]; 
int C(int n, int k) { 
    if(n < k || k < 0) return 0; 
    return mul(f[n], mul(fi[n - k], fi[k])); 
}

void solve() {
	int n, k; cin >> n >> k; 
    vi a(k); rep(i,0,k) cin >> a[i]; 
    
    vi pmx = a;             
    rep(i,1,k) pmx[i] = max(pmx[i], pmx[i - 1]); 
    
    vi pos(n + 1, -1);      
    rep(i,0,k) pos[a[i]] = i; 

    int ans = 0; 
    rep(u,1,n+1) { 
        if(pos[u] == -1) { 
            // en cuantas perm u es < q alguien de la izq
            if(pmx.back() > u) { 
                ans = add(ans, mul(f[n - k], p2[u - 1])); 
            }else{ 
                int m = u - k - 1; 
                int sum = C(n - k, n - k - m);
                int total = mul(sum, f[n - k - 1 - m]);
                total = mul(total, f[m]); 
                total = sub(f[n - k], total); 
                ans = add(ans, mul(total, p2[u - 1])); 
            }
        }else{ 
            int mxL = (pos[u] == 0 ? 0 : pmx[pos[u] - 1]); 
            if(mxL > u) ans = add(ans, mul(f[n - k], p2[u - 1])); 
        }
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    p2[0] = f[0] = 1; 
    rep(i,1,N) p2[i] = add(p2[i - 1], p2[i - 1]), f[i] = mul(f[i - 1], i); 

    fi[N - 1] = bp(f[N - 1], mod - 2); 
    for(int i = N - 1; i; i--) fi[i - 1] = mul(fi[i], i); 

	int tt; cin >> tt; 
	while(tt--) solve();
}
