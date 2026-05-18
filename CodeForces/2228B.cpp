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
    int n, x1, x2, k; 
    cin >> n >> x1 >> x2 >> k; 
    if(n <= 3) { 
        cout << "1\n"; return;  
    }
    int d = abs(x1 - x2); d = min(d, n - d); 
    cout << k + d << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
