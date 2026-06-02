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

const int N = 3'500'000 + 5; 
int color[N]; 
vi adj[N]; 
set<int> alive; 

void calc(int u) { 
    int cnt = 0; 
    for(int v : adj[u]) cnt += (color[v] == color[u]); 
    if(cnt >= 2) alive.insert(u); 
    else alive.erase(u); 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m; cin >> n >> m; 
    rep(i,0,m) { 
        int u, v; cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    rep(i,1,n+1) color[i] = rand() % 4; 
    rep(i,1,n+1) calc(i); 

    array<int,4> cur_cnt; 
    while(sz(alive)) { 
        int u = *alive.begin(); alive.erase(alive.begin()) ; 
        fill(all(cur_cnt), 0); 
        for(int v : adj[u]) cur_cnt[color[v]]++; 
        int mn = 0; 
        rep(i,1,4) if(cur_cnt[i] < cur_cnt[mn]) mn = i; 
        color[u] = mn; 
        calc(u); 
        for(int v : adj[u]) calc(v); 
    }
    rep(i,1,n+1) cout << color[i] + 1 << " " ; cout << "\n"; 
}
