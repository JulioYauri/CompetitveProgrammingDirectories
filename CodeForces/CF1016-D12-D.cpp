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

const int N = 100 + 4; 
int n, m; 
int a[N], b[N], ca[N], cb[N], ans[N][N], c[N][N]; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    cin >> n >> m; 
    rep(i,0,n) cin >> a[i]; 
    rep(i,0,m) cin >> b[i]; 

    for(int bit = 0; bit <= 30; bit++) { 
        rep(i,0,n) ca[i] = (a[i] >> bit) & 1; 
        rep(i,0,m) cb[i] = (b[i] >> bit) & 1; 
        int total = 0; 
        rep(i,0,n) total += ca[i]; 
        rep(i,0,m) total += cb[i]; 
        if(total % 2) { 
            cout << "NO\n"; return 0; 
        }
        rep(i,0,n) rep(j,0,m) c[i][j] = 0; 
        if(n < m) { 
            rep(i,0,n) if(ca[i]) {      
                c[i][0] ^= 1; 
                cb[0] ^= 1; 
            }
            vi cols; 
            rep(j,0,m) if(cb[j]) cols.push_back(j); 
            assert(sz(cols) % 2 == 0) ; 
            for(int i = 0; i < sz(cols); i += 2) { 
                int j1 = cols[i], j2 = cols[i + 1]; 
                c[0][j1] ^= 1; 
                c[0][j2] ^= 1; 
            }
        }else{ 
            rep(j,0,m) if(cb[j]) { 
                c[0][j] ^= 1; 
                ca[0] ^= 1; 
            } 
            vi rows; 
            rep(i,0,n) if(ca[i]) rows.push_back(i); 
            assert(sz(rows) % 2 == 0); 
            for(int i = 0; i < sz(rows); i += 2) { 
                int i1 = rows[i], i2 = rows[i + 1]; 
                c[i1][0] ^= 1; 
                c[i2][0] ^= 1; 
            }
        }
        rep(i,0,n) rep(j,0,m) ans[i][j] |= (c[i][j] << bit); 
    }
    cout << "YES\n"; 
    rep(i,0,n) rep(j,0,m) cout << ans[i][j] << " \n"[j == m - 1]; 
}
