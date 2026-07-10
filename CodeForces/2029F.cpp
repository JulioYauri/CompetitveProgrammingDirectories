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


bool solve() {
    int n; cin >> n; 
    string s; cin >> s; 
    if(count(all(s), s[0]) == n) return true;   
    
    rep(i,0,n) { 
        if(s[i] != s[0]) { 
            rotate(s.begin(), s.begin() + i, s.end()); 
            break; 
        }
    }

    vi cc; 
    for(int l = 0, r; l < n; l = r) { 
        r = l + 1; 
        while(r < n && s[r] == s[l]) r++; 
        cc.push_back(r - l); 
    }

    int odd1 = 0, even1 = 0; 
    rep(i,0,sz(cc)) if(cc[i] > 1) { 
        if(i % 2) odd1++; 
        else even1++; 
    }

    if(odd1 > 0 && even1 > 0) return false; 
    if(odd1 == 0 && even1 == 0) return false; 
    
    vi v; 
    if(odd1 > 0) for(int i = 1; i < sz(cc); i += 2) v.push_back(cc[i]); 
    else for(int i = 0; i < sz(cc); i += 2) v.push_back(cc[i]); 
    if(sz(v) == 1) return true; 
    
    int even_cnt = 0; 
    for(int x : v) even_cnt += (x % 2 == 0); 
    return even_cnt == 1; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) { 
        cout << (solve() ? "YES\n" : "NO\n") ; 
    }
}
