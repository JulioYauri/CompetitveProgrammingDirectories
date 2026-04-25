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
    if(n == 1) { 
        cout << "1\n"; return; 
    }
    if(n % 2) { 
        vi ans(n - 1); iota(all(ans), 2); 
        for(int i = 2; i + 1 < sz(ans); i += 4) swap(ans[i], ans[i + 1]); 
        ans.push_back(1); 
        for(int i : ans) cout << i << " "; cout << "\n";  
    }else{ 
        vi ans(n); iota(all(ans), 1); 
        for(int i = 1; i + 1 < sz(ans); i += 4) swap(ans[i], ans[i + 1]); 
        for(int i : ans) cout << i << " "; cout << "\n"; 
    }

}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
