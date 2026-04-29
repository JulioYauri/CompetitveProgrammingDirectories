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
	
    int n; cin >> n; 
    ll total = 0; 
    vii p; 
    rep(i,0,n) { 
        string s; cin >> s; 
        int cnt_s = 0, cnt_h = 0; 
        for(char c : s) { 
            if(c == 's') { 
                cnt_s++; 
            }else{ 
                total += cnt_s; 
                cnt_h++; 
            }
        }
        p.emplace_back(cnt_s, cnt_h); 
    }

    sort(all(p), [&](auto lhs, auto rhs) { 
        return 1LL * lhs.second * rhs.first < 1LL * lhs.first * rhs.second; 
    }); 

    ll total_s = 0; 
    for(auto [s, h] : p) total += 1LL * h * total_s, total_s += s; 
    cout << total << "\n"; 

}
