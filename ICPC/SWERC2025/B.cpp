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


void solve() {
    int n, l, r; 
    cin >> n >> l >> r; 
    vi a(n); rep(i,0,n) cin >> a[i]; 
    sort(all(a)) ; 

    vi d(n); rep(i,0,n) d[i] = l - a[i]; 

    ll ans = 0; 
    { //  -> -> -> .... <- 
        // cerr << "minimo en L \n"; 
        // minimo en l 
        ll have = 0;  
        vl vals(n); 
        rep(i,0,n) { 
            vals[i] = (a[i] - l);  
        }
        vl p = vals; 
        rep(i,1,n) p[i] += p[i - 1]; 
        auto sum = [&](int lo, int hi) { 
            if(lo > hi) return 0LL; 
            if(lo == 0) return p[hi]; 
            return p[hi] - p[lo - 1]; 
        };
        rep(take,1,n+1) { 
            have += l - a[take - 1];
            int lo = max(n - take - 1, take - 1), hi = n;
            if(hi - lo <= 1) { 
                ans = max(ans, have) ; 
                continue; 
            }
            while(hi - lo > 1) { 
                int mi = lo + hi >> 1; 
                if(vals[mi] < 0) lo = mi; 
                else hi = mi; 
            }  
            // cerr << "take: " << take << "\n"; 
            // cerr << "  cur:" << have + sum(hi, n - 1) << ", hi: " << hi << "\n"; 
            ans = max(ans, have + sum(hi, n - 1)); 
        }
    }
    { // -> ....  <- <- <- <- 
        // minimo en r 
        // cerr << "minimo en R\n"; 
        ll have = 0; 
        vl vals(n); 
        rep(i,0,n) { 
            vals[i] = (r - a[i]); 
        }
        vl p = vals; 
        rep(i,1,n) p[i] += p[i - 1]; 
        auto sum = [&](int lo, int hi) { 
            if(lo > hi) return 0LL; 
            if(lo == 0) return p[hi]; 
            return p[hi] - p[lo - 1]; 
        };
        rep(take,1,n+1) { 
            have += a[n - take] - r; 
            int lo = -1, hi = min(take, n - take); 
            if(hi - lo <= 1) { 
                ans = max(ans, have) ; 
                continue; 
            }
            while(hi - lo > 1) { 
                int mi = lo + hi >> 1; 
                if(vals[mi] < 0) hi = mi; 
                else lo = mi; 
            }
            // cerr << "take: " << take << "\n"; 
            // cerr << "  cur:" << have + sum(0,lo) << " lo: " << lo << "\n"; 
            ans = max(ans, have + sum(0, lo)); 
        }
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
