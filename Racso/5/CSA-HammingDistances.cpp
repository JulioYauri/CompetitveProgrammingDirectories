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

const int B = 8; 
const int M = 17; 
int cnt[1 << B][1 << B][9]; 
int ans[M]; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n, m; cin >> n >> m; 
    rep(_,0,n) { 
        int x; cin >> x; 
        int l = x / (1 << B); 
        int r = x % (1 << B); 
        rep(i,0,M) ans[i] = 0; 
        rep(msk,0,1<<B) { 
            int h = __builtin_popcount(msk ^ l); 
            rep(i,0,B+1) ans[i + h] += cnt[msk][r][i]; 
        }
        
        rep(i,0,m+1) cout << ans[i] << " "; 
        cout << "\n"; 
        
        rep(msk,0,1<<B) cnt[l][msk][__builtin_popcount(msk ^ r)]++; 
    }

}
