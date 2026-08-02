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
	int n, qq; cin >> n >> qq; 
    vector<vvi> p(2, vvi(2, vi(n + 1))) ; 
    string a, b; cin >> a >> b; 
    rep(i,0,n) {
        int ii = 0, jj = 0 ;  
        if(a[i] == '1') ii = 1; 
        if(b[i] == '1') jj = 1; 
        p[ii][jj][i + 1] = 1; 
    }

    rep(i,0,2) rep(j,0,2) rep(k,1,n+1) p[i][j][k] += p[i][j][k - 1]; 

    while(qq--) { 
        int l, r; cin >> l >> r ; 
        int t01 = p[0][1][r] - p[0][1][l - 1]; 
        int t10 = p[1][0][r] - p[1][0][l - 1]; 
        int t11 = p[1][1][r] - p[1][1][l - 1]; 
        int t00 = p[0][0][r] - p[0][0][l - 1]; 
        if(t01 < t10) swap(t01, t10); 
        t01 -= t10; 
        if(t11 + t00 < t01) cout << "NO\n"; 
        else cout << "YES\n"; 
    }

}   


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
