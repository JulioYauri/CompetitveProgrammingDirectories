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

const int N = 500'000 + 10; 
const int mod = 1'000'000'000 + 7; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int mul(ll a, ll b) { return a * b % mod ; }
int bp(int a, int e) { 
    int ans = 1; 
    while(e) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1 ; 
    }
    return ans; 
}

int f[N], fi[N]; 
int C(int n, int k) { 
    if(n < 0 || n < k) return 0; 
    return mul(f[n], mul(fi[k], fi[n - k])); 
}

void solve() {
    int n; cin >> n; 
    vector<pair<ll,int>> vals(n); 
    vl val(n + 2); 
    rep(i,0,n) { 
        cin >> vals[i].first; 
        val[i + 1] = vals[i].first; 
        vals[i].second = i + 1; 
    }

    vi L(n + 2, -1), R(n + 2, -1); 
    rep(i,1,sz(L)) L[i] = i - 1; 
    rep(i,0,sz(R) - 1) R[i] = i + 1; 
    L[0] = R.back() = -1; 
    int vis = 0; 
    vector<bool> done(n + 2, false); done[0] = done.back() = true; 
    auto rem = [&](int i) { 
        vis++; 
        L[R[i]] = L[i]; 
        R[L[i]] = R[i]; 
    };  
    auto calc = [&](int i) { return 1LL * (i - L[i]) * (R[i] - i); };

    queue<int> q; 
    rep(i,1,n+1) { 
        if(calc(i) == val[i] && val[i] == 1 && !done[i]) { 
            done[i] = true; 
            q.push(i); 
        }
    } 
    vi to_L(n + 2, -1), to_R(n + 2, -1), last_L(n + 2, -1), last_R(n + 2, -1);  
    while(sz(q)) { 
        int u = q.front(); q.pop(); 
        rem(u); 
        if(L[u] != -1 && !done[L[u]] && to_R[L[u]] != u) { 
            if(calc(L[u]) == val[L[u]]) { 
                to_R[L[u]] = u; 
                to_L[L[u]] = last_L[L[u]]; 
                q.push(L[u]); 
                done[L[u]] = true; 
            }else{ 
                last_R[L[u]] = u; 
            }
        }   
        if(R[u] != -1 && !done[R[u]] && to_L[R[u]] != u) { 
            if(calc(R[u]) == val[R[u]]) { 
                to_L[R[u]] = u; 
                to_R[R[u]] = last_R[R[u]]; 
                q.push(R[u]); 
                done[R[u]] = true; 
            }else{ 
                last_L[R[u]] = u; 
            }
        }
    }
    
    
    int root = -1, rcnt = 0; 
    rep(i,1,n+1) { 
        if(1LL * i * (n + 1 - i) == val[i]) { 
            root = i; 
            rcnt++; 
        }
    }
    
    if(vis != n || rcnt != 1 || accumulate(all(val), 0LL) != 1LL * n * (n + 1) / 2) { 
        cout << "0\n"; return; 
    }

    set<int> pos = {0, n + 1}; 
    auto dfs = [&](auto &&self, int u) -> int { 
        auto ptr = pos.insert(u).first; 
        int L = *prev(ptr), R = *next(ptr); 
        int have = C(R - L - 2, u - L - 1); 
        if(to_L[u] != -1) have = mul(have, self(self, to_L[u])); 
        if(to_R[u] != -1) have = mul(have, self(self, to_R[u])); 
        return have; 
    };
    cout << dfs(dfs, root) << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    f[0] = 1; 
    rep(i,1,N) f[i] = mul(i, f[i - 1]); 
    fi[N - 1] = bp(f[N - 1], mod - 2); 
    for(int i = N - 1; i; i--) fi[i - 1] = mul(fi[i], i); 

	int tt; cin >> tt; 
	while(tt--) solve();
}
