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
    vii cn(n); 
    rep(i,0,n) cin >> cn[i].first >> cn[i].second; 

    sort(all(cn)) ; 
    vii a ; 
    for(int l = 0, r = 0; l < n; l = r) { 
        int ones = 0; 
        while(r < n && cn[l].first == cn[r].first) { 
            ones += cn[r].second; 
            r++; 
        }
        a.emplace_back(r - l, ones); 
    }
    sort(all(a)) ; 
    reverse(all(a)) ; 
    vi q(1, a[0].first); 
    rep(i,1,sz(a)) { 
        int val = min(q.back() - 1, a[i].first); 
        if(val <= 0) break ;
        q.push_back(val); 
    } 
    priority_queue<int> pq; 
    int ans = 0, pos = 0; 
    for(int val : q) { 
        while(pos < sz(a) && a[pos].first >= val) { 
            pq.push(a[pos].second); 
            pos++; 
        }
        ans += min(pq.top(), val); 
        pq.pop(); 
    }
    cout << accumulate(all(q), 0) << " " << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
