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
    vi p(n); rep(i,0,n) cin >> p[i], p[i]--; 

    vi id; 
    rep(i,0,n) { 
        if(i != p[i]) id.push_back(i); 
    }

    for(int l = 0, r = sz(id) - 1; l < r; l++, r--) swap(p[id[l]], p[id[r]]); 
    cout << (is_sorted(all(p)) ? "YES\n" : "NO\n"); 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
