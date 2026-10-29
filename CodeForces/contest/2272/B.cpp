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

const int inf = 10'000'000; 

void solve() {
    int n; cin >> n; 
    string a, b; cin >> a >> b; 
    int total = 0; 
    rep(i,0,n) total += (a[i] == 'f'); 
    rep(i,0,n) total += (b[i] == 'f'); 
    cout << total % 2 << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
