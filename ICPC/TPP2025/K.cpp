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

    vi v(8); rep(i,0,8) cin >> v[i]; 
    int k; cin >> k; 

    int ans = -1; 
    rep(msk,1,1<<8) { 
        if((msk >> 7) & 1) continue;
        if(__builtin_popcount(msk) != k) continue;  
        vi cnt(8,0); 
        rep(i,0,8) { 
            if((msk >> i) & 1) { 
                cnt[i] ++; 
                cnt[i + 1]++; 
            }
        }
        if(*max_element(all(cnt)) > 1) continue; 
        string s; 
        rep(i,0,8) if(cnt[i] == 0) s.push_back('0' + v[i]); 
        if(s[0] == '0') continue; 
        ans = max(ans, stoi(s)); 
    }
    if(ans == -1) { 
        cout << "Indeterminado\n"; 
    }else{ 
        cout << ans << "\n"; 
    }
}
