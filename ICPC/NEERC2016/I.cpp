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

int f(int x) { return abs(x) % 2; }

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    freopen("integral.in", "r", stdin);
    freopen("integral.out", "w", stdout);

    int n; cin >> n; 
    vii v(n); rep(i,0,n) cin >> v[i].first >> v[i].second; 

    vi val(n), ls(n);
    rep(i,0,n) { 
        int x = v[(i + 1) % n].first - v[i].first; 
        int y = v[(i + 1) % n].second - v[i].second; 
        if(x == 0) { 
            val[i] = f(y); 
        }else if(y == 0) { 
            val[i] = f(x); 
        }else{ 
            val[i] = (x % 2 == 0 && y % 2 == 0) ^ 1; 
        }
    }
    
    ls = val; 
    rep(i,1,n) ls[i] += ls[i - 1]; 
    
    if(ls.back() % 2) { 
        cout << "0\n"; 
        return 0; 
    }

    int cnt[2][2][2] = { };
    rep(i,1,n) { 
        int x = f(v[i].first), y = f(v[i].second); 
        cnt[x][y][ls[i - 1] % 2]++; 
    } 

    ll ans = 0;
    int last = ls[n - 2];  
    for(int i = 0, j = n - 1; i < n; i++, j = (j + 1) % n) { 
        int x = f(v[i].first), y = f(v[i].second); 
        rep(xx,0,2) rep(yy,0,2) { 
            if(x == xx && y == yy) { 
                ans += cnt[x][y][0]; 
            }else{ 
                ans += cnt[xx][yy][1]; 
            } 
        }
        cnt[f(v[(i + 1) % n].first)][f(v[(i + 1) % n].second)][val[i]]--; 
        last += val[j]; 
        cnt[f(v[(j + 1) % n].first)][f(v[(j + 1) % n].second)][last % 2]++; 
        if(val[i] % 2) { 
            rep(xx,0,2) rep(yy,0,2) swap(cnt[xx][yy][0], cnt[xx][yy][1]); 
            last ^= 1; 
        }
    }
    cout << (ans - 2 * n) / 2 << "\n"; 
}
