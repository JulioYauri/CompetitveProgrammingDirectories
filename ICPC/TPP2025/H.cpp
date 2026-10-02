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

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

ull pollard(ull n) {
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	auto f = [&](ull x) { return modmul(x, x, n) + i; };
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}

using B = __int128_t; 
const int mod = 998244353; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(ll a, ll b) { return a * b % mod; }
int bp(int a, ll e) { 
    int ans = 1; 
    while(e) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1; 
    }
    return ans; 
}

int solve2(B exp, ll n) { 
    int ans = 0; 
    if(exp - 2 >= 0) { 
        B t = exp - 1; 
        int todo = bp((exp + 1) % mod, n); 
        int a = bp((exp - 1) % mod, n); 
        int b = sub(bp(exp % mod, n), a); 
        int total = sub(todo, add(a, add(b, b))); 
        ans = add(ans, mul(t % mod, total)); 
    }   
    int todo = bp((exp + 1) % mod, n); 
    int without = bp(exp % mod, n); 
    int total = sub(todo, without); 
    ans = add(ans, total); 
    ans = add(ans, total); 
    return ans; 
}

void solve() { 
    ll h, n, x; cin >> h >> n >> x; 
    if(h == 1) { 
        cout << "1\n"; return; 
    }
    if(n == 1) { 
        cout << "0\n"; return; 
    }
    auto fs = factor(h); 
    sort(all(fs)); 
    fs.erase(unique(all(fs)), fs.end());
    int ans = 1; 
    for(auto p : fs) { 
        int exp = 0; 
        while(h % p == 0) exp++, h /= p; 
        ans = mul(ans, solve2(B(exp) * x, n - 1));
    }
    cout << ans << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int tt; cin >> tt; 
    while(tt--) solve(); 

}
