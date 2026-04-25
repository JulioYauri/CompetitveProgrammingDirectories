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
    priority_queue<int> pq; 
    ll ans = 0; 
    rep(i,0,n) { 
        int x; cin >> x; 
        if(pq.empty()) pq.push(x); 
        else { 
            int b = pq.top(); 
            if(b < x) pq.push(x); 
            else { 
                ans += b - x; 
                pq.pop(); 
                pq.push(x); 
                pq.push(x); 
            }
        }
    }
    cout << ans << "\n"; 

}
