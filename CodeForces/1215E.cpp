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



signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    vi a(n); rep(i,0,n) cin >> a[i], a[i]--; 
    
    vi c = a; 
    sort(all(c)); 
    c.erase(unique(all(c)), c.end()); 
    rep(i,0,n) a[i] = lower_bound(all(c), a[i]) - c.begin() ; 

    int C = sz(c); 
    vvi pos(C); 
    rep(i,0,n) { 
        pos[a[i]].push_back(i); 
    }

    vector cnt(C, vl(C)); 
    rep(i,0,C) { 
        rep(j,0,C) { 
            if(i == j) continue; 
            auto &a = pos[i]; 
            auto &b = pos[j]; 
            int ptr = 0; 
            for(int x : a) { 
                while(ptr < sz(b) && b[ptr] < x) ptr++; 
                cnt[i][j] += ptr; 
            }
        }
    }

    ll inf = 1LL << 62; 
    vl dp(1 << C, inf) ; 
    dp[0] = 0; 
    rep(mask,1,1<<C) { 
        rep(i,0,C) { 
            if((mask >> i & 1) == 0) continue; 
            int lm = mask ^ 1 << i; 
            ll total = 0;
            int cm = mask; 
            while(cm) { 
                total += cnt[i][__builtin_ctz(cm)]; 
                cm &= (cm - 1); 
            }
            dp[mask] = min(dp[mask], dp[lm] + total); 
        }
    }
    cout << dp.back() << "\n"; 
}

