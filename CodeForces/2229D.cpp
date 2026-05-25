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
    vi a(n), b(n); 
    rep(i,0,n) cin >> a[i]; 
    rep(i,0,n) cin >> b[i]; 
    rep(i,0,n) if(a[i] > b[i]) swap(a[i], b[i]); 

    int lo = 1, hi = 2 * n + 1; 
    while(hi - lo > 1) { 
        int mi = lo + hi >> 1; 
        vi st; 
        rep(i,0,n) { 
            if(a[i] < mi && b[i] >= mi) continue; 
            int val = (a[i] >= mi) ; 
            if(val) st.push_back(val); 
            else if(st.empty() || st.back() == 1) st.push_back(val); 
        }
        int c1 = count(all(st), 1), c0 = sz(st) - c1; 
        if(c1 > c0) lo = mi ; 
        else hi = mi; 
    }
    cout << lo << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
