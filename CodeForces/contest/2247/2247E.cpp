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
    ll n, k; cin >> n >> k; 
    if(k % 2) { 
        cout << "-1\n"; return; 
    }

    ll mn = 2 * (n - 1) ; 
    ll mx = n * (n - 1) / 2 + n / 2; 
    if(mn > k || k > mx) { 
        cout << "-1\n"; return; 
    }

    vi perm(n); ;
    perm[0] = 1; 
    perm.back() = n; 
    k -= mn;  
    for(int move = 2, final_pos = n - 2, pos = 1; move < n && k > 0; move += 2, final_pos--) { 
        ll can_do = (final_pos - pos) * 2;
        if(can_do < k) { 
            perm[final_pos] = move; 
            pos++; 
            k -= can_do; 
        } else{ 
            ll dist = k / 2; 
            perm[pos + dist] = move; 
            break; 
        }
    }

    vector<bool> vis(n + 1, false) ; 
    for(int i : perm) vis[i] = true; 
    int cur = 1; 
    rep(i,0,n) { 
        if(perm[i] != 0) continue; 
        while(vis[cur]) cur++; 
        perm[i] = cur; 
        vis[cur] = true; 
    }
    rep(i,0,n-1) cout << perm[i] << " " << perm[i + 1] << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
