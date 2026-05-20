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

const int N = 100000 + 4; 
int distinct = 0, locs = 0; 
int par[N], siz[N], cnt_siz[N]; 
bool alive[N]; 
void rem_siz(int s) { 
    cnt_siz[s]--; 
    if(cnt_siz[s] == 0) distinct--; 
}
void add_siz(int s) { 
    if(cnt_siz[s] == 0) distinct++; 
    cnt_siz[s]++; 
}
int get(int u) { return par[u] == u ? u : par[u] = get(par[u]); }
void unite(int u, int v) { 
    u = get(u); 
    v = get(v); 
    if(u == v) return; 
    locs--; 
    par[u] = v; 
    rem_siz(siz[u]); 
    rem_siz(siz[v]); 
    siz[v] += siz[u]; 
    add_siz(siz[v]); 
}   

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    vi v(n+1); 
    map<int,int> pos; 
    rep(i,1,n+1) { 
        cin >> v[i], pos[v[i]] = i; 
        par[i] = i; 
    } 

    vi vals(v.begin() + 1, v.end()); sort(all(vals)); 
    int k = -1, cur_locs = -1; 
    for(auto d : vals) { 
        int idx = pos[d] ; 
        alive[idx] = true; 
        siz[idx] = 1; 
        locs++; 
        add_siz(1); 
        if(alive[idx - 1]) unite(idx, idx - 1); 
        if(alive[idx + 1]) unite(idx, idx + 1);
        if(distinct == 1) {
            if(locs > cur_locs || (locs == cur_locs && (d + 1) < k)) { 
                cur_locs = locs; 
                k = d + 1; 
            }
        }
    }

    cout << k << "\n"; 
}
