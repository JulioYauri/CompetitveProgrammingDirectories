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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

bool ask(ll l, ll r) { 
    cout << l << " " << r << endl; 
    string ans; cin >> ans; 
    if(l == r && ans == "Yes") exit(0); 
    if(ans == "Bad") exit(0); 
    return ans == "Yes"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    ll n, k; cin >> n >> k; 
    ll l = 1, r = n; 
    while(true) { 
        while(r - l + 1 > 4 * k + 3) { 
            ll m = l + (r - l) / 2; 
            bool inside = ask(l, m); 
            if(inside) { 
                l = max(1LL, l - k); 
                r = min(n, m + k); 
            }else{ 
                l = max(1LL, m + 1 - k); 
                r = min(n, r + k);         
            }
        }
        ll who = l + rng() % (r - l + 1); 
        ask(who, who); 
        l = max(1LL, l - k); 
        r = min(n, r + k); 
    }
}
