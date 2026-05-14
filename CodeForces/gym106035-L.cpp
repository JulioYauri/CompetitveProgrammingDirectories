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

    int n; cin >> n; 
    cout << n << endl; 
    ll total = 0; 
    rep(i,1,n+1) { 
        cout << i << " " << i << endl; 
        total += 1LL * i * 500; 
    }

    ll have; cin >> have; 
    cout << "! " << have - total << endl;

}
