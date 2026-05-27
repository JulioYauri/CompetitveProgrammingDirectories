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

    string s; cin >> s; 
    int n = sz(s); 
    int c0 = count(all(s), '0'), c1 = count(all(s), '1'), cc = n - c1 - c0; 
    
    vector<string> ans; 
    if(c0 + cc > c1) ans.push_back("00"); 
    if(c1 + cc >= c0 + 2) ans.push_back("11"); 

    auto test = [&](const string &t) { 
        // cerr << "testing: " << t << "\n"; 
        int last_1 = -1, last_0 = -1; 
        rep(i,0,sz(t)) { 
            if(t[i] == '1') last_1 = i; 
            else last_0 = i; 
        }
        if(last_1 == -1 || last_0 == -1) return ""; 
        if(last_0 > last_1) return "10"; 
        return "01"; 
    };

    rep(cc0,0,cc+1) { 
        int t0 = cc0 + c0, t1 = n - t0; 
        if(t0 == t1 || t0 + 1 == t1) { 
            string t = s; 
            int done = 0; 
            rep(i,0,n) { 
                if(t[i] == '?') { 
                    if(done == cc0) t[i] = '1'; 
                    else { 
                        t[i] = '0'; 
                        done++; 
                    }
                }
            }
            ans.push_back(test(t)); 
            t = s; 
            done = 0; 
            for(int i = n - 1; i >= 0; i--) { 
                if(t[i] == '?') { 
                    if(done == cc0) t[i] = '1'; 
                    else { 
                        t[i] = '0'; 
                        done++; 
                    }
                }
            }
            ans.push_back(test(t)); 
        }
    }
    sort(all(ans)); 
    ans.erase(unique(all(ans)), ans.end()) ; 
    for(auto i : ans) if(i != "") cout << i << "\n"; 
}
