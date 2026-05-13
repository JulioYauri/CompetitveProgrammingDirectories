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

const int mod = 998244353; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(ll a, ll b) { return a * b % mod; }
int bp(int a, int e) { 
	int ans = 1; 
	while(e) { 
		if(e & 1) ans = mul(ans, a); 
		a = mul(a, a); 
		e >>= 1; 
	}
	return ans; 
}


struct ST { 
	struct Z { 
		int s0, s1, s2;
		Z() : s0(0), s1(0), s2(0) { } 
		Z operator+(const Z& rhs) { 
			Z res; 
			res.s0 = add(s0, rhs.s0); 
			res.s1 = add(s1, rhs.s1); 
			res.s2 = add(s2, rhs.s2); 
			return res; 
		}
	};
	Z nil; 
	Z app(const Z& to, int val) { 
		Z res; 
		res.s0 = to.s0; 
		res.s1 = add(to.s1, mul(to.s0, val)); 
		res.s2 = add(to.s2, mul(2, mul(val, to.s1))); 
		res.s2 = add(res.s2, mul(mul(val, val), to.s0));
		return res; 
	}

	vector<Z> t; 
	vi lazy; 
	int n; 
	ST(int n) : n(n), t(n * 4 + 5), lazy(n * 4 + 5) {
		build(1, 1, n); 
	}
	void build(int v, int tl, int tr) { 
		if(tl == tr) { 
			t[v].s0 = 1; 
			return; 
		}
		int tm = tl + tr >> 1; 
		build(v * 2, tl, tm); 
		build(v * 2 + 1, tm + 1, tr); 
		t[v] = t[v * 2] + t[v * 2 + 1]; 
	}
	void push(int v) { 
		t[v * 2] = app(t[v * 2], lazy[v]); 
		t[v * 2 + 1] = app(t[v * 2 + 1], lazy[v]) ; 
		lazy[v * 2] = add(lazy[v * 2], lazy[v]); 
		lazy[v * 2 + 1] = add(lazy[v * 2 + 1], lazy[v]); 
		lazy[v] = 0;
	}
	void upd(int v, int tl, int tr, int l, int r, int val) { 
		if(l > r) return; 
		if(l == tl && r == tr) { 
			t[v] = app(t[v], val); 
			lazy[v] = add(lazy[v], val); 
			return; 
		}
		int tm = tl + tr >> 1; 
		push(v); 
		upd(v * 2, tl, tm, l, min(r, tm), val); 
		upd(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, val); 
		t[v] = t[v * 2] + t[v * 2 + 1]; 
	}
	Z query(int v, int tl, int tr, int l, int r) { 
		if(l > r) return nil; 
		if(l == tl && r == tr) return t[v]; 
		push(v); 
		int tm = tl + tr >> 1; 
		return query(v * 2, tl, tm, l, min(r, tm)) + 
				query(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r); 
	}
	void upd(int l, int r, int val) { upd(1, 1, n, l, r, val); }
	Z query(int l, int r) { return query(1, 1, n, l, r); }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n, qq; cin >> n >> qq; 
	
	ST st(n); 
	int i2 = bp(2, mod - 2); 
	while(qq--) { 
		int l, r, a; cin >> l >> r >> a; 
		a %= mod; 
		st.upd(l, r, a); 
		auto [s0, s1, s2] = st.query(l, r) ; 
		int ans = sub(mul(s1, s1), s2); 
		cout << mul(ans, i2) << "\n"; 
	}
}
