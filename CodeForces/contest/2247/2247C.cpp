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
    vi a(n); rep(i,0,n) cin >> a[i]; 
    vi b(n); rep(i,0,n) cin >> b[i]; 

    if(a == b) { 
        cout << "0\n"; return; 
    }

    if(accumulate(all(a), 0) == 0) { 
        cout << "-1\n"; return;         
    }

    if(accumulate(all(b), 0) == n) { 
        cout << "-1\n"; return ;
    }

    int c10 = 0;
    rep(i,0,n) if(a[i] == 1 && b[i] == 0) c10 ++; 
    cout << (c10 % 2 == 0 ? 2 : 1) << "\n"; 


}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
