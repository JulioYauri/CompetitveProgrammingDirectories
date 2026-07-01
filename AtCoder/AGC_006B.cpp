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
	
    int n, x; cin >> n >> x; 
    if(n == 2) { 
        if(x == 2) cout << "Yes\n1 2 3\n"; 
        else cout << "No\n"; 
        return 0; 
    }
    if(x == 1 || x == 2 * n - 1) { 
        cout << "No\n"; return 0; 
    }
    vector<bool> vis(2 * n - 1 + 1) ; 
    vi ans(2 * n - 1) ; 
    if(x + 2 <= 2 * n - 1 && x >= 2) { 
        // tengo 2 mayores y uno menor 
        ans[n] = x; vis[x] = true;  
        ans[n - 1] = 1; vis[1] = true; 
        ans[n - 2] = 2 * n - 1; vis[2 * n - 1] = true; 
        ans[n + 1] = 2 * n - 2; vis[2 * n - 2] = true; 
    }else{ 
        ans[n] = x; vis[x] = true; 
        ans[n - 1] = 2 * n - 1; vis[2 * n - 1] = true; 
        ans[n - 2] = 1; vis[1] = true; 
        ans[n + 1] = 2; vis[2] = true; 
    }
    int val = 1; 
    rep(i,0,sz(ans)) if(ans[i] == 0) { 
        while(val <= 2 * n - 1 && vis[val]) val++; 
        ans[i] = val; 
        vis[val] = true; 
    }
    cout << "Yes\n"; 
    for(int i : ans) cout << i << "\n";  

}
