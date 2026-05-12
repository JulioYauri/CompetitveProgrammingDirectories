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

const ll inf = 1LL << 60; 
struct Z { 
    ll a[2][2];
    bool nil;  
    Z() { rep(i,0,2) rep(j,0,2) a[i][j] = inf; nil = true; }
    Z(ll x) { 
        rep(i,0,2) rep(j,0,2) a[i][j] = inf; 
        a[1][1] = x; 
        a[0][0] = 0; 
        nil = false; 
    }
    Z operator+(const Z& rhs) const { 
        Z res; auto &h = res.a; 
        res.nil = rhs.nil && this -> nil; 
        if(res.nil) return res; 
        if(rhs.nil) res = *this;
        else if(this -> nil) res = rhs; 
        else { 
            rep(l,0,2) rep(r,0,2) { 
                h[l][r] = min(h[l][r], this -> a[l][0] + rhs.a[1][r]); 
                h[l][r] = min(h[l][r], this -> a[l][1] + min(rhs.a[1][r], rhs.a[0][r]));
            }
        } 
        return res; 
    }
    void p() { 
        rep(i,0,2) rep(j,0,2) cerr << a[i][j] << " " ; cerr << "\n"; 
    }
};  
Z NIL ;

struct ST { 
    int n; 
    vector<Z> t; 
    ST(int n) : n(n), t(n * 4 + 5) { }
    void upd(int v, int tl, int tr, int pos, int val) { 
        if(tl == tr) { 
            t[v] = Z(val); return; 
        }
        int tm = tl + tr >> 1; 
        if(pos <= tm) upd(v * 2, tl, tm, pos, val); 
        else upd(v * 2 + 1, tm + 1, tr, pos, val); 
        t[v] = t[v * 2] + t[v * 2 + 1]; 
    }
    Z query(int v, int tl, int tr, int l, int r) {
        if(l > r)  return NIL ;
        if(tl == l && tr == r) return t[v]; 
        int tm = tl + tr >> 1; 
        return query(v * 2, tl, tm, l, min(r, tm)) 
                + query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r); 
    }
};

void solve() { 
    int n, k; cin >> n >> k; 
    ST st(n); 
    rep(i,0,n) { 
        int x; cin >> x; 
        st.upd(1, 0, n - 1, i, x); 
    }
    ll ans = inf; 
    rep(i,k-1,n) { 
        { 
            auto q = st.query(1, 0, n - 1, i - k + 1, i) ; 
            ans = min(ans, q.a[1][1]); 
        }
        if(i >= k) { 
            auto q = st.query(1, 0, n - 1, i - k, i); 
            ans = min(ans, q.a[1][1]); 
        }
    }
    cout << ans << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    // rep(i,0,2) rep(j,0,2) nil.a[i][j] = 0; 

    int tt; cin >> tt; 
    while(tt--) solve(); 
}
