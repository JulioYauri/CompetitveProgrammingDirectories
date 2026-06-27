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

int siz_inv; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
void FST(vi& a, bool inv) {
	for (int n = sz(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
			int &u = a[j], &v = a[j + step]; tie(u, v) =
				// inv ? pii(v - u, u) : pii(v, u + v); // AND
				// inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
				pii(add(u, v), sub(u, v));                   // XOR /// include-line
		}
	}
	if (inv) for (int& x : a) x = 1LL * x * siz_inv % mod; // XOR only /// include-line
}
vi conv(vi a, vi b) {
	FST(a, 0); FST(b, 0);
	rep(i,0,sz(a)) a[i] = 1LL * a[i] * b[i] % mod;
	FST(a, 1); return a;
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m; cin >> n >> m; 
    vi a(n); rep(i,0,n) cin >> a[i]; 

    vi cnt(1 << m); 
    rep(i,0,n) cnt[a[i]]++; 
    
    vi diff_counts = cnt; 
    sort(all(diff_counts)); 
    diff_counts.erase(unique(all(diff_counts)), diff_counts.end()); 
    
    const int lim = 20;
    int last = 0;
    vl ans(1 << m); 
    vi poly(1 << m); 
    siz_inv = modpow(1 << m, mod - 2); 
    rep(i,0,lim) { 
        if(i >= sz(diff_counts)) break; 
        int cur_min = diff_counts[i], val = cur_min - last; 
        rep(j,0,1<<m) poly[j] = (cnt[j] >= cur_min); 
        vi to_add = conv(poly, poly); 
        rep(j,0,1<<m) ans[j] = add(1LL * to_add[j] * val % mod, ans[j]); 
        last = cur_min; 
    }

    int inv2 = modpow(2, mod - 2); 
    rep(i,0,1<<m) ans[i] = ans[i] * inv2 % mod; 
    if(lim < sz(diff_counts)) {
        vi remaining; 
        int val = diff_counts[lim], last_done = diff_counts[lim - 1]; 
        rep(i,0,1<<m) { 
            if(cnt[i] >= val) { 
                remaining.push_back(i); 
            }
        }

        rep(i,0,sz(remaining)) { 
            rep(j,i+1,sz(remaining)) { 
                int a = remaining[i], b = remaining[j]; 
                ans[a ^ b] = add(ans[a ^ b], sub(min(cnt[a], cnt[b]), last_done)); 
            }
        }

    }

    ans[0] = 0; 
    rep(i,0,1<<m) ans[0] = add(ans[0], cnt[i] / 2); 
    
    int ten = 1, final_ans = 0;  
    rep(i,0,1<<m) { 
        final_ans = add(final_ans, 1LL * ans[i] * ten % mod); 
        ten = 1LL * ten * 10 % mod; 
    }
    cout << final_ans << "\n"; 
}
