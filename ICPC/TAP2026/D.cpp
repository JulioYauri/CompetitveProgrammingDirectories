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

vi vsum(vi &a, vi &b) { 
    vi ans; 
    int carry = 0; 
    rep(i,0,max(sz(a), sz(b))) { 
        int h = carry; 
        if(i < sz(a)) h += a[i]; 
        if(i < sz(b)) h += b[i]; 
        ans.push_back(h % 10); 
        carry = h / 10; 
    }
    while(carry > 0) ans.push_back(carry % 10), carry /= 10; 
    return ans; 
}

int sum(vi &a, vi &b) { 
    int total = 0, carry = 0; 
    rep(i,0,max(sz(a), sz(b))) { 
        int h = carry; 
        if(i < sz(a)) h += a[i]; 
        if(i < sz(b)) h += b[i]; 
        total += h % 10; 
        carry = h / 10; 
    }
    while(carry > 0) total += carry % 10, carry /= 10; 
    return total; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    string s; cin >> s; 
    vi v; rep(i,0,sz(s)) v.push_back(s[i] - '0') ; 
    reverse(all(v)); 
    vi z = v; 
    rep(i,0,8) z = vsum(z, v); 
    int lo = 0, hi = 2000000; 
    reverse(all(v)); 
    while(hi - lo > 1) { 
        int mi = lo + hi >> 1; 
        vi d; 
        int mi2 = mi; 
        while(mi2 > 0) d.push_back(mi2 % 10), mi2 /= 10; 
        if(sum(d, z) > mi) lo = mi; 
        else hi = mi; 
    }
    cout << hi << "\n"; 
}
