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

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
ll modpow(ll a, ll exp) { 
    ll ans = 1; 
    while(exp > 0) { 
        if(exp & 1) ans = ans * a % mod; 
        a = a * a % mod; 
        exp >>= 1; 
    }
    return ans; 
}

// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modpow(root, mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
	    n = 1 << B;
	int inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

const int N = 200000 + 10; 
int mul(ll a, ll b) { return a * b % mod; }
int fi[N], f[N]; 
int C(int n, int k) { 
    if(n < 0 || k < 0 || k > n) return 0; 
    return mul(f[n], mul(fi[n - k], fi[k]));
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    f[0] = 1; 
    rep(i,1,N) f[i] = mul(i, f[i - 1]); 
    fi[N - 1] = modpow(f[N - 1], mod - 2); 
    for(int i = N - 1; i; i--) fi[i - 1] = mul(fi[i], i); 

    int n; cin >> n; 
    map<int,int> cnt_a, cnt_b; 
    rep(i,0,n) { 
        int x; cin >> x; 
        cnt_a[x]++; 
    }
    rep(i,0,n) { 
        int x; cin >> x; 
        cnt_b[x]++; 
    }

    priority_queue<pii, vii, greater<pii>> pq; 
    vector<vl> polys; 
    for(auto [x, cnt] : cnt_b) { 
        int id = sz(polys), total_a = cnt_a[x]; 
        vl poly(1, 1); 
        rep(choose,1,cnt+1) { 
            int x1 = C(cnt, choose), x2 = C(total_a, choose), m = mul(x1, x2); 
            poly.push_back(mul(m, f[choose])); 
        }
        polys.push_back(poly); 
        pq.emplace(sz(poly), id); 
    }   

    while(sz(pq) >= 2) { 
        auto [siz1, id1] = pq.top(); pq.pop(); 
        auto [siz2, id2] = pq.top(); pq.pop(); 
        vl new_poly = conv(polys[id1], polys[id2]); 
        polys[id1] = new_poly; 
        pq.emplace(sz(new_poly), id1); 
    }

    auto &res = polys[pq.top().second]; 
    int total = 0; 
    rep(i,1,sz(res)) { 
        res[i] = mul(res[i], f[n - i]); 
        if(i % 2) total += res[i]; 
        else total -= res[i]; 
        while(total >= mod) total -= mod; 
        while(total < 0) total += mod; 
    } 
    total = f[n] - total;
    while(total >= mod) total -= mod; 
    while(total < 0) total += mod;  
    cout << mul(total, fi[n]) << "\n"; 
}
