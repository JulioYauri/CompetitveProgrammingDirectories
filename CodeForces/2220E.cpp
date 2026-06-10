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

const double inf = 1e40; 

void solve() {
	int n; cin >> n; 
    string c; cin >> c; 
    vvi adj(n); 
    vi deg(n); 
    rep(i,1,n) { 
        int u, v; cin >> u >> v; 
        u--, v--; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        deg[u]++; 
        deg[v]++; 
    }

    vector<bool> extra(n, false); {
        queue<int> q; 
        rep(i,0,n) { 
            if(deg[i] == 1 && c[i] == '0') { 
                q.push(i); 
                extra[i] = true; 
            }
        }
        auto deg_cp = deg; 
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            for(int v : adj[u]) { 
                if(c[v] == '1' || extra[v]) continue; 
                deg_cp[v]--; 
                if(deg_cp[v] == 1) { 
                    q.push(v); 
                    extra[v] = true; 
                }
            }
        }
    }
    map<tuple<int,int,int>,double> dp; 
    // rooteo en u, parent, par se pinta antes que u ? 
    auto get_val = [&](auto &&self, int u, int par, int flag) -> double {
        if(dp.count({u, par, flag})) return dp[{u, par, flag}]; 
        if(c[u] == '1') return 0;
        vector<pair<double,double> > ch; 
        for(int v : adj[u]) { 
            if(extra[v] || v == par) continue; 
            ch.emplace_back(self(self, v, u, 0), self(self, v, u, 1)); 
        }
        double total = 0; 
        for(auto [f, s] : ch) total += f; 
        double ans = double(deg[u]) / (sz(ch) + flag) + total;  
        vector<double> profit(sz(ch)); 
        rep(i,0,sz(ch)) profit[i] = ch[i].second - ch[i].first; 
        sort(all(profit)) ; 
        int good = sz(ch); 
        rep(i,1,sz(ch) + 1) { 
            total += profit[i - 1];
            good --;  
            ans = min(ans, total + double(deg[u]) / (good + flag));
        }
        return dp[{u, par, flag}] = ans; 
    };  

    vi comp_id(n, -1); 
    int nc = 0; 
    rep(i,0,n) { 
        if(c[i] == '1' || extra[i] || comp_id[i] != -1 ) continue; 
        queue<int> q; 
        q.push(i) ; 
        comp_id[i] = nc++; 
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            for(int v : adj[u]) { 
                if(extra[v] || c[v] == '1' || comp_id[v] != -1) continue; 
                comp_id[v] = comp_id[u]; 
                q.push(v); 
            }
        }
    }
    vector<double> comp_min(nc, inf); 
    rep(i,0,n) { 
        if(comp_id[i] == -1) continue; 
        double total = 0;
        int good = 0;  
        for(int v : adj[i]) if(!extra[v]) total += get_val(get_val, v, i, 0), good++;
        total += double(deg[i]) / good;  
        comp_min[comp_id[i]] = min(comp_min[comp_id[i]], total); 
    }

    double ans = accumulate(all(comp_min), 0.0); 
    rep(i,0,n) if(extra[i]) ans += double(deg[i]); 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cout << fixed << setprecision(12); 

	int tt; cin >> tt; 
	while(tt--) solve();
}
