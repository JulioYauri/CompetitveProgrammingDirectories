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
    int n; cin >> n; 
    vi v(n); 
    rep(i,0,n) cin >> v[i]; 
    
    vi ds; 
    rep(i,1,n) { 
        int diff = v[i] - v[i - 1]; 
        if(diff > 0) ds.push_back(diff); 
    }
    
    sort(all(ds)); 
    ds.erase(unique(all(ds)), ds.end()); 

    if(sz(ds) == 0) { 
        assert(n == 2) ; 
        int first = v[1]; 
        int flast = v[0] / (first - 1); 
        cout << max(first, flast) << "\n"; 
        return ;
    }

    int ans = *max_element(all(ds)); 
    for(int i = n - 1; i > 0; i--) { 
        if(v[i] - v[i - 1] > 0) { 
            ans = max(ans, v[i] / (v[i] - v[i - 1])); 
        }
    }
    

    rep(i,1,n) { 
        if(v[i] - v[i - 1] <= 0) { 
            int last_d = -1; 
            if(i - 1 > 0) { 
                last_d = v[i - 1] - v[i - 2]; 
            }
            if(last_d == -1) { 
                if(i + 1 < n) { 
                    last_d = v[i + 1] - v[i] - 1; 
                }
            }
            if(last_d != -1)  { 
                ans = max(ans, v[i - 1] / last_d); 
            }
        }
    }
    cout << ans << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int tt; cin >> tt ; 
    while(tt--) solve(); 


}
