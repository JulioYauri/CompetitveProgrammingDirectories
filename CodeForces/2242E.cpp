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

string get_bn(ll x) { 
    string res; 
    while(x > 0) { 
        res.push_back('0' + (x % 2)); 
        x /= 2; 
    }
    reverse(all(res)); 
    return res; 
}

void solve() {
    ll l, r, n; cin >> l >> r >> n; 
    vi pots; 
    rep(i,0,32) { 
        ll p = (1LL << i) ; 
        if(p >= l && p <= r) pots.push_back(i); 
    }
    ll a, b;
    string sa, sb;  
    if(sz(pots) >= 2) { 
        a = (1LL << pots.end()[-1]);
        b = (1LL << pots.end()[-2]);  
        sa = get_bn(a), sb = get_bn(b); 
    }else if(sz(pots) == 0) { 
        string L = get_bn(l), R = get_bn(r); 
        sa = L, sb = R; 
        rep(i,0,sz(L)) { 
            if(L[i] == '0' && R[i] == '1') { 
                rep(j,i+1,sz(L)) { 
                    sa[j] = '1'; 
                    sb[j] = '0'; 
                }
                break; 
            } 
        }
    }else{ 
        ll pot = (1LL << pots[0]); 
        if(pot == l) a = pot, b = pot + 1; 
        else a = l, b = pot;
        sa = get_bn(a), sb = get_bn(b); 
    }
    rep(i,0,n) cout << ((sa[i % sz(sa)] == '1') & (sb[i % sz(sb)] == '1'));
    cout << "\n" ; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
