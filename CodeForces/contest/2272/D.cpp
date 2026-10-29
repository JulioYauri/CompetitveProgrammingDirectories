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

pii vs(vvi &adj) { 
    int n = sz(adj); 
    int lv = -1; 
    rep(i,0,n) { 
        if(sz(adj[i]) == 1) { 
            return {adj[i][0], 0} ;  
        }
    }
    return {0, 1}; 
}

void solve() {
    int k; cin >> k; 
    vii v(k); 
    rep(i,0,k) { 
        int n; cin >> n; 
        vvi adj(n); 
        rep(_,1,n) { 
            int u, v; cin >> u >> v; 
            u--; v--; 
            adj[u].push_back(v); 
            adj[v].push_back(u); 
        }
        v[i] = vs(adj); 
    }

    int r = 0; 
    rep(i,0,k) { 
        if(v[i].second == 0) { 
            r = i; 
            break; 
        }
    }
    rep(i,0,k) {
        if(r == i) continue; 
        cout << r + 1 << " " << v[r].first + 1 << " " << i + 1 << " " << v[i].first + 1 << "\n"; 
    }

}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}