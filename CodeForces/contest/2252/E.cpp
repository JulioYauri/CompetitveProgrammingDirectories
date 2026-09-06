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

void solve() {
    ll n; cin >> n; 
    vi digs; 
    while(n > 0) { 
        digs.push_back(n % 2); 
        n /= 2; 
    }
    reverse(all(digs)); 
    int siz = sz(digs);
    // pos , smaller , ya puse 11  
    vector<vvi> memo(siz, vvi(2, vi(2, -1))); 
    auto dp = [&](auto &&self, int pos, bool smaller, bool b11) -> int { 
        if(pos == siz) return b11; 
        int &h = memo[pos][smaller][b11]; 
        if(h != -1) return h; 
        h = 0 ; 
        if(pos + 2 <= siz) { // puedo intentar 11 o 01
            if(smaller) { 
                h = add(h, self(self, pos + 2, true, true)); // 11
                if(b11) h = add(h, self(self, pos + 2, true, true)); // 01  
            }else{ 
                // 11 
                if(digs[pos] == 1 && digs[pos + 1] == 1) { 
                    h = add(h, self(self, pos + 2, false, true)); 
                }
                // 01
                if(b11) { 
                    if(digs[pos] == 1) { // 1..
                        h = add(h, self(self, pos + 2, true, true)); 
                    }else{ // 0..
                        if(digs[pos + 1] == 1) { 
                            h = add(h, self(self, pos + 2, false, true)); 
                        }
                    }
                } 
            }
        }
        // intento con 0 
        h = add(h, self(self, pos + 1, smaller ? smaller : digs[pos] == 1, b11)); 
        return h; 
    };  
    cout << dp(dp, 0, 0, 0) << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
