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

void alice() { 
    int n, k; cin >> n >> k; 
    vi a(n, -1); 
    vi v(k); rep(i,0,k) cin >> v[i], v[i]--;
    for(int i : v) a[i] = 1; 
    vi st; 
    vector<bool> matched(n, false); 
    rep(i,0,n) { 
        if(a[i] == 1) { 
            st.push_back(i); 
        }else{ 
            if(sz(st)) st.pop_back(), matched[i] = true; 
        }
    }
    for(int i = n - 1; i >= 0; i--) { 
        if(a[i] == -1 && !matched[i]) { 
            v.push_back(i); 
            break; 
        }
    }
    for(int i : v) cout << i + 1 << " "; cout << "\n"; 
}

void bob() { 
    int n, k; cin >> n >> k; 
    vi a(n, -1) ; 
    rep(i,0,k+1) { 
        int x; cin >> x; 
        x--; 
        a[x] = 1; 
    }
    vi st; 
    rep(i,0,n) { 
        if(a[i] == 1) { 
            st.push_back(i); 
        }else{ 
            if(sz(st)) st.pop_back(); 
        }
    }
    cout << st[0] + 1 << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    string s; cin >> s; 
    int tt; cin >> tt; 
    if(s == "Alice") { 
        while(tt--) alice(); 
    }else{ 
        while(tt--) bob(); 
    }
}
