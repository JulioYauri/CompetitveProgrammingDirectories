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
    int n, m; cin >> n >> m; 
    vii v(n + m); 
    rep(i,0,n) { 
        cin >> v[i].first; 
        v[i].second = 1; 
    }
    rep(i,n,m+n) { 
        cin >> v[i].first; 
        v[i].second = -1; 
    }

    int ops = n - m; 
    if(ops < m) { 
        cout << "NO\n"; return; 
    }

    sort(all(v)) ; 
    rep(_,0,2) { 
        int total = 0; 
        for(auto [f, s] : v) { 
            total += s; 
            if(total < 0) { 
                cout << "NO\n"; return; 
            }
        }
        reverse(all(v)); 
    }   
    cout << "YES\n"; 

}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
