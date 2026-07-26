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

int get(vi perm) {
    int n = sz(perm); 
    vector<bool> mex(n + 1, false); 
    int cur = 0, xr = 0; 
    rep(i,0,n) { 
        mex[perm[i]] = true; 
        while(mex[cur]) cur++; 
        xr ^= cur; 
    }
    return xr; 
}

void ps(const vi& v) { 
    cout << "YES\n"; 
    for(int i : v) cout << i << " " ; cout << "\n"; 
}

void solve() {
    int n, k; cin >> n >> k; 
    k ^= n ;
    vi v; 
    for(int bit = 30; bit >= 0; bit--) { 
        if((k >> bit) & 1) v.push_back(bit); 
    }

    v.push_back(-1); 
    vi ans(n, -1); 

    if((v[0] == -1 ? 0 : (1 << v[0])) > n - 1) { 
        cout << "NO\n"; return; 
    }

    vector<bool> vis(n, false); 
    for(int i = n - 1, v_i = 0; i >= 0, v_i < sz(v); i--, v_i++) { 
        int cur = (v[v_i] == -1 ? 0 : (1 << v[v_i]));
        ans[i] = cur; 
        vis[cur] = true; 
    }

    int cur = 0; 
    rep(i,0,n) { 
        if(ans[i] != -1) break; 
        while(vis[cur]) cur++; 
        ans[i] = cur; 
        vis[cur] = true; 
    }   
    ps(ans); 
}


void stupid() { 
    int n; cin >> n; 
    // int n, k; cin >> n >> k; 
    vi perm(n); iota(all(perm), 0); 

    map<int,vi> mp; 
    do { 
        vector<bool> mex(n + 1, false); 
        int cur = 0, xr = 0; 
        rep(i,0,n) { 
            mex[perm[i]] = true; 
            while(mex[cur]) cur++; 
            xr ^= cur; 
        }
        // cout << "perm: "; 
        // for(int i : perm) cerr << i << " " ; cerr << "  have: " << xr << "\n"; 
        mp[xr] = perm;  
    }while(next_permutation(all(perm))); 
    for(auto [f, s] : mp) { 
        cerr << f << " - "; 
        for(int i : s) cerr << i << " "; cerr << "\n"; 
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    // stupid() ; 
	int tt; cin >> tt; 
	while(tt--) solve();
}
