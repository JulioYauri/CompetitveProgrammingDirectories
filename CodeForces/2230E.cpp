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

const ll inf = 1'000'000'000 ; 
struct SegmentTree{
    vl tree; 
    int n;
    SegmentTree(int n) : n(n) , tree(2 * n + 5, 0) {}  
    void upd(int p, ll v){ 
        p += n; 
        for(tree[p] += v; p > 1; p>>=1) tree[p>>1] = min(tree[p],tree[p^1]);  
    }
    ll query(int l, int r){ // [l, r)
        ll res = inf; // ll !
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l & 1) res = min(res, tree[l++]); // op 
            if(r & 1) res = min(res, tree[--r]);
        }
        return res;
    }
    void dbg() { 
        rep(i,0,n) { 
            ll val = query(i, i + 1); 
            if(val >= inf) cerr << "inf " ; 
            else cerr << val << " "; 
        }
        cerr << "\n"; 
    }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    vii ps(n); 
    rep(i,0,n) cin >> ps[i].first; 
    rep(i,0,n) cin >> ps[i].second; 
    int qq; cin >> qq; 
    vii Ls(qq), Ms(qq); 
    vvi vals(3, vi(qq)); 
    rep(i,0,3) rep(j,0,qq) cin >> vals[i][j]; 
    rep(j,0,qq) { 
        Ls[j].first = vals[1][j];  
        Ms[j].first = vals[1][j] + vals[2][j]; 
        Ls[j].second = Ms[j].second = j; 
    }

    sort(all(ps)); 
    vii cs(n); rep(i,0,n) cs[i].first = ps[i].second, cs[i].second = i; 
    sort(all(cs)); 
    vl ans(qq, inf); 
    auto get_pos = [&](int x) { 
        return upper_bound(all(ps), make_pair(x, -1)) - ps.begin(); 
    };
    { // Ls 
        SegmentTree stval(n), st(n); 
        rep(i,0,n) { 
            st.upd(i, inf); 
            stval.upd(i, inf + ps[i].first); 
        } 
        sort(all(Ls)); 
        int now = 0; 
        for(auto [pos, idx] : Ls) { 
            while(now < n && cs[now].first < pos) { 
                st.upd(cs[now].second, -inf);
                stval.upd(cs[now].second, -inf);  
                now++; 
            }
            int l_end = vals[0][idx], m_end = vals[0][idx] + vals[2][idx];
            int l_pos = get_pos(l_end), m_pos = get_pos(m_end); 
            auto here = min({st.query(0,l_pos), stval.query(l_pos, m_pos),
                        st.query(m_pos, n) + m_end});
            ans[idx] = min(ans[idx], here); 
        }

    }
    { // Ms 
        SegmentTree st(n), stval(n); 
        rep(i,0,n) { 
            st.upd(i, inf); 
            stval.upd(i, ps[i].first + inf); 
        } 
        sort(all(Ms)); 
        int now = 0; 
        for(auto [pos, idx] : Ms) { 
            while(now < n && cs[now].first < pos) { 
                st.upd(cs[now].second, -inf + cs[now].first);
                stval.upd(cs[now].second, -inf + cs[now].first);  
                now++; 
            }
            int l_end = vals[0][idx], m_end = vals[0][idx] + vals[2][idx];
            int l_pos = get_pos(l_end), m_pos = get_pos(m_end); 
            ans[idx] = min({ans[idx], st.query(0,l_pos), stval.query(l_pos, m_pos),
                        st.query(m_pos, n) + m_end}); 
        }
    }
    { // Rs
        SegmentTree st(n), stval(n); 
        rep(i,0,n) { 
            st.upd(i, inf); 
            stval.upd(i, ps[i].first + inf); 
        } 
        reverse(all(Ms)); 
        int now = n - 1; 
        for(auto [pos, idx] : Ms) { 
            while(now >= 0 && cs[now].first >= pos) { 
                st.upd(cs[now].second, -inf); 
                stval.upd(cs[now].second, -inf); 
                now--; 
            }
            int l_end = vals[0][idx], m_end = vals[0][idx] + vals[2][idx];
            int l_pos = get_pos(l_end), m_pos = get_pos(m_end); 
            ans[idx] = min({ans[idx], st.query(0,l_pos) + pos, stval.query(l_pos, m_pos) + pos,
                        st.query(m_pos, n) + m_end + pos}); 
        }
    }
    for(auto i : ans) cout << i << "\n"; 
}
