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
    vi a(n); rep(i,0,n) cin >> a[i]; 
    vector<pair<ll,ll>> st; 
    for(int i = n - 1; i >= 0; i--) { 
        ll have = a[i], extra = 0; 
        while(sz(st) && st.back().first < have + extra) { 
            extra += st.back().first + st.back().second; 
            st.pop_back(); 
        }
        st.emplace_back(have, extra); 
    }
    cout << st[0].first + st[0].second << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
