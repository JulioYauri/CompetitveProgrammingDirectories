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

const int MAXN = 1'000'000 + 5; 

signed main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n, k; cin >> n >> k; 
    vi p(n); rep(i,0,n) cin >> p[i], p[i]--; 
    
    vi v;
    vector<bool> vis(n, false);  
    rep(i,0,n) { 
        if(vis[i]) continue; 
        int siz = 0; 
        for(int u = i; !vis[u]; u = p[u]) { 
            siz++; 
            vis[u] = true; 
        }
        v.push_back(siz); 
    }
    
    sort(all(v)); 
    vii pc; 
    for(int siz : v) { 
        if(pc.empty() || pc.back().first != siz) pc.emplace_back(siz, 1); 
        else pc.back().second++; 
    }
    
    bitset<MAXN> dp; dp[0] = 1;  
    for(auto [siz, cnt] : pc) { 
        for(int cur = 1; cur < cnt; cur *= 2) { 
            cnt -= cur; 
            dp |= (dp << (cur * siz)) ; 
        }
        if(cnt) dp |= (dp << (cnt * siz)); 
    }
    int mn = k + 1; 
    if(dp[k]) mn--; 

    int mx = 0; 
    { 
        vi pos; 
        auto nxt = [&](int id) { 
            if(pos[id] == v[id]) return -1; 
            pos[id]++ ; 
            if(v[id] % 2) return (pos[id] <= v[id] / 2 ? 2 : pos[id] > v[id] / 2 + 1 ? 0 : 1); 
            else return pos[id] <= v[id] / 2 ? 2 : 0; 
        };

        priority_queue<pii> pq; 
        rep(i,0,sz(v)) pos.push_back(1), pq.emplace(2, i); 
        rep(_,0,k) { 
            auto [cur_max, who] = pq.top(); pq.pop(); 
            mx += cur_max; 
            int new_val = nxt(who); 
            if(new_val != -1) pq.emplace(new_val, who); 
        }
    }
    cout << mn << " " << mx << "\n"; 
}
