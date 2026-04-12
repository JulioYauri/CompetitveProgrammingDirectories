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

const int N = 1'000'000 + 5;
ll cnt[N * 2], tot[N * 2], pcnt[N * 2]; 
ll sum(int l, int r) { 
    if(l > r) return 0; 
    return tot[r] - (l == 0 ? 0 : tot[l - 1]); 
}
ll rcnt(int l, int r) { 
    if(l > r) return 0; 
    return pcnt[r] - (l == 0 ? 0 : pcnt[l - 1]);     
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    ll x, y; cin >> x >> y; 
    rep(i,0,n) { 
        int q; cin >> q; 
        cnt[q] ++; 
        tot[q] += q; 
    }

    rep(i,0,N * 2) { 
        pcnt[i] = cnt[i]; 
        if(i) pcnt[i] += pcnt[i - 1], tot[i] += tot[i - 1]; 
    }
    ll ans = 1LL << 62; 
    int lim = x / y; 
    rep(g,2,N) { 
        ll cur = 0; 
        for(int mul = g, l = 1; l < N; mul += g, l += g) {
            int m = max(l, mul - lim); 
            { // [m, mul - 1]
                cur += (1LL * mul * rcnt(m, mul - 1) - sum(m, mul - 1)) * y; 
            }       
            if(m - 1 >= l) { // [l, m - 1]
                cur += 1LL * rcnt(l, m - 1) * x; 
            }
        }   
        ans = min(ans, cur); 
    }
    cout << ans << "\n"; 
}
