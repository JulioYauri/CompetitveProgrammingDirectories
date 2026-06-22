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
    string s; cin >> s; 
    int k; cin >> k; 
    int n = sz(s); 
    s.insert(s.begin(), '#'); 

    int have = 0 ; 
    vi b(n + 1); 
    rep(i,0,sz(s)-2) { 
        if(s[i] == 'A' && s[i + 1] == 'B' && s[i + 2] == 'C') { 
            have++; 
            b[i] = b[i + 1] = b[i + 2] = have; 
        }
    }

    if((have + k) * 3 > n) { 
        cout << "-1\n"; return ;
    }

    auto get = [&](int i) { 
        set<int> s; 
        rep(j,0,3) if(b[i + j]) s.insert(b[i + j]) ; 
        return s; 
    };
    auto isABC = [&](int i)     { 
        return i + 2 < sz(s) && b[i] && b[i] == b[i + 2] ; 
    };

    int inf = 1 << 25; 
    vvi dp(n + 1, vi(k + 1, inf)), dp2(n + 1, vi(k + 1, inf)); 
    rep(i,0,3) dp[i][0] = dp2[i][0] = 0 ; 
    rep(i,3,n+1) { 
        if(isABC(i - 2)) {  
            rep(j,0,k+1) dp[i][j] = min(dp[i - 3][j], dp2[i - 3][j]); 
        }else{ 
            int add = (s[i - 2] != 'A') + (s[i - 1] != 'B') + (s[i] != 'C'); 
            set<int> my = get(i - 2); 
            for(int last = i - 3; last >= max(0, i - 5); last--) { 
                int extra = 1; 
                if(last - 2 > 0) { 
                    set<int> his = get(last - 2); 
                    for(auto x : my) if(!his.count(x)) extra --; 
                }else{ 
                    extra -= sz(my);  
                }
                rep(j,0,k+1) { 
                    if(j - extra >= 0 && j - extra <= k) { 
                        dp[i][j] = min(dp[i][j], dp[last][j - extra] + add); 
                    }
                }
            }
            int extra = 1 - sz(my); 
            if(i >= 6) { 
                rep(j,0,k+1) { 
                    if(j - extra >= 0 && j - extra <= k) { 
                        dp[i][j] = min(dp[i][j], dp2[i - 6][j - extra] + add); 
                    }
                }
            }
        }
        rep(j,0,k+1) dp2[i][j] = min(dp[i][j], dp2[i - 1][j]); 
    }

    cout << dp2[n][k] << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int tt; cin >> tt; 
    while(tt--) solve(); 

}
