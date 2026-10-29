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
    int lo = -1, hi = n + 1; 
    vi cur(n); 
    while(hi - lo > 1) { 
        int mi = lo + hi >> 1; 
        fill(all(cur), 0); 
        for(int now = mi, l = 0; now > 0 && l < n; now--) { 
            int q = mi / now ; 
            while(q-- && l < n) { 
                cur[l] = now; 
                l++; 
            }
        }
        ll total = accumulate(all(cur), 0LL); 
        if(total >= n) hi = mi; 
        else lo = mi; 
    }
    cout << hi << "\n"; 
    fill(all(cur), 0) ; 
    for(int now = hi, l = 0; now > 0 && l < n; now--) { 
        int q = hi / now ; 
        while(q-- && l < n) { 
            cur[l] = now; 
            l++; 
        }
    }
    ll extra = accumulate(all(cur), 0LL) - n ; 
    for(int i = n - 1; i >= 0 && extra > 0; i--) { 
        ll take = min(extra, 1LL * cur[i]) ; 
        cur[i] -= take; 
        extra -= take; 
    }
    int idx = 1; 
    for(int i : cur) { 
        int x = i; 
        while(x--) { 
            cout << idx << " " ; 
        }
        idx++; 
    }
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
