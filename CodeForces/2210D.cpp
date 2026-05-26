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

pii work(const string& s) { 
    int lf = 0 ; 
    rep(i,1,sz(s)) if(s[i - 1] == '(' && s[i] == ')') lf++; 
    int id = 1, who = sz(s) + 100;  
    vi st(1, 0), ch(sz(s) + 2), d(sz(s) + 2); 
    for(char c : s) { 
        if(c == '(') { 
            d[id] = d[st.back()] + 1; 
            st.push_back(id++); 
        }else{   
            st.pop_back(); 
            ch[st.back()]++; 
            if(ch[st.back()] >= 2) who = min(who, d[st.back()]); 
        }
    }
    return { who, lf } ; 
}   

void solve() {
    int n; cin >> n; 
    string s, t; cin >> s >> t; 
    cout << (work(s) == work(t) ? "YES\n" : "NO\n") ; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
