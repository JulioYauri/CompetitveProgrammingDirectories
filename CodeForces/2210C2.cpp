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

const int LIM = 22; 
vi prs; 
bool is_prime(int n) { 
    if(n == 2) return true; 
    rep(i,2,n) if(n % i == 0) return false; 
    return true;    
}

void solve() {
	int n; cin >> n; 
    vl a(n), b(n); 
    rep(i,0,n) cin >> a[i]; 
    rep(i,0,n) cin >> b[i]; 
    
    vl gs(n - 1); 
    rep(i,1,n) gs[i - 1] = gcd(a[i], a[i - 1]) ; 
    vl mins(n);
    rep(i,0,n) { 
        ll lc = (i == 0 ? 1 : gs[i - 1]); 
        if(i < n - 1) lc = lc / gcd(lc, gs[i]) * gs[i]; 
        mins[i] = lc;   
    }

    vector<pair<ll, int>> dp;
    { 
        ll val = mins[0]; 
        bool found = false; 
        for(auto p : prs) { 
            if(p * val > b[0]) break; 
            if(p * val == a[0]) { 
                dp.emplace_back(a[0], 0); 
                found = true; 
            }else{ 
                dp.emplace_back(p * val, 1); 
            }
        }
        if(!found) dp.emplace_back(a[0], 0) ; 
    }
    rep(i,1,n) { 
        vector<pair<ll,int> > ndp; 
        ll val = mins[i]; 
        bool found = false; 
        for(auto p : prs) {
            if(p * val > b[i]) break; 
            if(p * val == a[i]) { 
                found = true; 
                int mx = 0 ; 
                for(auto [last, ops] : dp) { 
                    if(gcd(last, p * val) == gs[i - 1]) mx = max(mx, ops); 
                }
                ndp.emplace_back(p * val, mx); 
            }else{ 
                int mx = 0; 
                for(auto [last, ops] : dp) { 
                    if(gcd(last, p * val) == gs[i - 1]) mx = max(mx, ops + 1); 
                }
                ndp.emplace_back(p * val, mx) ; 
            } 
        }
        if(!found) {
            int mx = 0;  
            for(auto [last, ops] : dp) { 
                if(gcd(last, a[i]) == gs[i - 1]) mx = max(mx, ops); 
            }
            ndp.emplace_back(a[i], mx) ; 
        }
        swap(ndp, dp); 
    }
    int ans = 0 ; 
    for(auto [f, s] : dp) ans = max(ans, s); 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    prs.push_back(1) ; 
    rep(i,2,100) { 
        if(is_prime(i)) prs.push_back(i); 
        if(sz(prs) == LIM) break ;
    }

	int tt; cin >> tt; 
	while(tt--) solve();
}
