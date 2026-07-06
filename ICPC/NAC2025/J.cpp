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

using Z = array<array<vl,3>,3>; 
string order = "BYR" ; 
int id(char c) { 
    rep(i,0,3) if(order[i] == c) return i; 
    return -1; 
}

void add_to(vl &my, const vl &adding) { 
    my.resize(max(sz(my), sz(adding))); 
    rep(i,1,sz(my)) { 
        if(i < sz(adding)) { 
            my[i] += adding[i] ; 
            if(my[i] >= mod) my[i] -= mod; 
        }
    }
}

Z solve(string &s, int l, int r) { 
    if(l == r) { 
        int idx = id(s[l]); 
        Z h; 
        rep(i,0,3) rep(j,i,3) h[i][j].push_back(0); 
        h[idx][idx].push_back(1); 
        return h; 
    }

    int m = l + r >> 1; 
    Z L = solve(s, l, m), R = solve(s, m + 1, r); 
    Z h; 
    rep(i,0,3) { 
        rep(j,i,3) { 
            add_to(h[i][j], L[i][j]); 
            add_to(h[i][j], R[i][j]); 
            rep(m1,i,j+1) { 
                rep(m2,m1,j+1) { 
                    add_to(h[i][j], conv(L[i][m1], R[m2][j])); 
                }
            }
        }
    }

    rep(i,0,3) rep(j,i,3) h[i][j][0] = 0; 
    return h; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    string s; cin >> s; 
    Z ans = solve(s, 0, sz(s) - 1) ;   

    vl len_cnt(sz(s) + 1) ;
    len_cnt[0] = 1; 
    rep(i,0,3) rep(j,i,3) { 
        rep(len,0,sz(s)+1) { 
            if(len >= sz(ans[i][j])) break; 
            len_cnt[len] += ans[i][j][len]; 
            if(len_cnt[len] >= mod) len_cnt[len] -= mod; 
        }
    }

    vl probs(sz(s) + 1), del_prob(sz(s) + 1); 
    int cur_den = sz(s);    
    del_prob[0] = 1; 
    rep(i,1,sz(s) + 1) { 
        del_prob[i] = del_prob[i - 1]; 
        del_prob[i] *= modpow(cur_den, mod - 2); 
        del_prob[i] %= mod;
        del_prob[i] = del_prob[i] * i % mod;   
        cur_den --; 
    }

    rep(i,0,sz(s) + 1) { 
        int del = sz(s) - i ; 
        probs[i] = len_cnt[i] * del_prob[del] % mod; 
    }
    probs[0] = 1; 
    rep(i,0,sz(s)) probs[i] = (probs[i] - probs[i + 1] + mod) % mod; 
    ll exp = 0; 
    rep(i,0,sz(s)+1) { 
        int del = sz(s) - i; 
        exp += probs[i] * del % mod; 
        exp %= mod; 
    }
    cout << exp << "\n"; 
}
