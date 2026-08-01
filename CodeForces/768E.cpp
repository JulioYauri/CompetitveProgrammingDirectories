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

int get(int n) {
    int i ;  
    for(i = 1; i <= n; i++) n -= i; 
    return i - 1;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    int total = 0; 
    rep(i,0,n) { 
        int x; cin >> x; 
        total ^= get(x); 
    }   
    cout << (total == 0 ? "YES\n" : "NO\n"); 

}
