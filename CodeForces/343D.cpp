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

const int N = 500'000 + 3; 
struct SegmentTree1 { // asigna en rango 
    vi t; vector<bool> mark; 
    int n; 
    SegmentTree1(int n) : n(n) { 
        t.assign(n * 4 + 5, -1); 
        mark.assign(n * 4 + 5, false); 
    }
    void push(int v) { 
        if(!mark[v]) return; 
        mark[v * 2] = mark[v * 2 + 1] = true; 
        t[v * 2] = t[v * 2 + 1] = t[v]; 
        mark[v] = false; 
    }
    void upd(int v, int tl, int tr, int l, int r, int b) { 
        if(l > r) return ; 
        if(tl == l && r == tr) { 
            t[v] = b; 
            mark[v] = true; 
            return; 
        }
        int tm = tl + tr >> 1; 
        push(v); 
        upd(v * 2, tl, tm, l, min(r, tm), b); 
        upd(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, b); 
    }
    int query(int v, int tl, int tr, int pos) { 
        if(tl == tr) return t[v]; 
        push(v); 
        int tm = tl + tr >> 1; 
        if(pos <= tm) return query(v * 2, tl, tm, pos); 
        else return query(v * 2 + 1, tm + 1, tr, pos); 
    }
};

struct SegmentTree{
    vi tree; // ll si es necesario
    int n;
    SegmentTree(int n) : n(n) , tree(2 * n + 5, 0) {} // nulo 
    void upd(int p, int v){ // ll !
        p += n; 
        for(tree[p] = v; p > 1; p>>=1) tree[p>>1] = max(tree[p],tree[p^1]); // modificar op 
    }
    int query(int l, int r){ // [l, r)
        int res = 0; // ll !
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l & 1) res = max(res, tree[l++]); // op 
            if(r & 1) res = max(res, tree[--r]);
        }
        return res;
    }
};

vi adj[N]; 
int tin[N], tout[N], timer = 0; 
void dfs(int u, int p = -1) { 
    tin[u] = timer++; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        dfs(v, u) ; 
    }
    tout[u] = timer; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        u--, v--; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    dfs(0); 
    int qq; cin >> qq; 
    SegmentTree1 fills(n);
    SegmentTree emps(n);  
    rep(q,1,qq+1) { 
        int tp, u; cin >> tp >> u; 
        u--; 
        if(tp == 1) fills.upd(1,0,n-1,tin[u],tout[u]-1,q); 
        else if(tp == 2) emps.upd(tin[u], q); 
        else { 
            int last_filled = fills.query(1, 0, n - 1, tin[u]); 
            int last_emptied = emps.query(tin[u], tout[u]); 
            cout << (last_filled > last_emptied) << "\n"; 
        }
    }

}
