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
int sub(int a, int b) { return a < b ? a - b + mod : a - b ; }
int mul(ll a, ll b) { return a * b % mod; }

const int N = 8000 + 10; 
int n, m; 
int calls[N][N], b[N], memo[N]; 
vi adj[N]; 

int dp(int a, int src) { 
    if(a == src) return 1; 
    int &h = memo[a]; 
    if(h != -1) return h; 
    h = 0; 
    for(int v : adj[a]) h = add(h, dp(v, src)); 
    return h; 
}

int dp2(int a) { 
    int &h = memo[a]; 
    if(h != -1) return h; 
    h = b[a]; 
    for(int v : adj[a]) h = add(h, dp2(v)); 
    return h ;
}

void calc(int src) { 
    memset(memo, -1, sizeof(memo)); 
    rep(i,1,n+1) calls[i][src] = dp(i, src); 
}

const int B = 90; 
int batch_val[N], val[N]; 

void build() { 
    rep(i,1,n+1) { 
        val[i] = 0; 
        rep(j,1,n+1) { 
            val[i] = add(val[i], mul(calls[i][j], b[j])); 
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    cin >> n; 
    rep(i,1,n+1) cin >> b[i]; 

    cin >> m; 
    rep(i,0,m) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
    }

    rep(i,1,n+1) calc(i); 

    vi updates, qans;
    qans.reserve(1'000'000 + 10); 
    memset(batch_val, -1, sizeof(batch_val));  
    build(); 
    int qq; cin >> qq; 
    while(qq--) { 
        char c; cin >> c; 
        if(c == 'Q') { 
            int u; cin >> u; 
            int ans = val[u]; 
            for(auto x : updates) { 
                int diff = sub(batch_val[x], b[x]); 
                ans = add(ans, mul(diff, calls[u][x])); 
            }
            qans.push_back(ans); 
        }else{ 
            int i, v; cin >> i >> v; 
            if(batch_val[i] != -1) { 
                batch_val[i] = v; 
            }else{ 
                batch_val[i] = v; 
                updates.push_back(i); 
            }
            if(sz(updates) == B) { 
                for(int x : updates) { 
                    b[x] = batch_val[x]; 
                    batch_val[x] = -1; 
                }
                updates.clear(); 
                memset(memo, -1, sizeof(memo)); 
                rep(i,1,n+1) val[i] = dp2(i); 
            }
        }
    }
    int ans = 0; 
    rep(i,0,sz(qans)) { 
        ans = add(ans, mul(i + 1, qans[i])); 
    }
    cout << ans << "\n"; 
}
