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

const int N = 2000 + 4; 
vi adj[N]; 
int d[N], tin[N], tout[N], cnt[N][N], siz[N], timer;
vi tour; 
int n, k; 
void dfs(int u, int p = -1) { 
    tin[u] = timer++; 
    tour.push_back(u); 
    siz[u] = 1 ; 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        d[v] = d[u] + 1; 
        dfs(v, u); 
        siz[u] += siz[v]; 
    }
    tout[u] = timer; 
}

ll ans; 
ll d1[N][N], d2[N][N]; 
void dfs2(int u, int p = -1) { 
    for(int v : adj[u]) { 
        if(v == p) continue; 
        dfs2(v, u); 
        rep(i,tin[v],tout[v]) { 
            int x = tour[i], his = d[x] - d[u], need = k - 1 - his; 
            if(need >= 0) ans += d2[u][need]; 
        }
        rep(i,tin[v],tout[v]) {  
            int x = tour[i], his = d[x] - d[u]; 
            rep(i,0,n+1) { 
                if(i + his >= n) break; 
                d2[u][i + his] += d1[u][i]; 
            }
        }
        rep(i,tin[v],tout[v]) { 
            int x = tour[i], his = d[x] - d[u]; 
            d1[u][his]++; 
        }
    }
    rep(i,1,siz[u]+1) { 
        int have = i + 1, need = k - have; 
        if(need <= 0) continue; 
        ans += 1LL * (cnt[u][need] - d1[u][need]) * d1[u][i]; 
    }
    rep(two,0,siz[u]+1) { 
        int need = k - 1 - two; 
        if(need < 0) continue; 
        int total = cnt[u][need] - d1[u][need] ;
        ans += 1LL * d2[u][two] * total ; 
    }
}

void solve() {
    cin >> n >> k; 
    rep(i,0,n+1) { 
        adj[i].clear(); 
        rep(j,0,n+1) cnt[i][j] = d1[i][j] = d2[i][j] = 0; 
    } 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        u--, v--; 
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }
    queue<int> q; 
    rep(u,0,n) { 
        vi di(n, -1); 
        di[u] = 0; 
        cnt[u][di[u]] = 1; 
        q.push(u); 
        while(sz(q)) { 
            int v = q.front(); q.pop(); 
            for(int w : adj[v]) { 
                if(di[w] != -1) continue; 
                di[w] = di[v] + 1; 
                cnt[u][di[w]]++; 
                q.push(w); 
            }
        }
    }
    timer = 0; 
    tour.clear(); 
    dfs(0);
    ans = 0;    
    dfs2(0); 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
