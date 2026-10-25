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

    int n, qq; cin >> n >> qq; 
    string s; cin >> s; 
    vi c4(n); 
    rep(i,0,n) if(s[i] == '4') c4[i] = 1; 
    rep(i,1,n) c4[i] += c4[i - 1] ; 

    while(qq--) { 
        int l, r, x, y; 
        cin >> l >> r >> x >> y; 
        l--, r--; 
        int t4 = c4[r] - (l == 0 ? 0 : c4[l - 1]); 
        int t8 = (r - l + 1) - t4; 
        x = abs(x); 
        y = abs(y); 
        if(x <= t8 && y <= t8) { 
            cout << "YES\n"; 
            continue; 
        }
        if(x < y) swap(x, y); 
        if(y <= t8) { 
            if(x <= t8 + t4) { 
                cout << "YES\n"; 
            }else{ 
                cout << "NO\n"; 
            }
        }else{ 
            x -= t8; 
            y -= t8; 
            if(x + y < t4 + 1) { 
                cout << "YES\n"; 
            }else{ 
                cout << "NO\n"; 
            }
        }
    }

}
