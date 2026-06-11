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

bool compare(vi a, vi b){ 
    sort(all(a)); 
    sort(all(b)); 
    return a == b; 
}

void solve() {
    int n; cin >> n; 
    vi cnt;
    vector<string> v; 
    for(int bit = 0; ; bit++) { 
        int total = 0; 
        rep(i,1,n+1) total += ((i >> bit) & 1) ; 
        if(total == 0) break ;
        string s; cin >> s; 
        v.push_back(s); 
        cnt.push_back(total); 
    }

    int m = sz(cnt);    
    vi v_cnt(m);
    rep(i,0,m) v_cnt[i] = count(all(v[i]), '1'); 
    if(!compare(v_cnt, cnt)) { 
        cout << "0\n"; return; 
    } 

    rep(i,0,m) { 
        if(cnt[i] == v_cnt[i]) continue; 
        rep(j,i+1,m) { 
            if(v_cnt[j] == cnt[i]) { 
                swap(v_cnt[j], v_cnt[i]); 
                swap(v[j], v[i]); 
                break; 
            }
        }
    }

    vector<bool> vis(n + 1, false); 
    rep(i,0,n) { 
        int num = 0; 
        rep(b,0,m) { 
            if(v[b][i] == '1') num |= (1 << b); 
        }
        if(num > n || num == 0 || vis[num]) {
            cout << "0\n"; return;
        }
        vis[num] = true; 
    }
    ll ans = 1; 
    map<int,int> mp; 
    for(int i : cnt) mp[i]++; 
    for(auto [val, c] : mp) { 
        while(c >= 1) { 
            ans *= c; 
            c--; 
        }
    }
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
