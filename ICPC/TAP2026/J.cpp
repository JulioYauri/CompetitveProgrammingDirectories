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

    string s; cin >> s; 
    int n = sz(s); 
    vi v(n); 
    rep(i,0,n) { 
        if(s[i] == 'T') v[i] = 0; 
        else if(s[i] == 'A') v[i] = 1; 
        else v[i] = 2; 
    }
    
    vvi dp(n, vi(n, 0)); 
    rep(i,0,n-2) { 
        if((v[i] ^ v[i + 1] ^ v[i + 2]) == 3) { 
            dp[i][i + 2] = 1; 
        }
    }
    rep(i,0,n) rep(j,0,n) if(i > j) dp[i][j] = 1; 
    
    for(int len = 6; len <= n; len += 3) { 
        rep(lo,0,n) { 
            int hi = lo + len - 1; 
            if(hi >= n) break; 
            rep(l,0,4) { 
                int r = 3 - l, tot = 0; 
                rep(i,0,l) tot ^= v[lo + i]; 
                rep(i,0,r) tot ^= v[hi - i]; 
                if(tot == 3) dp[lo][hi] |= dp[lo + l][hi - r]; 
            }
            if(v[lo] != v[hi]) { 
                int want = (3 ^ v[lo] ^ v[hi]); 
                rep(i,lo+1,hi) { 
                    if(v[i] == want) { 
                        dp[lo][hi] |= (dp[lo + 1][i - 1] && dp[i + 1][hi - 1]); 
                    }
                }
            }
            for(int i = lo + 2; i < hi; i += 3) { 
                dp[lo][hi] |= (dp[lo][i] && dp[i + 1][hi]); 
            }
        }
    }
    cout << (dp[0][n - 1] ? "S\n" : "N\n");
}
