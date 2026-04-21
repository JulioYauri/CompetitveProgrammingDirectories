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
    int n, a, b; cin >> n >> a >> b; 
    if(n % 2 || (a + b) % 2 == 0) { 
        cout << "No\n"; return; 
    }

    bool first = true; 
    string ans; 
    for(int r1 = 1; r1 <= n; r1 += 2) { 
        int r2 = r1 + 1; 
        if(a == r1 || a == r2) { 
            bool dir = true;  
            rep(col,1,n+1) { 
                if(col == b) ans.push_back('R'); 
                else { 
                    if(dir) ans.push_back('D'); 
                    else ans.push_back('U'); 
                    ans.push_back('R'); 
                    dir = !dir; 
                }
            }
            ans.pop_back(); ans.push_back('D'); 
            first = false; 
        }else{ 
            if(first) { 
                rep(i,1,n) ans.push_back('R'); 
                ans.push_back('D'); 
                rep(i,1,n) ans.push_back('L'); 
                ans.push_back('D'); 
            }else{  
                rep(i,1,n) ans.push_back('L'); 
                ans.push_back('D'); 
                rep(i,1,n) ans.push_back('R'); 
                ans.push_back('D'); 
            }
        }
    }
    ans.pop_back(); 
    cout << "Yes\n"; 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
