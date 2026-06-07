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

struct P{ 
    int x, y, i; 
    P(int x, int y, int i) : x(x), y(y), i(i) { }
};

void solve() {
	int n; cin >> n; 
    vector<P> pts; 
    rep(i,1,n+1) { 
        int x, y; cin >> x >> y; 
        pts.emplace_back(x, y, i); 
    }
    sort(all(pts), [](P &lhs, P &rhs) { return lhs.x < rhs.x; }); 
    vector<P> pos, neg;
    vector<tuple<int,int,int> > ans;  
    for(auto p : pts) { 
        while(sz(pos) && pos.back().y > p.y) { 
            if(sz(pos) >= 2) ans.emplace_back(p.i, pos.back().i, pos.end()[-2].i); 
            pos.pop_back();  
        }
        while(sz(neg) && neg.back().y < p.y) { 
            if(sz(neg) >= 2) ans.emplace_back(p.i, neg.back().i, neg.end()[-2].i); 
            neg.pop_back(); 
        }
        pos.push_back(p); 
        neg.push_back(p); 
    }
    cout << sz(ans) << "\n"; 
    for(auto [i, j, k] : ans) cout << i << " " << j << " " << k << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
