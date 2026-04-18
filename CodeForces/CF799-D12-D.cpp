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

const ll inf = 1LL << 20; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    ll a, b, h, w; cin >> a >> b >> h >> w; 
    int n; cin >> n; 
    vl ln(n); rep(i,0,n) cin >> ln[i] ; 
    sort(all(ln)); 
    reverse(all(ln)); 
    
    if(a < b) swap(a, b); 
    if(h < w) swap(h, w); 
    if(h >= a && w >= b) { 
        cout << "0\n"; return 0; 
    }


    vl dp(a + 1, 0); 
    if(h <= a) dp[h] = w; 
    else dp[a] = w; 
    int ans = 0; 
    for(auto val : ln) { 
        vl ndp = dp; 
        rep(i,1,a+1) if(dp[i]) { 
            ndp[i] = max(ndp[i], min(dp[i] * val, inf)); 
            int wh = min(i * val, a) ; 
            ndp[wh] = max(ndp[wh], dp[i]); 
        }
        swap(ndp, dp);
        ans++;  
        if(dp[a] >= b) { 
            cout << ans << "\n"; 
            return 0; 
        }
        for(int i = a; i >= b; i--) { 
            if(dp[i] >= a) { 
                cout << ans << "\n"; 
                return 0; 
            }
        }
    }
    cout << "-1\n"; 
}
