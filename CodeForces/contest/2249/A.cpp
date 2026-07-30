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
    vi l(n + 1), r(n + 1), u(n + 1), v(n + 1); 
    rep(i,1,n+1) cin >> l[i] >> r[i] >> u[i] >> v[i]; 

    auto inside = [&](int i, int left, int right) { 
        return i >= left && i <= right; 
    };
    for(int siz = n; siz > 0; siz--) { 
        int lo = 1, hi = n, total = 0, lo_pos = 1, hi_pos = siz; 
        while(lo <= hi) { 
            while(lo <= n && (inside(lo_pos, l[lo], r[lo]) || inside(siz - lo_pos + 1, u[lo], v[lo]))) lo++; 
            while(hi >= 1 && (inside(hi_pos, l[hi], r[hi]) || inside(siz - hi_pos + 1, u[hi], v[hi]))) hi--; 
            if(lo > n || hi < 0 || lo > hi) break; 
            if(lo != hi) total += 2; 
            else total ++; 
            if(total >= siz) { 
                cout << siz << "\n"; return; 
            }
            lo_pos++; 
            hi_pos--; 
            lo++; 
            hi--;   
        }
    }
    cout << 0 << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
