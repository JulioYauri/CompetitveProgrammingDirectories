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

const int N = 500 + 3 ; 
int memo[N][N], n; 
string s; 

int dp(int l, int r) { 
    if(l >= r) return 0;  
    int &h = memo[l][r]; 
    if(h != -1) return h; 
    h = dp(l + 1, r - 1) + (s[l] == s[r]); 
    rep(m,l,r+1) { 
        if(l < m && m < r) { 
            if(s[l] == s[m]) h = max(h, 1 + dp(l + 1, m - 1) + dp(m, r));
            if(s[m] == s[r]) h = max(h, 1 + dp(l, m) + dp(m + 1, r - 1));
        }
        h = max(h, dp(l, m) + dp(m + 1, r)); 
    }
    // cerr << "l,r: " << l << " " << r << " -> " << h << "\n"; 
    return h; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    cin >> n >> s; 
    memset(memo, -1, sizeof(memo)); 
    cout << n - dp(0, n - 1) << "\n"; 

}
