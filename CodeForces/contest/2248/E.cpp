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
    int n, m, d; cin >> n >> m >> d; 
    vl p(m), r(m); 
    rep(i,0,m) cin >> p[i] >> r[i]; 
    rep(i,0,m*2) { 
        ll np = p[i] + n; 
        p.push_back(np); 
        r.push_back(r[i]); 
    }

    // cerr << "p, r: \n"; 
    // rep(i,0,sz(r)) { 
    //     cerr << p[i] << " " << r[i] << "\n"; 
    // }

    rep(i,1,sz(r)) r[i] += r[i - 1]; 
    rep(i,0,m) { 
        ll sum = r[i] + p[i] * d; 
        ll len_need = p[i] + 1; 
        rep(j,0,m+1) { 
            ll from = (j == 0 ? 0 : p[j - 1]) + 1; 
            int lo = -1, hi = sz(p); 
            while(hi - lo > 1) { 
                int mi = (lo + hi) / 2; 
                if(p[mi] <= from + len_need - 1) lo = mi; 
                else hi = mi; 
            }
            assert(lo != -1) ; 
            ll cur_sum = r[lo] - (j == 0 ? 0 : r[j - 1]);
            if(cur_sum + len_need * d < sum) { 
                cout << "YES\n"; return; 
            }
        }
    }
    cout << "NO\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
