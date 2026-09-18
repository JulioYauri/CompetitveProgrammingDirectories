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

const int N = 700 + 10;
const int mod = 1'000'000'000 + 7; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int mul(ll a, ll b) { return a * b % mod; }
int memo[N][N][3][3], par[N]; 
int dp(int l, int r, int lp, int rp) { 
    if(l + 1 == r) { 
        if((lp && rp) || (lp == 0 && rp == 0)) return 0; 
        return 1; 
    } 
    int &h = memo[l][r][lp][rp];
    if(h != -1) return h; 
    
    if(l == par[r]) { 
        h = 0; 
        if(lp && rp) return 0;
        if(lp == 0 && rp == 0) return 0;  
        rep(lp2,0,3) rep(rp2,0,3) { 
            if(lp2 > 0 && lp2 == lp) continue; 
            if(rp2 > 0 && rp2 == rp) continue; 
            h = add(h, dp(l + 1, r - 1, lp2, rp2)); 
        }
        return h; 
    }
    int nr = par[r] - 1, nl = par[r]; 
    h = 0; 
    rep(lp2,0,3) { 
        if(lp2 && rp) continue ;
        if(lp2 == 0 && rp == 0) continue;  
        int total = dp(nl, r, lp2, rp); 
        rep(rp2,0,3) { 
            if(rp2 > 0 && rp2 == lp2) continue; 
            h = add(h, mul(total, dp(l, nr, lp, rp2))); 
        } 
    }
    return h; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    string s; cin >> s; 
    vi st; 
    int n = sz(s); 
    rep(i,0,sz(s)) { 
        if(s[i] == '(') st.push_back(i); 
        else { 
            int w = st.back(); 
            par[w] = i; 
            par[i] = w; 
            st.pop_back(); 
        }
    }
    memset(memo, -1, sizeof(memo)); 
    int ans = 0;
    rep(lp,0,3) rep(rp,0,3) ans = add(ans, dp(0,n-1,lp,rp));  
    cout << ans << "\n"; 
}
