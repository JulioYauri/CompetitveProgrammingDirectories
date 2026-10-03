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

bool is_p(int n) { 
    if(n == 1) return false; 
    if(n == 2) return true; 
    for(int i = 2; i * i <= n; i++) { 
        if(n % i == 0) return false; 
    }
    return true;  
}

const int N = 1'000'000 + 10; 
vi primes; 
bool cr[N]; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    rep(i,0,N) cr[i] = 1; 
    cr[0] = cr[1] = 0; 
    rep(i,2,N) { 
        if(cr[i]) { 
            primes.push_back(i); 
            for(int j = 2 * i; j < N; j += i) cr[j] = 0; 
        }
    }

    vi ps; 
    rep(i,3,7000) { 
        if(is_p(i)) { 
            int sum = 0, cur = i; 
            while(cur > 0) sum += cur % 10, cur /= 10; 
            if(is_p(sum)) { 
                ps.push_back(i); 
            }
        }
    }

    ll n; cin >> n; 
    int ans = 0; 
    for(int q : ps) { 
        int exp = q - 1; 
        for(int p : primes) { 
            __int128_t cur = 1; 
            int i = 0; 
            while(i < exp && cur <= n) { 
                cur *= p; 
                i++; 
            }
            if(i == exp && cur <= n) ans++; 
            else break; 
        }
    }
    cout << ans << "\n"; 
}   
