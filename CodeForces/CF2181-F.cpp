#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define rep(i,a,b) for(int i = (a) ; i < (b) ; i++)

using namespace ::std;
using ll = long long;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef pair<int , int> pii;
typedef vector<pii> vii;

const ll inf = 1LL << 62; 
ll test(vl &d, vl &v, ll val) { 
    int n = sz(v); 
    d[0] = val; 
    rep(i,1,n) d[i] = v[i] - d[i - 1];  
    ll mx = *max_element(all(d)), mn = *min_element(all(d)); 
    if(mn == 0) return mx; 
    ll sum = accumulate(all(d), 0LL); 
    return max(mx, (sum + (n - 1) - 1) / (n - 1)); 
}

void solve() { 
    int n; cin >> n; 
    vl v(n); rep(i,0,n) cin >> v[i]; 
    if(n % 2) { 
        vl d(n); 
        d[0] = 0; 
        rep(i,1,n) d[i] = v[i] - d[i - 1]; 
        ll x = (v[0] - d.back()) / 2;
        cout << test(d, v, x) << "\n";  
    }else{ 
        vl d(n); 
        d[0] = 0; 
        rep(i,1,n) d[i] = v[i] - d[i - 1]; 
        ll L = 0, R = inf; 
        rep(i,0,n) { 
            if(i % 2) R = min(R, d[i]); 
            else L = max(L, -d[i]); 
        }
        
        while(R - L >= 5) { 
            ll mid = (L + R) / 2; 
            if(test(d, v, mid) > test(d, v, mid + 1)) L = mid; 
            else R = mid + 1; 
        }

        rep(i,L+1,R+1) if(test(d,v,L) > test(d,v,i)) L = i;
        cout << test(d,v,L) << "\n"; 
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt; cin >> tt; 
    while(tt--) solve(); 

}