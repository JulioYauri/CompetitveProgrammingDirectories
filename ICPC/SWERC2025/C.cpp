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
    vvi g(n, vi(m)); 
    rep(i,0,n) rep(j,0,m) cin >> g[i][j]; 

    if(n % 2 == 0) { 
        sort(all(g)); 
        g.erase(unique(all(g)), g.end()); 
        for(auto &v : g) { 
            for(int i : v) cout << i << " "; 
        }
        cout << "\n"; 
        return ; 
    }

    vvi vecs; 
    rep(i,0,n) { 
        vecs.emplace_back(g[i].begin(), g[i].begin() + m / 2); 
        vecs.emplace_back(g[i].begin() + m / 2, g[i].end()); 
    }

    sort(all(vecs)); 
    vecs.erase(unique(all(vecs)), vecs.end()); 

    auto get_coord = [&](auto &v) { 
        return lower_bound(all(vecs), v) - vecs.begin(); 
    };

    int siz = sz(vecs); 
    vi L(siz);  
    rep(i,0,n) { 
        vector vl(g[i].begin(), g[i].begin() + m / 2); 
        vector vr(g[i].begin() + m / 2, g[i].end()) ; 
        auto cl = get_coord(vl); 
        auto cr = get_coord(vr); 
        L[cr] = cl; 
    }

    int cur = 0; 
    vi cyc; 
    do { 
        cur = L[cur]; 
        cyc.push_back(cur); 
    }while(cur != 0) ;   
    reverse(all(cyc)); 
    for(auto c : cyc) { 
        auto &v = vecs[c]; 
        for(int i : v) cout << i << " "; 
    }
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
