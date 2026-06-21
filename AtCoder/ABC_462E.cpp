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
    ll a, b, x, y; cin >> a >> b >> x >> y ; 
    x = abs(x); 
    y = abs(y); 
    ll diag = min(x, y), cost = diag * 2LL * min(a, b); 
    if(x > y) { 
        ll extra = x - y; 
        ll just_b = extra * b + ((extra + 1) / 2) * 2 * b; 
        ll just_a = extra * a + (extra / 2) * 2 * a ; 
        ll b_a = (extra + 1) / 2 * a + extra / 2 * b; 
        cost += min({b_a, just_b, just_a}); 
    }else{ 
        ll extra = y - x; 
        ll just_a = extra * a + ((extra + 1) / 2) * 2 * a;
        ll just_b = extra * b + (extra / 2) * 2 * b;  
        ll a_b = (extra + 1) / 2 * b + extra / 2 * a; 
        cost += min({a_b, just_a, just_b}); 
    }
    cout << cost << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
