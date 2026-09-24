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

const int N = 1'000'000 + 10; 
int a[N], ans[N];
bool vis[N];  

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    rep(i,1,n+1) cin >> a[i]; 
    
    vector<vvi> by_sizes(n + 2); 
    rep(i,1,n+1) { 
        if(vis[i]) continue; 
        vi cyc;
        int u = i;
        for(int u = i; !vis[u]; u = a[u]) cyc.push_back(u), vis[u] = true; 
        if(sz(cyc) % 2 == 0) { 
            by_sizes[sz(cyc)].push_back(cyc); 
            continue;  
        }
        if(sz(cyc) == 1) { 
            ans[cyc[0]] = cyc[0]; 
            continue; 
        }
        for(int j = 0, pos = sz(cyc) / 2 + 1; j < sz(cyc); j++, pos = (pos + 1 == sz(cyc) ? 0 : pos + 1)) { 
            ans[cyc[j]] = cyc[pos]; 
        }
    }
    for(int siz = 2; siz < sz(by_sizes); siz += 2) { 
        auto &vecs = by_sizes[siz]; 
        if(sz(vecs) % 2) { 
            cout << "-1\n"; return 0; 
        }
        for(int i = 0; i < sz(vecs); i+=2) { 
            auto &v1 = vecs[i]; 
            auto &v2 = vecs[i + 1]; 
            rep(j,0,sz(v1)) { 
                ans[v1[j]] = v2[j]; 
                ans[v2[j]] = v1[(j + 1) % sz(v1)];  
            }
        }
    }
    rep(i,1,n+1) cout << ans[i] << " "; cout << "\n"; 
}
