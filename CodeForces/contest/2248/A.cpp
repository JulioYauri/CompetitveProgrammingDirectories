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
    string s; cin >> s; 
    for(char &c : s) { 
        if(c == '1') { 
            c = ' '; 
            break;
        }
    }
    for(char &c : s) { 
        if(c == '0') { 
            c = ' ' ; 
            break; 
        }
    }
    for(char c : s) { 
        if(c != ' ') cout << c ; 
    }
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
