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
    int n; cin >> n; 
    vi py(n + 2), cnt(n + 2); 
    vvi at(n + 2); 
    rep(i,0,n) { 
        int x, y; cin >> x >> y; 
        py[y] = 1; cnt[y]++; 
        at[x].push_back(y); 
    } 
    rep(i,1,sz(py)) py[i] += py[i - 1]; 
    
    int l_min = 2 * n, l_max = -2 * n, r_min = -1, r_max = -1, r_total = n; 
    rep(i,0,n+2) if(cnt[i]) { 
        if(r_min == -1) r_min = i; 
        r_max = i; 
    }
    
    ll ans = 0; 
    rep(x,0,n+2) if(sz(at[x])) { 
        for(int y : at[x]) { 
            l_min = min(l_min, y); 
            l_max = max(l_max, y); 
            cnt[y]--; 
            r_total--; 
        }
        if(r_total == 0) break; 
        while(cnt[r_min] == 0) r_min++; 
        while(cnt[r_max] == 0) r_max--;
        int cur_min = max(l_min, r_min), cur_max = min(l_max, r_max) ;
        if(cur_max > cur_min) ans += py[cur_max - 1] - py[cur_min - 1]; 
    }
    cout << ans << "\n"; 
}   

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int tt; cin >> tt; 
    while(tt--) solve(); 

}
