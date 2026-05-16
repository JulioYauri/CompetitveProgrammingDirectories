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
    
    int n, m; 
    ll a, b; cin >> n >> m >> a >> b; 
    vi A(n); rep(i,0,n) cin >> A[i]; 
    vi B(m); rep(i,0,m) cin >> B[i]; 
    vi l(m); rep(i,0,m) cin >> l[i]; 

    double mn = 1e30; 
    int lp = -1, rp = -1; 
    auto test = [&](int a_i, int b_i) { 
        double dist_a = sqrt(a * a + 1LL * A[a_i] * A[a_i]); 
        double dist_b = sqrt((b - a) * (b - a) + 1LL * (A[a_i] - B[b_i]) * (A[a_i] - B[b_i]));
        return dist_a + dist_b; 
    };

    rep(i,0,m) { 
        double h = l[i]; 
        int lo = 0, hi = n - 1; 
        while(hi - lo >= 5) { 
            int mid = lo + hi >> 1; 
            if(test(mid, i) > test(mid + 1, i)) lo = mid; 
            else hi = mid + 1; 
        }
        rep(j,lo+1,hi+1) if(test(lo, i) > test(j, i)) lo = j; 
        if(h + test(lo, i) < mn) { 
            mn = h + test(lo, i); 
            lp = lo; 
            rp = i; 
        }
    }
    cout << lp + 1 << " " << rp + 1 << "\n"; 
}
