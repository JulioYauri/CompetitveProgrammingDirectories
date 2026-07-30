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

const int mod = 998244353; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int mul(ll a, ll b) { return a * b % mod; }

void solve() {
    int n; cin >> n; 
    vi a(n - 1); rep(i,0,n-1) cin >> a[i]; 
    if(count(all(a), n)) { 
        cout << "0\n"; return; 
    }
    if(count(all(a), n - 1) == 0) { 
        cout << "0\n"; return; 
    }
    { // no aparecen separados  
        vector<bool> vis(n + 1, false); 
        for(int l = 0, r; l < sz(a); l = r) { 
            r = l + 1; 
            while(r < sz(a) && a[l] == a[r]) r++; 
            if(vis[a[l]]) { 
                cout << "0\n"; return; 
            }
            vis[a[l]] = true; 
        }
    }
    rep(i,0,sz(a) - 1) { 
        if(a[i] == n - 1) break; 
        if(a[i + 1] < a[i]) { 
            cout << "0\n"; return; 
        }
    }
    for(int i = sz(a) - 1; i >= 1; i--) { 
        if(a[i] == n - 1) break; 
        if(a[i - 1] < a[i]) { 
            cout << "0\n"; return; 
        }
    }
    vi cnt(n + 1); 
    rep(i,0,n-1) cnt[a[i]]++; 
    rep(i,1,n+1) { 
        if(cnt[i] > i) { 
            cout << "0\n"; return; 
        }
    }
    int space = 0, ans = 1; 
    for(int x = n - 1; x >= 1; x--) { 
        if(cnt[x] == 0) { 
            ans = mul(ans, space); 
            space--; 
        }else{ 
            space += cnt[x] - 1; 
        }
    }
    cout << mul(ans, 2) << "\n";
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
