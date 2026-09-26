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
    int n, m; cin >> n >> m; 
    string s; cin >> s; 
    
    vector<bool> bl(2 * n + 2 * m + 10, false); 
    vi v(m); 
    rep(i,0,m) { 
        cin >> v[i]; 
        if(v[i] < sz(bl)) bl[v[i]] = true; 
    }
    
    int cur = 1; 
    rep(i,0,n) { 
        if(s[i] == 'A') { 
            cur++;  
            v.push_back(cur); 
        }else{ 
            cur++; 
            while(cur < sz(bl) && bl[cur]) cur++; 
            bl[cur] = true; 
            v.push_back(cur);
            while(cur < sz(bl) && bl[cur]) cur++; 
        }
    }

    sort(all(v)); 
    v.erase(unique(all(v)), v.end()) ; 
    cout << sz(v) << "\n"; 
    for(int i : v) cout << i << " " ; cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
