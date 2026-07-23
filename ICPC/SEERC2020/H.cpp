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
struct NodeOr { 
    int cnt, val;
    NodeOr(int cnt = 0, int val = 0) : cnt(cnt), val(val) { }
    NodeOr operator + (const NodeOr& rhs) const  {
        return NodeOr(cnt + rhs.cnt, val | rhs.val); 
    }
};

struct NodeAnd { 
    int cnt, val;
    NodeAnd(int cnt = 0, int val = (1 << 30) - 1) : cnt(cnt), val(val) { }
    NodeAnd operator + (const NodeAnd& rhs) const  {
        return NodeAnd(cnt + rhs.cnt, val & rhs.val); 
    }
};

template<class T> 
struct SegmentTree{
    vector<T> tree; // ll si es necesario
    int n;
    SegmentTree(int n) : n(n) , tree(2 * n + 5) {} // nulo 
    void upd(int p, T v){ // ll !
        p += n; 
        for(tree[p] = v; p > 1; p>>=1) tree[p>>1] = (tree[p] + tree[p^1]); // modificar op 
    }
    T query(int l, int r){ // [l, r)
        T res; // ll !
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l & 1) res = (res + tree[l++]); // op 
            if(r & 1) res = (res + tree[--r]);
        }
        return res;
    }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n, qq; 
    cin >> n >> qq; 

    vi a(n); 
    rep(i,0,n) cin >> a[i]; 
    
    map<int, vi> poss; 
    rep(i,0,n) poss[a[i]].push_back(i); 

    const int LIM = 31; 
    vector<SegmentTree<NodeOr>> st_or(LIM, SegmentTree<NodeOr>(n)); 
    vector<SegmentTree<NodeAnd>> st_and(LIM, SegmentTree<NodeAnd>(n)); 
    rep(i,0,n) { 
        int x = a[i], bit_cnt = __builtin_popcount(x); 
        st_or[bit_cnt].upd(i, NodeOr(1, x)); 
        st_and[bit_cnt].upd(i, NodeAnd(1, x)); 
    }

    vi query_and(LIM), query_or(LIM); 
    vi total_and(LIM), total_or(LIM); 
    while(qq--) { 
        int l, r; 
        cin >> l >> r; 
        l--, r--; 

        rep(i,0,LIM) { 
            auto node_and = st_and[i].query(l, r + 1);
            tie(query_and[i], total_and[i]) = tie(node_and.val, node_and.cnt); 
            auto node_or = st_or[i].query(l, r + 1); 
            tie(query_or[i], total_or[i]) = tie(node_or.val, node_or.cnt); 
        }

        // or en prefijo, and en sufijo
        rep(i,1,LIM) { 
            query_or[i] |= query_or[i - 1]; 
            total_or[i] += total_or[i - 1]; 
        }

        for(int i = LIM - 1; i; i--) { 
            query_and[i - 1] &= query_and[i]; 
            total_and[i - 1] += total_and[i]; 
        }

        bool ok = false; 
        rep(i,0,LIM) { 
            if(i && query_and[i] == query_or[i - 1] && total_or[i - 1] > 0 && total_and[i] > 0) { 
                ok = true; 
                break; 
            }   
            if(query_and[i] == query_or[i]) { 
                int x = query_and[i]; 
                if(!poss.count(x)) continue ;
                auto &pos = poss[x]; 
                int x_cnt = upper_bound(all(pos), r) - lower_bound(all(pos), l); 
                if(x_cnt > 1) { 
                    ok = true; 
                    break; 
                }
            }
        }

        cout << (ok ? "YES\n" : "NO\n") ; 

    }

}
