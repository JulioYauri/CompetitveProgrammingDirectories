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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum) { 
				pos += pw, sum -= s[pos-1];
            }
		}
		return pos;
	}
    ll q(int l, int r) { 
        return query(r + 1) - query(l) ; 
    }
    void rupd(int l, int r, ll x) { 
        if(l > r) return; 
        update(l, x); 
        update(r + 1, -x); 
    }
};

const ll inf = 1LL << 60; 
struct SegTree { 
    // hallar primera posicion con 
    struct node { 
        ll mx; // greater - smaller 
        ll mx_active; 
        bool cnt ; // active cnt 
        node() { 
            mx = 0; 
            cnt = 0;
            mx_active = -inf;  
        }
    };
    node merge(const node &l, const node &r) const { 
        node res; 
        res.cnt = (l.cnt || r.cnt); 
        res.mx = max(l.mx, r.mx); 
        res.mx_active = max(l.mx_active, r.mx_active); 
        return res; 
    }
    vector<node> t; 
    vl lz; 
    int n; 
    SegTree(int n) : n(n) { 
        t.resize(4 * n + 5); 
        lz.resize(4 * n + 5); 
    }
    void push(int v) { 
        if(lz[v] == 0) return; 
        lz[v * 2] += lz[v]; 
        lz[v * 2 + 1] += lz[v]; 
        t[v * 2].mx += lz[v]; 
        t[v * 2 + 1].mx += lz[v] ; 
        if(t[v * 2].mx_active != -inf) t[v * 2].mx_active += lz[v]; 
        if(t[v * 2 + 1].mx_active != -inf) t[v * 2 + 1].mx_active += lz[v]; 
        lz[v] = 0; 
    }
    void point_update_active(int v, int tl, int tr, int pos, bool active) { 
        if(tl == tr) { 
            t[v].cnt = active; 
            if(t[v].cnt) t[v].mx_active = t[v].mx; 
            else t[v].mx_active = -inf; 
            return; 
        }
        int tm = tl + tr >> 1; 
        push(v); 
        if(pos <= tm) point_update_active(v * 2, tl, tm, pos, active); 
        else point_update_active(v * 2 + 1, tm + 1, tr, pos, active); 
        t[v] = merge(t[v * 2], t[v * 2 + 1]); 
    }
    void range_update(int v, int tl, int tr, int l, int r, ll x) { 
        if(l > r) return ;
        if(tl == l && r == tr) { 
            t[v].mx += x; 
            if(t[v].mx_active != -inf) t[v].mx_active += x; 
            lz[v] += x; 
            return; 
        }
        push(v); 
        int tm = tl + tr >> 1; 
        range_update(v * 2, tl, tm, l, min(r, tm), x); 
        range_update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x); 
        t[v] = merge(t[v * 2], t[v * 2 + 1]); 
    }
    ll point_query(int v, int tl, int tr, int pos) { 
        if(tl == tr) return t[v].mx; 
        push(v); 
        int tm = tl + tr >> 1; 
        if(pos <= tm) return point_query(v * 2, tl, tm, pos); 
        else return point_query(v * 2 + 1, tm + 1, tr, pos); 
    }
    // hallar primera posicion activa con t[v] = goal 
    int kth(int v, int tl, int tr, ll goal) {
        if(t[v].mx_active < goal) return -1;  
        if(tl == tr) return tl; 
        int tm = tl + tr >> 1; 
        push(v); 
        int right = kth(v * 2 + 1, tm + 1, tr, goal) ; 
        if(right != -1) return right; 
        return kth(v * 2, tl, tm, goal); 
    }
    void act(int pos, bool active) { return point_update_active(1, 0, n - 1, pos, active); }
    void rupd(int l, int r, ll x) { return range_update(1, 0, n - 1, l, r, x); }
    ll q(int pos) { return point_query(1, 0, n - 1, pos); }
    int kth(ll goal) { return kth(1, 0, n - 1, goal); }
};

void solve() {
    int n; cin >> n; 
    vector<pair<char, ll>> v(n); 
    rep(i,0,n) cin >> v[i].first >> v[i].second; 
    
    vl pref(n);
    FT ft(n + 1) ;  
    vector<bool> exists(n + 1) ; 
    rep(i,0,n) { 
        if(v[i].first == 'p') { 
            int val = v[i].second; 
            pref[i] = ft.q(val, n); 
            ft.update(val, 1); 
            exists[val] = true; 
        }
    }

    rep(i,1,n) pref[i] += pref[i - 1]; 

    FT active(n + 1); 
    SegTree st(n + 1); 
    rep(i,1,n+1) if(!exists[i]) {
        active.update(i, 1); 
        st.act(i, 1); 
        st.rupd(0, i - 1, 1);  
    }
     
    int last_s = -1; 
    vi ans(n); 
    rep(i,0,n) { 
        if(v[i].first == 'p') ans[i] = v[i].second; 
        else last_s = i; 
    }
    rep(i,0,last_s) { 
        if(v[i].first == 'p') { 
            int pval = v[i].second; 
            st.rupd(0, pval - 1, 1); 
        }
    }

    for(int i = last_s, next_s; i >= 0; i = next_s) { 
        next_s = i - 1; 
        while(next_s >= 0 && v[next_s].first == 'p') next_s--; 
        
        ll have = (next_s >= 0 ? v[next_s].second : 0); 
        if(i - 1 >= 0) { 
            have += pref[i - 1] - (next_s == -1 ? 0 : pref[next_s]) ; 
        }
        ll sum = 0; 
        rep(j,next_s+1,i) { 
            int pval = v[j].second; 
            st.rupd(pval + 1, n, -1); 
            sum += active.q(pval + 1, n) ; 
        }

        int idx = st.kth(v[i].second - have - sum); 
        assert(st.q(idx) == v[i].second - have - sum) ; 
        ans[i] = idx; 
        st.act(idx, 0); 
        st.rupd(0, idx - 1, -1); 
        active.update(idx, -1); 

        for(int j = next_s + 1; j < i; j++) { 
            int pval = v[j].second;     
            st.rupd(0, pval - 1, -1); 
            st.rupd(pval + 1, n, 1); 
        }
    }
    for(int i : ans) cout << i << " "; cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
