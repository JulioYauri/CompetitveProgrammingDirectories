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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m, qq; cin >> n >> m >> qq; 
    string s; cin >> s; 
    vi p;
    set<int> ex; rep(i,0,n) ex.insert(i);  
    rep(i,0,m) { 
        int l, r; cin >> l >> r; 
        l--, r--; 
        set<int>::iterator ptr ; 
        while((ptr = ex.lower_bound(l)) != ex.end() && *ptr <= r) { 
            p.push_back(*ptr);
            ex.erase(*ptr);  
        }
    }

    int ones = count(all(s), '1'); 
    int siz = sz(p); 
    FT ft(siz);
    vi pos_p(n, -1) ; 
    rep(i,0,siz) { 
        int pos = p[i];
        pos_p[pos] = i;  
        if(s[pos] == '1') ft.update(i, 1); 
    }
    while(qq--) { 
        int x; cin >> x; 
        x--; 
        if(s[x] == '1') { 
            if(pos_p[x] != -1) ft.update(pos_p[x], -1); 
            ones--; 
            s[x] = '0'; 
        }else{ 
            if(pos_p[x] != -1) ft.update(pos_p[x], 1) ; 
            ones++; 
            s[x] = '1'; 
        }
        int mx = min(siz, ones); 
        cout << mx - ft.query(mx) << "\n"; 
    }

}
