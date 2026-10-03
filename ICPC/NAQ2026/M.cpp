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

const int N = 100'000 + 10; 
bool cyc[N], vis[N]; 
int val[N], par[N]; 
vii adj[N]; 
int c_beg = -1, c_end = -1; 

void dfs(int u, int p) { 
    vis[u] = true; 
    for(auto [v, id] : adj[u]) { 
        if(v == p ) continue; 
        if(vis[v]) { 
            c_end = v; 
            c_beg = u; 
            return; 
        }
        par[v] = u; 
        dfs(v, u); 
    }
}

map<int,int> cnt2; 
void dfs2(int u, int p) {
    cnt2[val[u]]++;  
    for(auto [v, id] : adj[u]) { 
        if(v == p || cyc[id]) continue; 
        dfs2(v, u); 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, k; cin >> n >> k; 
    rep(i,1,n+1) cin >> val[i]; 
    rep(i,0,n) { 
        int u, v; cin >> u >> v; 
        adj[u].emplace_back(v, i); 
        adj[v].emplace_back(u, i); 
    }
    
    dfs(1,-1); 
    vi cycle; 
    for(int u = c_end; u != c_beg; u = par[u]) { 
        cycle.push_back(u); 
    } 
    cycle.push_back(c_beg) ;
    rep(i,0,sz(cycle)) { 
        int u = cycle[i]; 
        int v = cycle[(i + 1) % sz(cycle)]; 
        for(auto [w, idx] : adj[u]) { 
            if(w == v) { 
                cyc[idx] = true; 
            }
        }
    }

    ll ans = (k == 0 ? n : 0); 
    map<int,int> cnt; 
    rep(i,1,n+1) cnt[val[i]]++; 
    for(auto [f, s] : cnt) { 
        int other = f - k; 
        if(k == 0) { 
            ans += 2LL * s * (s - 1); 
        }else{ 
            if(cnt.count(other)) { 
                ans += 2LL * s * cnt[other]; 
            }
        }
    }

    for(int i : cycle) { 
        cnt2.clear(); 
        dfs2(i, -1); 
        for(auto [f, s] : cnt2) { 
            int other = f - k; 
            if(k == 0) { 
                ans -= 1LL * s * (s - 1); 
            }else{ 
                if(cnt2.count(other)) { 
                    ans -= 1LL * s * cnt2[other]; 
                }
            }
        }
    }
    cout << ans << "\n"; 
}
