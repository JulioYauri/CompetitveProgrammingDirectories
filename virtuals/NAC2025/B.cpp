#include<bits/stdc++.h>
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define ll long long
using namespace std;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

const int mod = 998244353; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int mul(ll a, ll b) { return a * b % mod; }
int bp(int a, int e) { 
    int ans = 1; 
    while(e) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1; 
    }
    return ans; 
}
int inv(int a) { return bp(a, mod - 2); }


const int N = 200000 + 10 ; 
int dp[N][2]; 
vi adj[N]; 
void dfs(int u, int p = -1) { 
    if(sz(adj[u]) == 1 && u != 1) { 
        dp[u][0] = 2; 
        dp[u][1] = 1; 
        return ;
    }
    vii ch; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        dfs(v, u); 
        ch.emplace_back(dp[v][0], dp[v][1]); 
    }
    vi pref(sz(ch)), suf(sz(ch)); 
    rep(i,0,sz(ch)) pref[i] = suf[i] = ch[i].first; 
    rep(i,1,sz(ch)) pref[i] = mul(pref[i], pref[i - 1]); 
    for(int i = sz(ch) - 1; i; i--) suf[i - 1] = mul(suf[i - 1], suf[i]); 

    int total = 0; 
    rep(i,0,sz(ch)) { 
        int h = mul(i - 1 >= 0 ? pref[i - 1] : 1, i + 1 < sz(ch) ? suf[i + 1] : 1); 
        total = add(total, mul(h, ch[i].second)); 
    }
    dp[u][1] = total ; 
    dp[u][0] = add(dp[u][1], pref.back()); 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n; 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    dfs(1); 
    int ans = 1; 
    for(int u : adj[1]) ans = mul(ans, dp[u][0]); 
    cout << ans << "\n"; 
}