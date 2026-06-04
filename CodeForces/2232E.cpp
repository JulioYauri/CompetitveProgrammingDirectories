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

const int mod = 1'000'000'000 + 7; 
int mul(ll a, ll b) { return a * b % mod; }

void solve() {
    int n, k; cin >> n >> k; 
    vvi g(n, vi(n)); 

    rep(_,0,k) { 
        int siz; cin >> siz; 
        int r, c; cin >> r >> c; r--, c--; 
        string s; if(siz > 1) cin >> s; 
        g[r][c] = siz; 
        for(char x : s) { 
            if(x == 'R') c++; 
            else r++ ; 
            g[r][c] = siz; 
        }
    }
    int ans = 1; 
    for(int row = n - 1, cur_val = 1; row > 0; row--, cur_val += 2) { 
        int mn = 0, mx = row;
        bool found = false;  
        for(int i = row, j = 0; i >= 0; i--, j++) {
            if(g[i][j] == 0) continue; 
            if(g[i][j] == cur_val) { 
                found = true; 
                break; 
            }
            if(i > 0 && g[i][j] == g[i - 1][j]) mn = max(mn, j); 
            if(j > 0 && g[i][j] == g[i][j - 1]) mx = min(mx, j);
        }
        if(found) continue; 
        int cnt = 0; 
        rep(j,mn,mx+1) cnt += (g[row - j][j] == 0); 
        ans = mul(ans, cnt); 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
