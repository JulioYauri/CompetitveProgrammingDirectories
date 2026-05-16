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
    vl a(n), b(n); 
    rep(i,0,n) cin >> a[i]; 
    rep(i,0,n) cin >> b[i]; 

    vector<bool> cc(n, false); 
    rep(i,0,n) { 
        if(count(all(a), a[i]) > 1) cc[i] = true; 
    }

    ll ans = 0; 
    rep(i,0,n) {
        if(cc[i]) { 
            ans += b[i]; 
            continue; 
        }
        rep(j,0,n) { 
            if(cc[j] && ((a[i] & a[j]) == a[i]))  {
                ans += b[i]; 
                break ;
            } 
        } 
    }
    cout << ans << "\n"; 
}
