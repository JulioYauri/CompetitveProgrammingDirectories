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

bool ask(char c) { 
    cout << c << endl ;
    char ans; cin >> ans; 
    return ans == c; 
}

void solve() {
    rep(i,0,100) { 
        char my = "FT"[rand() % 2]; 
        bool good = ask(my); 
        if(good) { 
            ask(my == 'F' ? 'T' : 'F'); 
        }else{ 
            ask(my); 
        }
    }
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
