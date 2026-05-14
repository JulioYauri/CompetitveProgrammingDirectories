#include <bits/stdc++.h>
using namespace std;
// errores de precision, F
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll; 
typedef vector<ll> vl; 
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<pii> vii;

typedef long double T; 
T eps = 1e-10; 

const int mod = 998244353; 
const int mod2 = 1e9 + 7; 
const int mod3 = 1e9 + 9; 

int add(int a, int b, const int& m) { return a + b >= m ? a + b - m : a + b; }
int mul(ll a, ll b, const int& m) { return a * b % m; }
int bp(int a, int e, const int& m) { 
    int ans = 1; 
    while(e > 0) { 
        if(e % 2) ans = mul(ans, a, m); 
        a = mul(a, a, m); 
        e >>= 1; 
    }
    return ans; 
}
int inv(int a, const int& m) { return bp(a, m - 2, m); }

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    ll x; cin >> x; 
    vl a(n); rep(i,0,n) cin >> a[i]; 
    sort(all(a)) ; 
    reverse(all(a)); 
    ll total = 0; 
    rep(i,0,n) { 
        int den = i + 1; 
        total += a[i] / den;
        a[i] %= den; 
    }

    if(total >= x) { 
        cout << "YES\n"; return 0; 
    }

    x -= total ; 
    int t1 = 0, t2 = 0, t3 = 0; 
    rep(i,0,n) { 
        t1 = add(t1, mul(a[i], inv(i + 1, mod), mod), mod);
        t2 = add(t2, mul(a[i], inv(i + 1, mod2), mod2), mod2); 
        t3 = add(t3, mul(a[i], inv(i + 1, mod3), mod3), mod3); 
    }

    if(t1 == total % mod && t2 == total % mod2 && t3 == total % mod3) { 
        cout << "YES\n"; return 0; 
    }

    T totald = 0 ; 
    rep(i,0,n) { 
        totald += (T)(a[i]) / (i + 1); 
    }
    // cerr << "totald: " << totald << "  x: " << x << "\n"; 
    if(totald + eps >= x) { 
        cout << "YES\n"; return 0 ; 
    }
    cout << "NO\n"; 
}
