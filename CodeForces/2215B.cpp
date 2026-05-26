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

const int M = 100 ; 
int d[M], gc[M][M], cur_num[M], ptr; 
void conv(ll n, ll base) { 
    while(n > 0) { 
        cur_num[ptr] = n % base; 
        n /= base; 
        ptr++; 
    } 
}  
void solve() {
    ll n; cin >> n; 
    if(n == 1) { 
        cout << "0\n"; return; 
    }
    ll cur_base = 2;
    int ans = 0; 
    while(true) {
        ptr = 0; 
        conv(n, cur_base);  
        if(ptr <= 2) break; 
        ll g = 0; 
        for(int l = 0, r = 0; l < ptr; l = r) { 
            while(l == r || (r < ptr && cur_num[r] == cur_num[r - 1])) r++; 
            g = gc[g][r - l]; 
        }
        ans += d[g];  
        cur_base++; 
    }
    auto check = [&](ll a, ll xp1) { 
        return xp1 > 1 && a < xp1 - 1; 
    };
    for(ll a = 1; a * a <= n; a++) { 
        if(n % a == 0) { 
            ans +=  check(a, n / a); 
            if(a * a != n) ans += check(n / a, a); 
        }
    }
    cout << ans << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    rep(i,2,M) { 
        rep(j,2,i+1) { 
            d[i] += (i % j == 0) ; 
        }
    }
    rep(i,0,M) rep(j,0,M) { 
        if(i == j && i == 0) gc[i][j] = 0; 
        else gc[i][j] = gcd(i, j); 
    }

	int tt; cin >> tt; 
	while(tt--) solve();
}
