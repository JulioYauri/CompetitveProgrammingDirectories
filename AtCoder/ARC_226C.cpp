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
	int h, w; cin >> h >> w; 
    if(h % 2 == 0 || w % 2 == 0) { 
        int ans = (h / 2) * (w / 2); 
        cout << ans << "\n"; 
        for(int i = 0; i + 1 < h; i += 2) { 
            for(int j = 0; j + 1 < w; j += 2) { 
                cout << i + 1 << " " << j + 1 << " " << 1 << "\n"; 
            }
        }
        return; 
    }
    vector<tuple<int,int,int>> ans; 
    int n = min(h, w); 
    vvi g(h + 1, vi(w + 1));

    int cur_color = 1; 
    auto paint = [&](int i, int j, int c) { 
        ans.emplace_back(i, j, c); 
        g[i][j] = g[i + c][j] = g[i][j + c] = g[i + c][j + c] = cur_color; 
        cur_color++; 
    };

    for(int beg = 1, end = n; beg < end; beg += 2, end -= 2) { 
        paint(beg, beg, end - beg); 
        if(end - beg <= 3) break; 
        for(int i = beg + 1; i + 1 < end; i += 2) paint(i, beg, 1); 
        for(int j = beg + 1; j + 1 < end; j += 2) paint(end - 1, j, 1); 
        for(int i = end - 1; i - 1 > beg; i -= 2) paint(i - 1, end - 1, 1); 
        for(int j = end - 1; j - 1 > beg; j -= 2) paint(beg, j - 1, 1); 
    }

    if(h < w) { 
        for(int j = h + 1; j + 1 <= w; j += 2) { 
            for(int i = 1; i + 1 <= h; i += 2) { 
                paint(i, j, 1); 
            }
        }
    }else{  
        for(int i = w + 1; i + 1 <= h; i += 2) { 
            for(int j = 1; j + 1 <= w; j += 2) { 
                paint(i, j, 1); 
            }
        }
    }

    // cerr << "final grid\n"; 
    // rep(i,1,h+1) rep(j,1,w+1) cerr << g[i][j] << " \n"[j == w]; 

    cout << sz(ans) << "\n"; 
    for(auto [i, j, k] : ans) cout << i << " " << j << " " << k << "\n"; 
    
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
