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

    int n; cin >> n; 
    vi v(2 * n - 1); rep(i,0,sz(v)) cin >> v[i]; 
    
    int lo = 0, hi = 2 * n; 
    vi a(2 * n - 1); 
    while(hi - lo > 1) { 
        int mi = lo + hi >> 1; 
        rep(i,0,sz(a)) a[i] = (v[i] >= mi); 
        pii right = {n - 1, -1}; 
        rep(i,n-1,2*n-1-1) { 
            if(a[i] == a[i + 1]) { 
                right.first = i - n - 1; 
                right.second = a[i]; 
                break; 
            }
        }
        pii left = {n - 1, -1}; 
        for(int i = n - 1; i > 0; i--) { 
            if(a[i] == a[i - 1]) { 
                left.first = n - 1 - i; 
                left.second = a[i]; 
                break; 
            }
        }
        bool ok ; 
        if(right.second == -1 && left.second == -1) { 
            ok = (n % 2 == 0) != (a[n - 1] == 1);
        }else if(left.second == -1) {
            ok = (right.second == 1); 
        }else if(right.second == -1) { 
            ok = (left.second == 1); 
        }else{ 
            if(right.second == left.second) { 
                ok = (left.second == 1); 
            }else{ 
                int closest_one = (left.second == 1 ? left.first : right.first); 
                int closest_zero = (left.second == 0 ? left.first : right.first); 
                ok = (closest_one < closest_zero); 
            }
        }
        if(ok) lo = mi; 
        else hi = mi; 
    }
    cout << lo << "\n"; 
}
