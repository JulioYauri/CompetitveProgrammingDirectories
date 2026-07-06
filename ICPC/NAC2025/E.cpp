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

    int n, k; cin >> n >> k; 
    vi h(n + 1), a(n + 1); 
    rep(i,1,n+1) cin >> h[i]; 
    rep(i,1,n+1) cin >> a[i]; 
    
    vii d(n); 
    vl pr(n + 1) ; 
    rep(i,1,n+1) { 
        pr[i] = d[i - 1].first = h[i] - a[i] ; 
        d[i - 1].second = i ; 
        pr[i] += pr[i - 1]; 
    } 

    sort(all(d)); 
    reverse(all(d)); 

    set<int> ss{0, n + 1}; 
    vector<tuple<ll,ll,ll>> queries_at(n + 1); 
    for(auto [val, pos] : d) { 
        auto ptr = ss.insert(val).first; 
        int l = *prev(ptr), r = *next(ptr); 
        if(pos - l < r - pos) { 
            
        }else{ 

        }
    }
}
