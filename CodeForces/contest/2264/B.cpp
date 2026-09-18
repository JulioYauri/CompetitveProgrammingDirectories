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
    int n, m; cin >> n >> m ; 
    vi a(n); rep(i,0,n) cin >> a[i]; 

    m--; 
    priority_queue<int> pq; 
    ll total = 0, ans = -(1LL << 62); 
    for(int x : a) { 
        if(sz(pq) == m) {
            ans = max(ans, - total + 1LL * x * (m + 1)); 
        }
        total += x; 
        pq.push(x); 
        if(sz(pq) == m + 1) { 
            total -= pq.top(); 
            pq.pop(); 
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
