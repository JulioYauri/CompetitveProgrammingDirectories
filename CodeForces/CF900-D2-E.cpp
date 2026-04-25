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

vi p[3]; 


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    string s; cin >> s; 
    int m; cin >> m; 

    vi v(n); 
    rep(i,0,n) { 
        if(s[i] == '?') { 
            v[i] = 2; 
            continue; 
        }
        v[i] = (s[i] == 'a') ; 
        if(i % 2) v[i] ^= 1; 
    }

    rep(i,0,3) p[i].assign(n, 0); 
    rep(i,0,n) p[v[i]][i] = 1; 
    rep(i,0,3) rep(j,1,n) p[i][j] += p[i][j - 1]; 

    vii to(n + 1, make_pair(-1, -1)) ; 
    for(int l = 0, r = m - 1; r < n; l++, r++) { 
        int have = p[l % 2][r] - (l == 0 ? 0 : p[l % 2][l - 1]); 
        if(have == 0) to[r + 1] = {l + 1, p[2][r] - (l == 0 ? 0 : p[2][l - 1])};
        else to[r + 1] = {-1, -1} ;
    }

    auto merge = [&](pii p1, pii p2) { 
        if(p1.first != p2.first) return p1.first > p2.first ? p1 : p2; 
        return p1.second < p2.second ? p1 : p2; 
    };

    vii dp(n + 1) ; dp[0] = {0, 0}; 
    rep(i,1,n+1) { 
        dp[i] = dp[i - 1]; 
        auto [last, q] = to[i]; 
        if(last != -1) { 
            dp[i] = merge(dp[i], {dp[last - 1].first + 1, dp[last - 1].second + q});
        }
    }
    
    cout << dp.back().second << "\n"; 
}
