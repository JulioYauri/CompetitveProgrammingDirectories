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

using B = __int128_t; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    B sum = 0; 
    vl b(n+2); 
    rep(i,0,n+2) { 
        cin >> b[i]; 
        sum += b[i]; 
    }

    sort(all(b)) ; 
    reverse(all(b)); 
    sum -= b[0]; 

    B first_sum = B(b[0]) * B(n - 1); 
    B mx = sum - first_sum; 
    B S = b[0]; 

    b.erase(b.begin());
    rep(i,0,sz(b)) { 
        if(mx == b[i]) { 
            b.erase(b.begin() + i); 
            break; 
        }
    }

    cout << ll(S) << " " << ll(mx) << "\n"; 
    rep(i,0,sz(b)) b[i] = S - b[i]; 
    sort(all(b));      
    for(auto i : b) cout << i << " "; 
    cout << "\n"; 
}
