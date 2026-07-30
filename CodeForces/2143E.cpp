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
    string s; cin >> s; 
    rep(i,0,n-1) { 
        if(s[i] == s[i + 1] && s[i] == ')') s[i] = s[i + 1] = '(';
    }
    if((count(all(s), '(') - count(all(s), ')')) % 4) { 
        cout << "-1\n"; return; 
    }

    vi closing_pos; 
    rep(i,0,n) if(s[i] == ')') closing_pos.push_back(i); 
    
    vi st; 
    for(int i : closing_pos) { 
        if(sz(st) && (st.back() % 2) != i % 2) st.pop_back(); 
        else st.push_back(i) ; 
    }
    
    if(sz(st)) { 
        int cur = (st[0] % 2 == 0 ? 2 : 1); 
        for(int &i : st) i = cur, cur += 2; 
    }

    s = string(n, '('); 
    for(int i : st) { 
        if(i >= n) { 
            cout << "-1\n"; return; 
        }
        s[i] = ')'; 
    } 
    int ops = count(all(s), '(') - count(all(s), ')'); 
    ops /= 4; 
    for(int i = n - 1; i > 0 && ops > 0; i-=2) { 
        if(s[i] == ')' || s[i - 1] == ')') { 
            cout << "-1\n"; return; 
        }
        s[i] = s[i - 1] = ')'; 
        ops--; 
    }
    cout << s << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
