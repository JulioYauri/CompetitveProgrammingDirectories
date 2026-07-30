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

struct SegmentTree{
    int n;
    vi t, lz; 
    SegmentTree(int n) : n(n) { 
        t.assign(4 * n + 5, 0); 
        lz.assign(4 * n + 5, 0); 
    }

    void push(int v) { 
        if(!lz[v]) return; 
        t[v * 2] += lz[v]; 
        t[v * 2 + 1] += lz[v]; 
        lz[v * 2] += lz[v]; 
        lz[v * 2 + 1] += lz[v]; 
        lz[v] = 0; 
    }

    void upd(int v, int tl, int tr, int l, int r, int add) { 
        if(l > r) return ; 
        if(tl == l && r == tr) { 
            t[v] += add; 
            lz[v] += add; 
            return; 
        }
        int tm = tl + tr >> 1; 
        push(v); 
        upd(v * 2, tl, tm, l, min(r, tm), add); 
        upd(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, add); 
        t[v] = max(t[v * 2], t[v * 2 + 1]); 
    }
    int qry(int v, int tl, int tr, int l, int r) { 
        if(l > r) return 0;
        if(tl == l && r == tr) return t[v]; 
        int tm = tl + tr >> 1; 
        push(v); 
        return max(qry(v * 2, tl, tm, l, min(r, tm)), 
                qry(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)); 
    }
    void upd(int l, int r, int x) { upd(1, 1, n, l, r, x); }
    int qry(int l, int r) { return qry(1, 1, n, l, r) ; }
};

void solve() {
    int n; cin >> n; 
    vi p(n + 1); 
    rep(i,1,n+1) cin >> p[i];   
    rep(i,1,n+1) p.push_back(p[i]); 
    vvi to(sz(p)); 
    vi pos(n + 1); 
    for(int i = sz(p) - 1; i; i--) { 
        int x = p[i]; 
        if(x + 1 <= n && pos[x + 1]) to[i].push_back(pos[x + 1]); 
        if(x - 1 >= 1 && pos[x - 1]) to[i].push_back(pos[x - 1]); 
        pos[x] = i; 
    }
    SegmentTree st(sz(p) + 1); 
    for(int i = sz(p) - 1; i > n; i--) { 
        st.upd(i, 2 * n, 1); 
        for(int u : to[i]) st.upd(u, 2 * n, -1); 
    }
    int ans = 0; 
    for(int i = n; i; i--) { 
        st.upd(i, 2 * n, 1); 
        for(int u : to[i]) st.upd(u, 2 * n, -1); 
        if(st.qry(i, i + n - 1) <= 2) ans++; 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
