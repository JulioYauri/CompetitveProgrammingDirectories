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
	int n, q, g; cin >> n >> q >> g; 
    map<int,int> ld; 
    map<int,int> cnt; 
    while(q--) { 
        char c; cin >> c; 
        if(c == 'P') { 
            int gn; cin >> gn; 
            int a; cin >> a; 
            rep(i,0,a) { 
                int who; cin >> who; 
                if(ld.count(who)) { 
                    cnt[ld[who]]--; 
                }
                ld[who] = gn; 
                cnt[ld[who]]++; 
            }
        }else{ 
            int gn; cin >> gn; 
            cout << cnt[gn] << "\n"; 
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
