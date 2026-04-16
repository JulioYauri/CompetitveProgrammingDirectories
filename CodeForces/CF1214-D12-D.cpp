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



signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m; cin >> n >> m; 
    vector<string> g(n); 
    rep(i,0,n) cin >> g[i]; 

    auto get_path = [&](){ 
        vector<vii> from(n, vii(m, {-1,-1})); 
        vvi vis(n, vi(m, 0)); 
        rep(i,0,n) rep(j,0,m) vis[i][j] = (g[i][j] == '#'); 
        
        queue<pii> q; q.emplace(0, 0); 
        vis[0][0] = 1; 
        while(sz(q)) { 
            auto [i, j] = q.front(); q.pop(); 
            if(i + 1 < n && !vis[i + 1][j]) { 
                vis[i + 1][j] = 1; 
                from[i + 1][j] = {i, j}; 
                q.emplace(i + 1, j); 
            }
            if(j + 1 < m && !vis[i][j + 1]) { 
                vis[i][j + 1] = 1; 
                from[i][j + 1] = {i, j}; 
                q.emplace(i, j + 1); 
            }
        }    
        vii path; 
        if(!vis[n - 1][m - 1]) return path; 
        for(auto p = from[n - 1][m - 1]; p != make_pair(0,0); p = from[p.first][p.second]) 
            path.push_back(p); 
        
        // for(auto [i, j] : path) cerr << i << " " << j << "\n"; 
        return path; 
    };
    int ans = 0; 
    while(true) { 
        vii cells = get_path(); 
        if(cells.empty()) break; 
        ans ++; 
        for(auto [i, j] : cells) g[i][j] = '#'; 
    }
    cout << ans << "\n"; 
}
