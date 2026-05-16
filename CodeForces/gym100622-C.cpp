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
    
    freopen("circles.in", "r", stdin); 
    freopen("circles.out", "w", stdout); 
    
    int w, h, n; cin >> w >> h >> n; 
    vector<vii> v(h); 
    rep(_,0,n) { 
        int x, y, rad; cin >> x >> y >> rad; 
        int first_h = max(y - rad, 0), last_h = min(h - 1, y + rad); 
        rep(cur_y,first_h,last_h+1) { 
            int l = -1, r = -1; 
            { 
                int lo = -1, hi = x; 
                while(hi - lo > 1) { 
                    int mi = lo + hi >> 1; 
                    int dx = mi - x, dy = y - cur_y; 
                    if(1LL * dx * dx + 1LL * dy * dy > 1LL * rad * rad) lo = mi ; 
                    else hi = mi ;  
                }
                l = hi; 
            }
            { 
                int lo = x, hi = w; 
                while(hi - lo > 1) { 
                    int mi = lo + hi >> 1; 
                    int dx = mi - x, dy = y - cur_y; 
                    if(1LL * dx * dx + 1LL * dy * dy > 1LL * rad * rad) hi = mi ; 
                    else lo = mi ;  
                }
                r = lo; 
            }
            v[cur_y].emplace_back(l, r); 
        } 
    }

    ll total = 0; 
    for(auto &vals : v) { 
        vii evs; 
        for(auto &[l, r] : vals) { 
            evs.emplace_back(l, 1); 
            evs.emplace_back(r + 1, -1); 
        }
        int last_x = 0, alive = 0; 
        sort(all(evs)); 
        for(int l = 0, r = 0; l < sz(evs); l = r) { 
            while(l == r || (r < sz(evs) && evs[r - 1].first == evs[r].first)) r++; 
            int cur_x = evs[l].first; 
            if(alive) total += (cur_x - last_x); 
            last_x = cur_x; 
            rep(i,l,r) alive += evs[i].second; 
        }
    }
    cout << 1LL * w * h - total << "\n"; 
}
