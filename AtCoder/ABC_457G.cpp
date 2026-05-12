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
    vii pts(n); rep(i,0,n) cin >> pts[i].first >> pts[i].second; 

    sort(all(pts), [&](auto &lhs, auto &rhs) { 
        if(lhs.first + lhs.second == rhs.first + rhs.second) 
            return lhs.first - lhs.second < rhs.first - rhs.second; 
        return lhs.first + lhs.second < rhs.first + rhs.second; 
    });

    vi v(n); rep(i,0,n) v[i] = - pts[i].second + pts[i].first; 

    int inf = 1 << 20; 
    vi dp(n + 3, -inf) ; dp[0] = inf;   
    for(auto x : v) { 
        int lo = -1, hi = sz(dp); 
        while(hi - lo > 1) { 
            int mi = lo + hi >> 1; 
            if(dp[mi] >= x) lo = mi; 
            else hi = mi; 
        }
        if(dp[hi - 1] > x && x > dp[hi]) dp[hi] = x; 
    }
    rep(i,0,sz(dp)) if(dp[i] == -inf) { 
        cout << i - 1 << "\n"; 
        return 0; 
    }
}
