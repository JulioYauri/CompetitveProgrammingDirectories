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

vector<string> dirs = {"DR", "DL", "UR", "UL"};
vii dii = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int get_id(const string& s) { 
    rep(i,0,sz(dirs)) if(s == dirs[i]) return i; 
    return -1; 
}
const int inf = INT_MAX; 

void solve() {
    int n, m, si, sj, ei, ej; 
    string d; 
    cin >> n >> m >> si >> sj >> ei >> ej >> d; 
    vector vis(n, vector(m, vector<bool>(4, false))); 
    vector cnt(n, vector(m, vi(4, inf))); 
    si--, sj--, ei--, ej--; 

    auto ok = [&](int i, int j) { 
        return i >= 0 && j >= 0 && i < n && j < m;
    };

    map<pii, int> corner ; 
    corner[{0,0}] = 0; 
    corner[{0,m-1}] = 1; 
    corner[{n-1,0}] = 2; 
    corner[{n-1,m-1}] = 3; 

    int dir = get_id(d); 
    int i = si, j = sj; 
    cnt[i][j][dir] = 0; 
    while(!vis[i][j][dir]) { 
        vis[i][j][dir] = true; 
        if(i == ei && j == ej) break ;
        auto [di, dj] = dii[dir]; 
        int ni = i + di, nj = j + dj; 
        if(ok(ni, nj)) { 
            cnt[ni][nj][dir] = cnt[i][j][dir]; 
            i = ni, j = nj; 
            continue; 
        }
        int my = cnt[i][j][dir]; 
        if(corner.count({i, j})) { 
            dir = corner[{i, j}]; 
            tie(di, dj) = dii[dir]; 
            ni = i + di,nj = j + dj; 
        }else{  
            if(i == 0) { 
                dir = (dir == 3 ? 1 : 0); 
            }else if(i == n - 1) { 
                dir = (dir == 0 ? 2 : 3); 
            }else if(j == 0) { 
                dir ^= 1; 
            }else { // j = m - 1
                dir ^= 1; 
            }   
            tie(di, dj) = dii[dir]; 
            ni = i + di,nj = j + dj;
        }
        cnt[ni][nj][dir] = my + 1; 
        i = ni, j = nj; 
    }   

    int mn = inf; 
    rep(i,0,4) mn = min(mn, cnt[ei][ej][i]); 
    if(mn == inf) cout << "-1\n"; 
    else cout << mn << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
