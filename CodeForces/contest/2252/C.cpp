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
    vl v(n); rep(i,0,n) cin >> v[i]; 
    vector<vl> g(n, vl(m)); 
    rep(i,0,n) rep(j,0,m) cin >> g[i][j]; 

    int ans = m;
    vl cur(m, 0); 
    for(int i = n - 1; i >= 0; i--) { 
        sort(all(g[i])); 
        for(ll x : g[i]) cur.push_back(x); 
        inplace_merge(cur.begin(), cur.begin() + m, cur.end()); 
        rotate(cur.begin(), cur.begin() + m, cur.end()); 
        while(sz(cur) > m) cur.pop_back(); 
        ll have = 0; 
        for(int j = m - 1, cnt = 1; j >= 0; j--, cnt++) { 
            have += cur[j]; 
            if(have >= v[i]) { 
                ans = min(ans, cnt); 
                break ;
            }
        }
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
