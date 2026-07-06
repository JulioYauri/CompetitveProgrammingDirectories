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

    int n, qq; cin >> n >> qq;  
    vii v(n); 
    rep(i,0,n) cin >> v[i].first >> v[i].second; 
    
    vector<tuple<int,int,int>> qs(qq); 
    rep(i,0,qq) {
        int d, o; cin >> d >> o; 
        qs[i] = {d, o, i}; 
    }

    const int inf = 1 << 25; 
    vi qans(qq, -1); 
    sort(all(qs)); 
    vii maxes(2, {inf, -1}); 
    int ptr = n - 1; 
    for(auto [d, rej, i] : qs) { 
        while(ptr >= 0 && v[ptr].first <= d) { 
            int cur_music = v[ptr].second; 
            bool found = false; 
            for(auto &[pos, music] : maxes) { 
                if(music == cur_music) { 
                    pos = ptr + 1;
                    found = true;  
                    break; 
                }
            }
            if(!found) { 
                maxes.emplace_back(ptr + 1, v[ptr].second); 
                sort(all(maxes)); 
                maxes.pop_back(); 
            }
            ptr--; 
        }   
        int ans = inf; 
        for(auto [pos, music] : maxes) { 
            if(music == rej || music == inf) continue; 
            ans = min(ans, pos); 
        }
        if(ans != inf) qans[i] = ans; 
    }
    for(auto i : qans) cout << i << "\n"; 
}
