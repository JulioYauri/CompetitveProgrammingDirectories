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

using T = long double; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    vi w(n + 1); rep(i,1,n+1) cin >> w[i]; 

    vvi divs(n + 1) ; 
    rep(i,1,n+1) for(int j = i * 2; j <= n; j += i) divs[j].push_back(i); 

    vector<T> ex(n + 1), p(n + 1), s(n + 1);
    T total = accumulate(all(w), T(0.0)) ; 
    rep(i,1,n+1) p[i] = T(w[i]) / total; 
    ex[1] = 1 / (1 - p[1]); 
    s[1] = ex[1] * p[1];
    rep(i,2,n+1) {  
        T sum_ex = 0, sum_p = 0; 
        for(int x : divs[i]) sum_ex += ex[x], sum_p += p[x]; 
        s[i] += sum_ex * sum_p; 
        for(int x : divs[i]) s[i] -= s[x];
        ex[i] = s[i]; 

        ex[i] += sum_ex * p[i]; 
        s[i] += sum_ex * p[i]; 

        sum_p += p[i]; 
        ex[i] = ex[i] / (1 - sum_p); 
        s[i] += ex[i] * sum_p; 
    } 

    cout << fixed << setprecision(10) << accumulate(all(ex), 0.0) - 1 << "\n"; 
}
