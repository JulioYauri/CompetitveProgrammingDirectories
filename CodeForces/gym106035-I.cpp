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
	
    int n; cin >> n; 
    vvi adj(n); 
    vi deg(n); 
    rep(i,0,n+2) { 
        int u, v; cin >> u >> v; 
        u--, v--; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        deg[u]++; 
        deg[v]++; 
    }

    int tail = -1, head = -1; 
    vi seg43; 

    vector<bool> vis(n, false); 
    rep(i,0,n) { 
        if(deg[i] != 2 || vis[i]) continue; 
        queue<int> q; 
        vi d(n, -1);          
        vis[i] = true; 
        q.push(i);
        d[i] = 0;  
        vi ends; 
        vi lens; 
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            for(int v : adj[u]) { 
                if(vis[v]) continue; 
                if(deg[v] != 2) { 
                    ends.push_back(v); 
                    lens.push_back(d[u] + 1); 
                    continue ; 
                }
                vis[v] = true; 
                d[v] = d[u] + 1; 
                q.push(v); 
            }
        }
        assert(sz(ends) == 2); 
        if(deg[ends[0]] == 4 && deg[ends[1]] == 4) { 
            tail = lens[0] + lens[1]; 
        }else if(deg[ends[0]] == 3 && deg[ends[1]] == 3) { 
            head = lens[0] + lens[1] + 1;  
        }else { 
            seg43.push_back(lens[0] + lens[1] + 1); 
        }
    }
    while(sz(seg43) < 2) seg43.push_back(2); 
    cout << head << " " << seg43[0] + seg43[1] - 1 << " " << tail << "\n"; 

}
