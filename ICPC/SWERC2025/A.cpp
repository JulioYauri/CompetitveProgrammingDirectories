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
    int n, k; cin >> n >> k; 
    vi cnt(4 * n + 10); 
    rep(i,0,n) { 
        int x; cin >> x; 
        cnt[x] ++; 
    }   
    
    vii st; 
    int ans = 0; 
    rep(i,0,sz(cnt)) { 
        if(cnt[i] == 0) { 
            if(sz(st) == 0) continue; 
            auto [pos, h] = st.back(); st.pop_back(); 
            if(h > k) ans = max(ans, i - pos);  
        }else{ 
            rep(h,2,cnt[i]+1) { 
                st.emplace_back(i, h);
            }
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
