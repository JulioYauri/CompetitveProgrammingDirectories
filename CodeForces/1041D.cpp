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

    int n; cin >> n; 
    ll h; cin >> h; 
    vii segs(n); rep(i,0,n) cin >> segs[i].first >> segs[i].second; 

    vl extra(n), cost(n); 
    rep(i,0,n) { 
        extra[i] = segs[i].second - segs[i].first; 
        cost[i] = (i - 1 < 0 ? 0 : segs[i].first - segs[i - 1].second); 
    }

    rep(i,1,n) extra[i] += extra[i - 1], cost[i] += cost[i - 1]; 
    ll ans = 0; 
    rep(i,0,n) { 
        int lo = -1, hi = n; 
        while(hi - lo > 1) { 
            int mi = lo + hi >> 1; 
            ll total_cost = cost[mi] - cost[i]; 
            if(total_cost < h) lo = mi ; 
            else hi = mi;  
        }
        
        // cerr << "i: " << i << "  here: " << h + extra[lo] - (i == 0 ? 0 : extra[i - 1]) << "\n"; 
        ans = max(ans, h + extra[lo] - (i == 0 ? 0 : extra[i - 1])); 
    }
    cout << ans << "\n"; 
}
