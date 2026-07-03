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


void solve() {
    int n; cin >> n; 
    vi a(n + 1); rep(i,1,n+1) cin >> a[i]; 
    vi b(n + 1); rep(i,1,n+1) cin >> b[i]; 
    
    vector<bool> vis2(n + 1, false); 
    vi cyc_len(n + 1), id(n + 1), cyc_sec(n + 1); 
    vector<set<int>> by_len(n + 1); 
    rep(i,1,n+1) if(!vis2[i]) { 
        vi cyc; 
        for(int u = i; !vis2[u]; u = a[u]) cyc.push_back(u), vis2[u] = true; 
        rotate(cyc.begin(), min_element(all(cyc)), cyc.end()) ; 
        for(int u : cyc) cyc_len[u] = sz(cyc), id[u] = cyc[0];
        int ID = id[cyc[0]]; 
        cyc_sec[ID] = (cyc[1 % sz(cyc)]);
        by_len[sz(cyc)].emplace(cyc[0]); 
    }
    
    vector<bool> vis(n + 1, false); 
    rep(i,1,n+1) if(b[i] != -1 && !vis[i]) { 
        int u = i, v = a[b[i]]; 
        if(cyc_len[u] != cyc_len[v]) { 
            cout << "NO\n"; return; 
        }   
        int v_id = id[v] ; 
        by_len[cyc_len[v_id]].erase(v_id); 
        while(!vis[a[u]]) { 
            vis[a[u]] = true; 
            if(b[a[u]] != -1 && b[a[u]] != v) { 
                cout << "NO\n"; return; 
            }
            b[a[u]] = v; 
            u = a[u]; 
            v = a[v]; 
        }
    }
    vi cnt(n + 1); 
    rep(i,1,n+1) if(b[i] != -1) cnt[b[i]] ++; 
    if(*max_element(all(cnt)) >= 2) { 
        cout << "NO\n"; return; 
    }
    
    rep(i,1,n+1) if(b[i] == -1) { 
        int u = i; 
        int v = *by_len[cyc_len[u]].begin(), v_id = id[v]; 
        by_len[cyc_len[v_id]].erase(v_id); 
        v = cyc_sec[v_id]; 
        while(!vis[a[u]]) { 
            vis[a[u]] = true; 
            if(b[a[u]] != -1 && b[a[u]] != v) { 
                cout << "NO\n"; return; 
            }
            b[a[u]] = v; 
            u = a[u]; 
            v = a[v]; 
        }
    }
    cout << "YES\n"; 
    rep(i,1,n+1) cout << b[i] << " "; cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
