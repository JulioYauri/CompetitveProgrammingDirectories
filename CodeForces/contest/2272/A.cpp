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
    int k; cin >> k; 
    vi v(n); rep(i,0,n) cin >> v[i]; 
    vector<bool> inside(n); 
    rep(i,0,n-k+1) { 
        inside[v[i]] = true; 
    }

    rep(i,0,n-k+1) { 
        if(!inside[i]) { 
            int my_pos = -1; 
            rep(j,0,n) { 
                if(v[j] == i) { 
                    my_pos = j; 
                    break; 
                }
            }
            cout << my_pos + 1 << " " << max_element(v.begin(), v.begin() + n - k + 1) - v.begin() + 1 << "\n"; 
            return; 
        }
    }
    cout << "-1\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
