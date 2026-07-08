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

const int N = 100 + 5; 
int a[N], p[N], res[N]; 
int n, b, k, x; 

int bp2(int a, ll exp, int m) { 
    int ans = 1; 
    while(exp) { 
        if(exp & 1) ans = 1LL * ans * a % m; 
        a = 1LL * a * a % m; 
        exp >>= 1; 
    }
    return ans;
}

void pp(ll step) { 
    rep(i,0,x) res[i] = 0; 
    int p10 = bp2(10, step, x);
    rep(i,0,x) { 
        rep(j,0,x) { 
            int pos = (i * p10 + j) % x; 
            res[pos] = add(res[pos], mul(p[i], p[j])); 
        }
    }
    rep(i,0,x) p[i] = res[i]; 
}

void pa(ll step) { 
    rep(i,0,x) res[i] = 0; 
    int p10 = bp2(10, step, x); 
    rep(i,0,x) { 
        rep(j,0,x) { 
            int pos = (i * p10 + j) % x; 
            res[pos] = add(res[pos], mul(a[i], p[j])); 
        }
    }
    rep(i,0,x) a[i] = res[i]; 
}


void bp(int exp) { 
    a[0] = 1; 
    ll step = 1; 
    while(exp > 0) { 
        if(exp & 1) pa(step); 
        pp(step); 
        step *= 2; 
        exp >>= 1; 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cin >> n >> b >> k >> x; 
    rep(i,0,n) { 
        int num; cin >> num; 
        p[num % x] ++; 
    }
    bp(b); 
    cout << a[k] << "\n"; 
}
