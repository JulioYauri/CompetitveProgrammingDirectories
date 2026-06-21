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

const int N = 500 + 10 ; 
int p[N];
int n;  
ll memo[N][N]; 
bool vis[N][N]; 
ll dp(int l, int r) { 
    if(l >= r) return 0; 
    if(vis[l][r]) return memo[l][r] ; 
    vi nums; 
    rep(i,0,n) { 
        if(p[i] >= l && p[i] <= r) nums.push_back(p[i]); 
    }
    vi pos(sz(nums)); 
    rep(i,0,sz(nums)) pos[nums[i] - l] = i; 
    string s(r - l + 1, 'R');
    s[pos[0]] = 'x'; 

    auto calc = [&](int i) -> int {
        if(i == 0 || i >= sz(s)) return 0;  
        if(s[i - 1] != 'x') return s[i] != s[i - 1];    
        if(i - 2 >= 0) return s[i] != s[i - 2]; 
        return 0; 
    };

    ll &h = memo[l][r]; 
    int diffs = 0; 
    rep(root,l,r+1) { 
        h = max(h, diffs + dp(l, root - 1) + dp(root + 1, r)); 
        
        int p = pos[root - l]; 
        if(p + 1 < sz(s)) diffs -= calc(p + 1); 
        s[p] = 'L'; 
        diffs += calc(p + 1); 
        diffs += calc(p); 

        if(root + 1 <= r) { 
            p = pos[root + 1 - l]; 
            diffs -= calc(p);
            diffs -= calc(p + 1); 
            s[p] = 'x'; 
            diffs += calc(p + 1);  
        }
    }   
    vis[l][r] = true; 
    return h; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    cin >> n; 
    rep(i,0,n) cin >> p[i]; 
    cout << dp(0, n - 1) << "\n"; 
}
