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

const int N = 200'000 + 10; 
const int inf = 1'000'000 + 10; 
vii qat[N]; 
int a[N], ans[N]; 
int n; 
struct SegmentTree{
    vi tree; // ll si es necesario
    int n;
    SegmentTree(int n) : n(n) , tree(2 * n + 5, -inf) {} // nulo 
    void upd(int p, int v){ // ll !
        p += n; 
        for(tree[p] = v; p > 1; p>>=1) tree[p>>1] = max(tree[p],tree[p^1]); // modificar op 
    }
    int query(int l, int r){ // [l, r)
        int res = -inf; // ll !
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l & 1) res = max(res, tree[l++]); // op 
            if(r & 1) res = max(res, tree[--r]);
        }
        return res;
    }
};
SegmentTree st(N); 

// RMQ rmq(v) 
// query = [l, r) , indexa en 0  
template<class T, class F>
struct RMQ {
    F merge; 
    vector<vector<T>> jmp;
    RMQ() { }
    void rebuild(int n) { 
        jmp.clear();
        vector<T> V(1); 
        rep(i,1,n+1) V.push_back({a[i], a[i]});
        jmp.push_back(V); 
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,0,sz(jmp[k]))
                jmp[k][j] = merge(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return merge(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};



struct MinMax { 
    pii operator() (const pii& l, const pii& r) const { 
        return { min(l.first, r.first), max(l.second, r.second) } ;
    }
};
RMQ<pii,MinMax> rmq; 



int solve_small(const vi& v) {
    st.upd(0, 0); 
    for(int x : v) st.upd(x, st.query(0, x) + 1); 
    int ans = st.query(0, n + 1); 
    
    for(int x : v) st.upd(x, -inf); 
    st.upd(0,-inf); 
    return ans; 
}   



const int LIM = 10; 
int val[N]; 
void go(int l, int r) { 
    if(r - l <= LIM) return;  
    int m = l + r >> 1; 
    st.upd(n + 1, 0); 
    for(int i = m; i >= l; i--) { 
        val[i] = st.query(a[i] + 1, n + 2) + 1; 
        st.upd(a[i], val[i]); 
        if(i + 1 <= m) val[i] = max(val[i], val[i + 1]); 
    }
    for(int i = m; i >= l; i--) st.upd(a[i], -inf); 
    st.upd(n + 1, -inf); 

    st.upd(0, 0); 
    rep(i,m+1,r+1) { 
        val[i] = st.query(0, a[i]) + 1; 
        st.upd(a[i], val[i]); 
        if(i - 1 >= m + 1) val[i] = max(val[i], val[i - 1]);
        for(int x = sz(qat[i]) - 1; x >= 0; x--) { 
            auto [le, idx] = qat[i][x]; 
            if(le > m) break ;
            int a = val[le], b = val[i]; 
            if(a < b) swap(a, b); 
            if(a >= 2) { 
                ans[idx] = (a + a + b) / 2; 
            }else{  
                pii left = rmq.query(le, m + 1), right = rmq.query(m + 1, i + 1); 
                if(left.first < right.second) ans[idx] = 2; 
                else ans[idx] = 1; 
            }
            qat[i].pop_back(); 
        } 
    }
    rep(i,m+1,r+1) st.upd(a[i], -inf); 
    st.upd(0, -inf); 

    go(l, m); go(m + 1, r); 
}

void solve() {
    int qq; cin >> n >> qq; 
    rep(i,1,n+1) qat[i].clear(); 
    rep(i,1,qq+1) ans[i] = -1; 

    
    rep(i,1,n+1) cin >> a[i]; 
    rmq.rebuild(n); 
    rep(i,1,qq+1) { 
        int l, r; cin >> l >> r; 
        if(r - l <= LIM) { 
            ans[i] = solve_small(vi(a + l, a + r + 1)) ; 
            continue; 
        }
        qat[r].emplace_back(l, i); 
    }
    rep(i,1,n+1) sort(all(qat[i])), reverse(all(qat[i])); 

    go(1, n) ; 
    rep(i,1,qq+1) { 
        assert(ans[i] != -1) ; 
        cout << ans[i] << "\n"; 
    } 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
