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
    auto f = [&](ll x) { 
        ll y = max_with(x / h, h, r, w); 
        return x / h * y ; 
    }; 

    ll ans = 0; 
    rep(_,0,2) { 
        ll x = sqr(2LL * r * r);
        ll x_l = x / h * h; 
        for(int its = 0; its < 1000 && x_l > 0; its++, x_l -= h) ans = max(ans, f(x_l)); 
        ll x_r = x_l + h; 
        for(int its = 0; its < 1000 && x_r <= 2 * r; its++, x_r += h) ans = max(ans, f(x_r)); 
        swap(w, h); 
    } 
    cout << ans << "\n"; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt; cin >> tt; 
    while(tt--) solve(); 

}