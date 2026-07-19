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

struct st { 
    int n; 
    struct node { 
        int mn, mx, cost, siz; 
        node(int x=0) : mn(x), mx(x), cost(0), siz(1) { }
        node operator+(const node& rhs) const { 
            node res; 
            res.mx = max(mx, rhs.mx); 
            res.mn = min(mn, rhs.mn); 
            res.siz = siz + rhs.siz; 
            if(rhs.mn < mx) res.cost = res.siz / 2; 
            res.cost = max({res.cost, cost, rhs.cost}) ; 
            return res; 
        }
    } ;
    vector<node> t; 
    st(int n, vi &vals) : n(n) { 
        t.resize(n * 2); 
        rep(i,n,sz(t)) t[i] = node(vals[i - n]); 
        for(int i = n - 1; i > 0; i--) t[i] = t[i * 2] + t[i * 2 + 1]; 
    }
    void upd(int pos, int val) { 
        pos += n ; 
        t[pos] = node(val); 
        pos /= 2; 
        while(pos > 0) t[pos] = t[pos * 2] + t[pos * 2 + 1], pos /= 2; 
    }
};  

const int inf = 1'000'000'010; 
void solve() {
    int n, qq; cin >> n >> qq; 
    vi v(n); rep(i,0,n) cin >> v[i]; 
    while( (n & (n - 1)) != 0 ) { 
        v.push_back(inf); 
        n++; 
    }
    
    st tree(n, v); 
    cout << tree.t[1].cost << "\n"; 
    while(qq--) { 
        int i, x; cin >> i >> x; 
        tree.upd(i,x) ; 
        cout << tree.t[1].cost << "\n"; 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
	int tt; cin >> tt; 
	while(tt--) solve();
}
