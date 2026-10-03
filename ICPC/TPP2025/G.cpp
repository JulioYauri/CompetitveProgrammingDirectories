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

    int n = 8; 
    vector<string> grid(n); 
    rep(i,0,n) cin >> grid[i]; 

    auto ok = [&](pii p) {
        auto [i, j] = p;  
        return i >= 0 && j >= 0 && i < n && j < n && grid[i][j] == '.'; 
    }; 

    auto kn = [&](vvi &v, pii cur, pii d1, pii d2) { 
        rep(i,0,2) { 
            cur.first += d1.first; 
            cur.second += d1.second; 
            if(!ok(cur)) { 
                return; 
            }
        }
        cur.first += d2.first; 
        cur.second += d2.second; 
        if(!ok(cur)) return ;
        v[cur.first][cur.second] = 1; 
    };  

    auto alf = [&](vvi &v, pii cur, pii d) { 
        while(ok(cur)) { 
            v[cur.first][cur.second] = 1; 
            cur.first += d.first; 
            cur.second += d.second; 
        }
    };  

    vector<vvi> gs(2, vvi(n, vi(n,0))); 
    vii cs(2); 
    rep(i,0,2) { 
        char c; cin >> c; 
        int i1, j1; cin >> i1 >> j1; 
        i1--, j1--; 
        cs[i] = {i1, j1}; 
        if(c == 'a') { 
            for(auto d1 : {1, -1}) { 
                for(auto d2 : {1, -1}) { 
                    alf(gs[i], cs[i], {d1, d2}); 
                }
            }
        }else{ 
            kn(gs[i], cs[i], {-1,0}, {0,-1}); 
            kn(gs[i], cs[i], {0,1}, {-1,0}); 
            kn(gs[i], cs[i], {1,0}, {0,1}); 
            kn(gs[i], cs[i], {0,-1},{1, 0});
        }
    }
    bool kantu = false, katur = false; 
    if(gs[0][cs[1].first][cs[1].second]) katur = true; 
    if(gs[1][cs[0].first][cs[0].second]) kantu = true; 
    if(kantu == katur) { 
        cout << "Empate\n"; 
    }else{ 
        cout << (kantu ? "Kantu\n" : "Katur\n"); 
    }
}
