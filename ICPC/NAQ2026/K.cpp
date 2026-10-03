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
    int n; cin >> n; 
    string s = "123456789"; 
    int ans = -1; 
    rep(l,0,sz(s)) { 
        rep(r,l,sz(s)) { 
            string cur; 
            rep(i,l,r+1) cur.push_back(s[i]); 
            int num = stoi(cur); 
            if(num >= n) { 
                if(ans == -1 || ans > num) ans = num; 
            }
        }
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
