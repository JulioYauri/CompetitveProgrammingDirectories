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

typedef uint64_t ull;
static int C; // initialized below

// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() const { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return (ull)*this == (ull)o; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
typedef A<1000000007, unsigned> H;

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}


const int mod = 1'000'000'000 + 7; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(ll a, ll b) { return a * b % mod; }

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    timeval tp;
	mingw_gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);

    int n; cin >> n; 
    vector<string> v(n); 
    rep(i,0,n) cin >> v[i]; 
    sort(all(v), [&](auto &l, auto &r) { 
        return sz(l) < sz(r) ; 
    });

    vi dp(n); 
    vector<bool> fin(n, true); 
    vector<HashInterval> vh; 
    rep(i,0,n) vh.emplace_back(v[i]); 

    vector<H> hashes(n); 
    rep(i,0,n) hashes[i] = hashString(v[i]); 

    vi sizes(n); 
    rep(i,0,n) sizes[i] = sz(v[i]); 
    sort(all(sizes)); 
    sizes.erase(unique(all(sizes)), sizes.end()); 

    vector<vector<vector<H>>> hs(n); 
    rep(i,0,n) { 
        int pos = 0; 
        for(int siz : sizes) { 
            hs[i].push_back({}); 
            if(siz == sz(v[i])) break; 
            rep(j,0,sz(v[i])) { 
                int r = j + siz; 
                if(r > sz(v[i])) break; 
                hs[i][pos].push_back(vh[i].hashInterval(j, r));  
            }
            sort(all(hs[i][pos])); 
            pos++; 
        }
    }

    rep(i,0,n) { 
        int my = sz(v[i]); 
        dp[i] = 1; 
        int pos = 0; 
        rep(j,0,i) { 
            int his = sz(v[j]);
            if(j > 0 && sz(v[j]) != sz(v[j - 1])) pos++;  
            if(his == my) break; 
            auto ptr = lower_bound(all(hs[i][pos]), hashes[j]); 
            if(ptr != hs[i][pos].end() && *ptr == hashes[j]) { 
                fin[j] = false; 
                dp[i] = add(dp[i], dp[j]); 
            }
        }
    }

    int ans = 0; 
    rep(i,0,n) { 
        if(fin[i]) { 
            ans = add(ans, dp[i]); 
        }
    }
    cout << ans << "\n"; 
}
