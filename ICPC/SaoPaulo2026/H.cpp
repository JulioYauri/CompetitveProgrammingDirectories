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

    vii res; 
    res.emplace_back(7 * 60, 10 * 60); 
    res.emplace_back(17 * 60, 20 * 60); 
    int n; cin >> n; 
    int cur = 5 * 60; 
    rep(_,0,n) { 
        int t; cin >> t; 
        cur += t; 
        for(auto [b, e] : res) { 
            if(b < cur && cur < e) { 
                int ex = cur - b; 
                cur = e + ex; 
                break; 
            }
        }
    }
    cout << cur - 5 * 60 << "\n"; 
}   
