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

const int N = 5000 + 10; 
vii adj[N]; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m; cin >> n >> m; 
    vii eds; 
    rep(i,0,m) { 
        int u, v; cin >> u >> v; 
        eds.emplace_back(u, v); 
        adj[u].emplace_back(v, i); 
        adj[v].emplace_back(u, i);
    }

    const double inf = 1e18; 
    vector<double> ans(m, inf); 
    vi d(n + 1); 
    vi ws(m, 1); 
    queue<int> q; 
    deque<int> dq; 
    rep(i,0,m+1) { 
        fill(all(d), -1); 
        d[1] = 0; 
        q.push(1); 
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            for(auto [v, idx] : adj[u]) { 
                if(d[v] == -1 && ws[idx] == 0) { 
                    d[v] = d[u] + 1; 
                    q.push(v); 
                }
            }
        }

        int num_one = 0, num_inf = 0; 
        if(d[n] != -1) { 
            num_one = d[n]; 
        }else{ 
            fill(all(d), -1);
            d[1] = 0;  
            dq.push_back(1); 
            while(sz(dq)) { 
                int u = dq.front(); dq.pop_front(); 
                for(auto [v, idx] : adj[u]) {
                    int nd = d[u] + ws[idx] ;  
                    if(d[v] == -1 || nd < d[v]) {
                        d[v] = nd; 
                        if(ws[idx]) dq.push_back(v); 
                        else dq.push_front(v); 
                    }
                }
            }
            num_inf = d[n]; 
        }
        int den_one = 0, den_inf = 0 ; 
        rep(k,0,m) { 
            if(ws[k] == 0) den_one++; 
            else den_inf++; 
            double h = inf; 
            if(den_inf == 0) { 
                if(num_inf == 0) h = double(num_one) / double(den_one);  
            }else{ 
                h = double(num_inf) / double(den_inf); 
            }
            ans[k] = min(ans[k], h); 
        }
        if(i < m) { 
            auto [u, v] = eds[i];   
            ws[i] = 0; 
        }
    }
    cout << fixed << setprecision(12) ;
    for(auto x : ans) cout << x << "\n"; 
}
