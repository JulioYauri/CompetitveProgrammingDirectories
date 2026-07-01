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


const int mod = 998244353; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int mul(ll a, ll b) { return a * b % mod; }

const int N = 500 + 10 ; 
int dp0[N][N], dp1[N][N]; 

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s; 
    
    reverse(all(s)); 
    vi dp(k + 1, 0); dp[0] = 1; 
    for(char c : s) { 
        vi ndp = dp; 
        rep(he,0,k) { 
            rep(me,1,k+1) {  
                if(he + me > k) break; 
                if(c == '1') { 
                    ndp[he + me] = add(ndp[he + me], mul(dp[he], dp1[he][me]));
                }else{ 
                    ndp[he + me] = add(ndp[he + me], mul(dp[he], dp0[he][me]));
                }
            }
        }
        swap(dp, ndp); 
    }
    cout << dp[k] << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    dp0[1][0] = dp0[0][1] = 1; 
    rep(total,1,N-2) { 
        rep(a,0,total+1) { 
            int b = total - a; 
            if(total % 2 == 0) dp0[a][b + 1] = add(dp0[a][b + 1], dp0[a][b]); 
            dp0[a + 1][b] = add(dp0[a + 1][b], dp0[a][b]); 
        }
    }
    
    dp1[1][0] = 1; 
    rep(total,1,N-2) { 
        rep(a,0,total+1) { 
            int b = total - a; 
            if(total % 2) dp1[a][b + 1] = add(dp1[a][b + 1], dp1[a][b]); 
            dp1[a + 1][b] = add(dp1[a + 1][b], dp1[a][b]);  
        }
    }

	int tt; cin >> tt; 
	while(tt--) solve();
}
