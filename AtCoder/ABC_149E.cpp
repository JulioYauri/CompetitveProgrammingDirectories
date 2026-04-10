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

const int N = 100000 + 4; 
ll a[N], p[N]; 
ll sum(int l, int r) { 
    if(l > r) return 0LL; 
    if(l == 0) return p[r]; 
    return p[r] - p[l - 1] ; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    ll m; cin >> m; 
    rep(i,0,n) cin >> a[i]; 
    sort(a, a + n); 
    
    rep(i,0,n) { 
        p[i] = a[i]; 
        if(i) p[i] += p[i - 1]; 
    }
    
    ll low = 0, high = 2 * a[n - 1] + 10; 
    while(high - low > 1) { 
        ll mid = low + (high - low) / 2; 
        ll c = 0;
        // sumas q sean >= a mid 
        for(int i = n - 1; i >= 0; i--) { 
            int lo = -1, hi = n; 
            while(hi - lo > 1) { 
                int mi = lo + (hi - lo) / 2; 
                if(a[i] + a[mi] >= mid) hi = mi; 
                else lo = mi; 
            }
            c += n - hi; 
        }
        if(c >= m) low = mid; 
        else high = mid; 
    }

    ll ans = 0, have = 0; 
    for(int i = n - 1; i >= 0; i--) { 
        int lo = -1, hi = n; 
        while(hi - lo > 1) { 
            int mi = lo + (hi - lo) / 2; 
            if(a[i] + a[mi] >= high) hi = mi; 
            else lo = mi; 
        }
        ans += 1LL * (n - hi) * a[i] + sum(hi, n - 1); 
        have += n - hi; 
    }
    cout << ans + low * (m - have) << "\n"; 

}
