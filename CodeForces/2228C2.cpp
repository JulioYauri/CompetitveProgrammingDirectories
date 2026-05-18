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
    ll a; cin >> a; 
    int n, mn = 20, mx = -1; cin >> n; 
    vector<bool> b(10, false); 
    rep(i,0,n) { 
        int x; cin >> x; 
        b[x] = 1; 
        mn = min(mn, x); 
        mx = max(mx, x); 
    }   
    if(a == 0) { 
        cout << mn << "\n"; 
        return ;
    }

    string s = to_string(a); 
    bool flag = true; 
    for(char c : s) { 
        if(!b[c - '0']) flag = false; 
    }
    if(flag) { 
        cout << "0\n"; return; 
    }

    ll ans = 1LL << 62; 
    auto test = [&](string t) { 
        ll h = stoll(t); 
        // cerr << "testing: " << h << "\n"; 
        ans = min(ans, abs(a - h)); 
    };
    int first = -1; 
    rep(i,1,10) { 
        if(b[i]) { 
            first = i; break ; 
        }
    }
    if(first != -1) { 
        test(string(1, '0' + first) + string(sz(s), '0' + mn)); 
    }
    string cur; 
    rep(pos,0,sz(s)) { 
        int dig = (s[pos] - '0'); 
        rep(i,dig+1,10) { 
            if(b[i]) { 
                string t = cur; 
                t.push_back('0' + i); 
                while(sz(t) < sz(s)) t.push_back('0' + mn); 
                test(t); 
                break; 
            }
        }
        for(int i = dig - 1; i >= 0; i--) { 
            if(b[i] || (i == 0 && pos == 0 && sz(s) > 1)) { 
                string t = cur; 
                t.push_back('0' + i); 
                while(sz(t) < sz(s)) t.push_back('0' + mx); 
                test(t); 
                break; 
            }   
        }
        if(b[s[pos] - '0']) cur.push_back(s[pos]); 
        else break; 
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
