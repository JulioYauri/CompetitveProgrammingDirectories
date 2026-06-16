#include<bits/stdc++.h>
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define ll long long
using namespace std;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

ll sqr(ll x) { 
    ll sq = sqrtl(x) - 4; 
    sq = max(sq, 0LL); 
    while(sq * sq <= x) sq++; 
    return sq - 1; 
}

ll max_with(ll take, ll len, ll r, ll other_len) { 
    ll other_mx = sqr(4LL * r * r - take * len * take * len) / other_len; 
    return other_mx; 
}   
void solve() { 
    ll r, w, h; cin >> r >> w >> h; 
    if(w > h) swap(w, h); 

    auto f = [&](ll take) { 
        ll mx = max_with(take, h, r, w);
        return mx * take;  
        // ll nxt_mx = max_with(mx, w, r, h);
        // return mx * nxt_mx; 
    };

    ll a = 1, b = 2 * r / h; 
    while (b - a >= 5) {
		ll mid = a + (b - a) / 2;
		if (f(mid) < f(mid+1)) a = mid; // (A)
		else b = mid+1;
	}
	rep(i,a+1,b+1) if (f(a) < f(i)) a = i; // (B)
    cout << f(a) << "\n"; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt; cin >> tt; 
    while(tt--) solve(); 

}