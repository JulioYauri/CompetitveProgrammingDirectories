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

// query = max [l, r)
// update = asignar en punto 
// indexa desde 0 
// 2 * n de memoria 
pii merge(pii a, pii b) { 
    if(a.first < b.first) return a; 
    else return b; 
}

const int inf = 2'000'000'000; 
struct SegmentTree{
    vii tree; // ll si es necesario
    int n;
    SegmentTree(int n) : n(n) , tree(2 * n + 5, pii(inf, inf)) {} // nulo 
    void upd(int p, pii v){ // ll !
        p += n; 
        for(tree[p] = v; p > 1; p>>=1) tree[p>>1] = merge(tree[p],tree[p^1]); // modificar op 
    }
    pii query(int l, int r){ // [l, r)
        pii res = {inf, inf}; // ll !
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l & 1) res = merge(res, tree[l++]); // op 
            if(r & 1) res = merge(res, tree[--r]);
        }
        return res;
    }
};

void solve() {
    int n; cin >> n; 
    vi val(n); rep(i,0,n) cin >> val[i]; 
    vvi adj(n); 
    rep(i,1,n) { 
        int p; cin >> p; 
        p--; 
        adj[p].push_back(i); 
    }

    vi tour(n), tin(n), tout(n); 
    int timer = 0;
    SegmentTree st(n);  
    auto dfs = [&](auto &&self, int u) -> void { 
        tin[u] = timer;  
        st.upd(timer, pii(val[u], tin[u])); 
        tour[timer++] = u;
        for(auto v : adj[u]) self(self, v); 
        tout[u] = timer; 
    };  
    dfs(dfs, 0); 
    ll total = 0; 
    auto dfs2 = [&](auto &&self, int u) -> void {
        if(sz(adj[u]) == 0) { 
            st.upd(tin[u], pii(val[u], tin[u])) ; 
            total += val[u]; 
            return; 
        } 
        for(int v : adj[u]) self(self, v); 
        auto [mn, who] = st.query(tin[u], tout[u]) ;
        st.upd(tin[u], pii(inf, tin[u]));  
        if(val[u] > mn) { 
            total -= mn; 
            total += val[u]; 
            st.upd(who, pii(inf, who)); 
            st.upd(tin[u], pii(val[u], tin[u])); 
        }
    };
    dfs2(dfs2,0); 
    int lvs = 0; 
    rep(i,1,n) lvs += sz(adj[i]) == 0; 
    
    vi other; 
    rep(i,0,n) { 
        auto [x, who] = st.query(tin[i], tin[i] + 1); 
        if(x == inf) other.push_back(val[tour[who]]); 
    }
    
    sort(all(other)); 
    reverse(all(other)); 
    vl ans(n, -1);
    ans[lvs - 1] = total; 
    int j = 0; 
    rep(i,lvs,n) ans[i] = ans[i - 1] + other[j++]; 
    
    for(auto i : ans) cout << i << " "; cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
