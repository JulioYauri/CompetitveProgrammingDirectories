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

using Z = array<int,3>;  
const int N = 200000 + 5; 
vi adj[N]; 
int up[N], total[N], ans[N]; 
Z dp[N];
int n; 

Z recalc(Z cur, int new_val) { 
    if(new_val > cur[0]) cur[0] = new_val; 
    sort(all(cur)); 
    return cur; 
}

void dfs(int u, int p, int limit) { 
    dp[u] = {0,0,0}; 
    for(int v : adj[u]) { 
        if(v > limit || v == p) continue; 
        dfs(v, u, limit); 
        dp[u] = recalc(dp[u], dp[v][1]); 
    }
    for(int &x : dp[u]) x++; 
}

int get_pos(Z &arr, int val) { 
    rep(i,0,3) if(arr[i] == val) return i; 
    return -1; 
}

void dfs2(int u, int p, int limit) {
    Z tmp = recalc(dp[u], up[u]); 
    total[u] = tmp[1]; 
    for(int v : adj[u]) { 
        if(v > limit || v == p) continue; 
        int his_val = dp[v][1] + 1, pos = get_pos(dp[u], his_val); 
        if(pos != -1) { 
            tmp = dp[u]; 
            tmp[pos] = up[u]; 
            sort(all(tmp)); 
            up[v] = tmp[1] + 1; 
        }else{ 
            tmp = recalc(dp[u], up[u]); 
            up[v] = tmp[1] + 1; 
        }
        dfs2(v, u, limit); 
    }   
}

int solve(int limit) { 
    dfs(1,-1,limit); 
    dfs2(1,-1,limit); 
    return *max_element(total + 1, total + limit + 1) ; 
}

void go(int l, int r, int l_val, int r_val) { 
    if(l + 1 >= r) return; 
    if(l_val == r_val) { 
        rep(i,l,r+1) ans[i] = ans[l]; 
        return; 
    }   
    int m = l + r >> 1;
    ans[m] = solve(m); 
    go(l, m, l_val, ans[m]); 
    go(m, r, ans[m], r_val); 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cin >> n; n++; 
    rep(i,2,n+1) { 
        int u; cin >> u ; 
        adj[u].emplace_back(i); 
        adj[i].emplace_back(u); 
    } 

    memset(ans,-1,sizeof(ans)); 
    ans[1] = 1; 
    ans[n] = solve(n); 
    go(1, n, 1, ans[n]);     
    rep(i,2,n+1) cout << ans[i] << " "; cout << "\n"; 
}
