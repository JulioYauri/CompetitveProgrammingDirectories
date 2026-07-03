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
    int n; cin >> n; 
    string s; cin >> s; 
    s.insert(s.begin(), '#');
    vector p(n + 1, vl(3, 0));
    p[0][0] = 1; 
    vl pr(n + 1, 0);  
    int cur = 0; 
    rep(i,1,n+1) { 
        if(s[i] == '1') cur ++; 
        else cur--;
        rep(j,0,3) p[i][j] = p[i - 1][j];
        cur = (cur + 3) % 3; 
        p[i][cur]++; 
        pr[i] = cur; 
    }

    vi L(n + 1); 
    for(int l = 1, r; l <= n; l = r) { 
        r = l + 1; 
        while(r <= n && s[r - 1] != s[r]) r++; 
        rep(i,l,r) L[i] = l ;  
    }
    
    ll ans = n; 
    rep(i,1,n+1) {  
        int from = min(L[i] - 1, i - 1), val = pr[i]; 
        if(from - 1 >= 0) rep(m,0,3) if(m != val) ans += p[from - 1][m]; 
    }
    cout << ans << "\n";
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
