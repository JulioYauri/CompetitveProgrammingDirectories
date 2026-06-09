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

using Z = array<int, 8> ;
const int N = 10, M = N * 3 + 4; 
Z memo[N][N][M]; 
bool vis[N][N][M]; 
Z dp(int lo, int hi, int k) { 
    if(vis[lo][hi][k]) return memo[lo][hi][k]; 
    Z h{0} ; 
    if(k == 0) { 
        h[lo]++; 
        vis[lo][hi][k] = true; 
        return memo[lo][hi][k] = h; 
    }
    int mi = (lo ^ hi); 
    Z L = dp(lo, mi, k - 1), R = dp(mi, hi, k - 1); 
    rep(i,0,8) h[i] += L[i] + R[i]; 
    vis[lo][hi][k] = true; 
    return memo[lo][hi][k] = h; 
}

void solve() {
    int n, k; cin >> n >> k; 
    string s1, s2; cin >> s1 >> s2; 
    array<int,4> arr{0}; 
    rep(i,0,n) {         
        if(s1[i] == '0' && s2[i] == '1') arr[0]++; 
        if(s1[i] == '1' && s2[i] == '0') arr[1]++; 
        if(s1[i] == '1' && s2[i] == '1') arr[2]++; 
    }
    ll ans = 0;     
    Z total = dp(6, 5, k); 
    rep(i,0,8) { 
        ll here = 0; 
        rep(bit,0,3) { 
            if((i >> bit) & 1) here += arr[bit]; 
        }
        ans += 1LL * total[i] * here * (n - here); 
    }
    int c1 = count(all(s2), '1') ; 
    ans += 1LL * c1 * (n - c1); 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
