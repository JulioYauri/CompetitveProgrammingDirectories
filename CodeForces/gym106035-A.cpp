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
    vi v(n); rep(i,0,n) cin >> v[i]; 
    vi a(n - 1); 
    rep(i,0,n-1) a[i] = (v[i] > v[i + 1]) ; 

    int cnt = 0; 
    rep(i,0,n-2) cnt += (a[i] ^ a[i + 1]); 
    cout << (cnt == 1 ? "YES\n" : "NO\n"); 

}
