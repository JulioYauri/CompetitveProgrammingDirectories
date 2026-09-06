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
    vi v(n); 
    rep(i,0,n) cin >> v[i]; 

    map<int,int> cnt; 
    for(int x : v) cnt[x]++; 

    int mx = 0, who = -1; 
    for(auto [f, s] : cnt) { 
        if(who == -1 || s > mx) { 
            mx = s; 
            who = f; 
        }
    }
    if(mx > n - mx) { 
        int total = 0; 
        for(int x : v) total += (x == who ? 0 : x); 
        total += (who * (n - mx)); 
        cnt[who] -= (n - mx); 
        total += min(cnt[who], 2) * who; 
        cout << total << "\n"; 
    }else{ 
        cout << accumulate(all(v), 0) << "\n"; 
    }

}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
