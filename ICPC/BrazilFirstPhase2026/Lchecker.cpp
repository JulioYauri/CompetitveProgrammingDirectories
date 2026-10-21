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

const int N = 100 ; 
int D[N][N];
vector<string> grid(N); 

int get_dist(pii src, pii send) { 
    auto ok = [&](int i, int j) {
        return i >= 0 && j >= 0 && i < N && j < N && grid[i][j] != '#' && grid[i][j] != '/' && grid[i][j] != '\\';
    };
    
    memset(D, -1, sizeof(D)); 
    queue<pii> q; 
    q.emplace(src.first, src.second); 
    vii movs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; 
    while(sz(q)) { 
        auto [i, j] = q.front(); q.pop(); 
        for(auto [di, dj] : movs) { 
            int ni = i + di; 
            int nj = j + dj; 
            if(!ok(ni,nj)) continue; 
            if(D[ni][nj] == -1) { 
                D[ni][nj] = D[i][j] + 1; 
                q.emplace(ni, nj); 
            }
        }
    }
    return D[send.first][send.second]; 
}

signed main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

    rep(i,0,N) cin >> grid[i]; 


    vii xs, ds; 
    rep(i,0,N) rep(j,0,N) { 
        if(grid[i][j] == 'X') xs.emplace_back(i, j); 
        if(grid[i][j] == '/' || grid[i][j] == '\\') ds.emplace_back(i, j); 
    }

    int total = 0; 
    int first = get_dist({0,0}, xs[0]); 
    cout << "first: " << first << "\n"; 
    grid[ds[0].first][ds[0].second] = '.'; 
    pii cur = {0, 0} ; 
    rep(i,0,10) { 
        // x a puerta 
        int h = get_dist(cur, xs[i]) + 1; 
        cout << "now: " << h << "\n"; 
        grid[ds[i].first][ds[i].second] = '.'; 
        total += h; 
        cur = xs[i]; 
    }
    
    pii goal; 
    rep(i,0,N) rep(j,0,N) { 
        if(grid[i][j] == 'F') { 
            goal = {i, j}; 
            break;  
        }
    }
    int last = get_dist(cur, goal);
    total += last;  
    cout << "last " << last << "\n"; 
    cout << " total : " << total << "\n"; 
    cerr << "goal: " << goal.first << " " << goal.second << "  cur: " << cur.first << " " << cur.second << "\n"; 
}
