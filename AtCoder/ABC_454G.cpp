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

const int N = 2'500'000 + 10; 
const int mod = 998244353; 
int p[N], q[N], d[N], c[N], moda[N], moda_cnt[N], cnt[N], siz[N], tin[N], tout[N]; 
vi adj[N]; 
int timer = 0, cur_moda = 0, cur_cnt = 0; 
vi tour; 

void dfs1(int u, int p) { 
    siz[u] = 1;
    tin[u] = timer++;  
    tour.push_back(u); 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        dfs1(v, u); 
        siz[u] += siz[v]; 
    }
    tout[u] = timer; 
}

void add(int color) { 
    cnt[color]++; 
    if(cnt[color] > cur_moda) { 
        cur_moda = cnt[color]; 
        cur_cnt = 1;  
    }else if(cnt[color] == cur_moda) { 
        cur_cnt++; 
    }
}

void dfs(int u, int p, bool keep) { 
    int mx = -1, big_child = -1; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        if(siz[v] > mx) mx = siz[v], big_child = v; 
    }
    
    for(int v : adj[u]) { 
        if(v == p || v == big_child) continue; 
        dfs(v, u, 0); 
    }

    if(big_child != -1) dfs(big_child, u, 1); 

    add(c[u]); 
    for(int v : adj[u]) { 
        if(v != p && v != big_child) { 
            rep(i,tin[v],tout[v]) add(c[tour[i]]); 
        }
    }

    moda[u] = cur_moda; 
    moda_cnt[u] = cur_cnt; 

    if(keep == 0) { 
        rep(i,tin[u],tout[u]) cnt[c[tour[i]]]--; 
        cur_moda = cur_cnt = 0; 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    ll seed; 
    int n, m, f; 
    cin >> n >> seed >> m >> f; 
    rep(i,2,m+1) cin >> q[i];
    rep(i,1,m+1) cin >> d[i]; 

    ll state = seed; 
    rep(i,2,n+1) { 
        if(i <= m) p[i] = q[i]; 
        else { 
            p[i] = (state % (i - 1)) + 1; 
            state = (state * 1103515245 + 12345) % (1LL << 31); 
        }
    }

    rep(i,1,n+1) { 
        if(i <= m) c[i] = d[i]; 
        else { 
            c[i] = state % f + 1; 
            state = (state * 1103515245 + 12345) % (1LL << 31); 
        }
    }
    
    rep(i,2,n+1) { 
        adj[i].push_back(p[i]); 
        adj[p[i]].push_back(i); 
    }

    dfs1(1,-1); 
    dfs(1,-1,1); 
    ll ans = 0; 
    rep(i,1,n+1) { 
        ans += 1LL * (moda[i] ^ i) * (moda_cnt[i] ^ i) ; 
        ans %= mod; 
    }


    cout << ans << "\n"; 
}
