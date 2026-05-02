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

const int mod = 1'000'000'000 + 7; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(ll a, ll b) { return a * b % mod; }

const int N = 200000 + 4; 
int p2[N]; 

struct FT {
    vi s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] = add(s[pos], dif);
	}
	int query(int pos) { // sum of values in [0, pos)
		int res = 0;
		for (; pos > 0; pos &= pos - 1) res = add(res, s[pos - 1]);
		return res;
	}
    int rq(int l, int r) { 
        return sub(query(r + 1), query(l)); 
    }
};


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    p2[0] = 1; 
    rep(i,1,N) p2[i] = p2[i - 1] * 2LL % mod; 

    int n; cin >> n; 
    int ans = 0; 
    FT dp(N + 1), seq(N + 1); 
    rep(i,0,n) { 
        int x; cin >> x; 
        // dp[i] = sum(dp[j < i]) + sum(seq[j < i]) 
        int a = add(dp.query(x), seq.query(x)); 
        int here = add(a, add(1, seq.rq(x, N))); 
        dp.update(x, here); 
        seq.update(x, p2[i]); 

        int rem = n - i - 1; 
        ans = add(ans, mul(here, p2[rem])); 
        
    }
    cout << ans << "\n"; 


    // int n; cin >> n; 
    // vi v(n); 
    // rep(i,0,n) cin >> v[i]; 
    // int ans = 0; 
    // rep(mask,1,1<<n) { 
    //     vi h; 
    //     rep(i,0,n) if((mask >> i) & 1) h.push_back(v[i]); 
    //     for(int l = 0, r = 0; l < sz(h); l = r) { 
    //         while(l == r || (r < sz(h) && h[r - 1] < h[r])) r++; 
    //         int len = r - l; 
    //         ans += len * (len + 1) / 2; 
    //     }
    // }
    // cout << ans << "\n"; 
}
