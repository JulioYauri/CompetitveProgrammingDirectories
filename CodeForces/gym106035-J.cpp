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

    int n, k, c; cin >> n >> k >> c; 
    vii g(c); rep(i,0,c) cin >> g[i].first >> g[i].second; 

    rep(i,1,n-k+2) { 
        bool ok = true; 
        for(auto [step, cnt] : g) { 
            int my = ((i + k - 1) / step) - ((i - 1) / step);
            if(my != cnt) { 
                ok = false; 
                break; 
            }
        }
        if(ok) { 
            cout << i << "\n"; return 0; 
        }
    }
    cout << "-1\n"; 
}
