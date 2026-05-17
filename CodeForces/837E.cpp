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
	
    ll x, y; cin >> x >> y; 
    vl divs; 
    for(ll i = 1; i * i <= x; i++) { 
        if(x % i == 0) { 
            divs.push_back(i); 
            if(i * i != x) divs.push_back(x / i); 
        }
    }

    sort(all(divs)); 
    ll ans = 0; 
    while(y > 0) { 
        ll g = gcd(x, y), next_y = 0; 
        int pos = lower_bound(all(divs), g) - divs.begin() + 1; 
        while(pos < sz(divs)) { 
            if(divs[pos] % g == 0) next_y = max(next_y, y / divs[pos] * divs[pos]); 
            pos++; 
        }
        ans += (y - next_y) / g; 
        y = next_y; 
    }
    cout << ans << "\n"; 
}
