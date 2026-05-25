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
    int n, m; cin >> n >> m; 
    vvi g(n, vi(m)); 
    rep(i,0,n) rep(j,0,m) { 
        char c; cin >> c; 
        g[i][j] = (c - '0') ; 
    }
    vvi asc = g, desc = g; 
    for(int i = n - 2; i >= 0; i--) rep(j,1,m) asc[i][j] += asc[i + 1][j - 1]; 
    rep(i,1,n) rep(j,1,m) desc[i][j] += desc[i - 1][j - 1]; 


    auto ok = [&](int ii, int jj) { 
        return ii >= 0 && jj >= 0 && ii < n && jj < m; 
    };
    rep(dist,1,n+m-1) { 
        ll total = 0 ; 
        rep(i,0,n) rep(j,0,m) if(g[i][j]) {
            { // asc1 
                int i1, j1; 
                if(ok(i - dist, j)) i1 = i - dist, j1 = j; 
                else i1 = 0, j1 = i + j - dist; 
                int i2, j2; 
                if(ok(i, j - dist)) i2 = i, j2 = j - dist; 
                else i2 = i + j - dist, j2 = 0; 
                if(ok(i1,j1)) total += asc[i1][j1]; 
                if(ok(i2 + 1, j2 - 1)) total -= asc[i2 + 1][j2 - 1]; 
            }        
            { // asc2
                int i1, j1; 
                if(ok(i, j + dist)) i1 = i, j1 = j + dist; 
                else j1 = m - 1, i1 = (i + j + dist) - j1; 
                int i2, j2; 
                if(ok(i + dist, j)) i2 = i + dist, j2 = j; 
                else i2 = n - 1, j2 = (i + j + dist) - i2; 
                if(ok(i1, j1)) total += asc[i1][j1]; 
                if(ok(i2 + 1, j2 - 1)) total -= asc[i2 + 1][j2 - 1]; 
            }            
            { // desc1 
                int i1, j1; 
                if(ok(i, j + dist)) i1 = i, j1 = j + dist; 
                else j1 = m - 1, i1 = (i - j - dist) + j1;  
                int i2, j2; 
                if(ok(i - dist, j)) i2 = i - dist, j2 = j; 
                else i2 = 0, j2 = -(i - j - dist); 
                if(ok(i1, j1)) total += desc[i1][j1]; 
                if(ok(i2 - 1, j2 - 1)) total -= desc[i2 - 1][j2 - 1]; 
            } 
            { // desc1 
                int i1, j1; 
                if(ok(i + dist, j)) i1 = i + dist, j1 = j; 
                else i1 = n - 1, j1 = i1 - (i - j + dist); 
                int i2, j2; 
                if(ok(i, j - dist)) i2 = i, j2 = j - dist; 
                else j2 = 0, i2 = (i - j + dist); 
                if(ok(i1,j1)) total += desc[i1][j1]; 
                if(ok(i2 - 1, j2 - 1)) total -= desc[i2 - 1][j2 - 1]; 
            }
            if(ok(i - dist, j)) total -= g[i - dist][j]; 
            if(ok(i + dist, j)) total -= g[i + dist][j]; 
            if(ok(i, j - dist)) total -= g[i][j - dist]; 
            if(ok(i, j + dist)) total -= g[i][j + dist]; 
        }
        cout << total / 2 << " "; 
    }
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
