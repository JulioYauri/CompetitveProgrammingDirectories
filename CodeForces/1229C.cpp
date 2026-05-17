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

const int N = 100000 + 5; 
vi adj[N], in[N]; 

ll calc(int u) { 
    int out = sz(adj[u]) - sz(in[u]); 
    return 1LL * out * sz(in[u]); 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m; cin >> n >> m; 
    rep(i,0,m) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        in[min(u, v)].push_back(max(u, v)); 
    }
    ll total = 0; 
    rep(i,1,n+1) total += calc(i); 
    cout << total << "\n" ;
    int qq; cin >> qq; 
    while(qq--) { 
        int u; cin >> u; 
        total -= calc(u); 
        for(int v : in[u]) { 
            total -= calc(v); 
            in[v].push_back(u);
            total += calc(v);  
        }
        in[u].clear(); 
        total += calc(u); 
        cout << total << "\n" ; 
    }
}
