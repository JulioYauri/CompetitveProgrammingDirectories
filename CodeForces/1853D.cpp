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
    vii v(n); 
    rep(i,0,n) { 
        cin >> v[i].first; 
        v[i].second = i; 
    }
    
    sort(all(v)); 
    reverse(all(v));
    int pos_cnt = 0; 
    rep(i,0,n) { 
        if(v[i].first >= i + 1) pos_cnt++; 
        else break; 
    }


    auto add = [&](int l, int r, int x, vi &vec) { 
        if(l > r) return; 
        vec[l] += x; 
        if(r + 1 <= pos_cnt - 1) vec[r + 1] -= x; 
    };  
    
    vi ans(n), tot(n); 
    add(0, pos_cnt - 1, pos_cnt, tot); 

    if(pos_cnt < n && v[pos_cnt].first == 0) { 
        rep(i,0,pos_cnt) { 
            if(v[i].first != pos_cnt) { 
                cout << "NO\n"; return; 
            }
        }

        if(pos_cnt > 0) { 
            rep(i,pos_cnt,n) ans[i] = -2; 
            rep(i,0,pos_cnt) ans[i] = 1;
        }else{ 
            rep(i,0,n) ans[i] = -1; 
        }

        vi real_ans(n); 
        rep(i,0,n) real_ans[v[i].second] = ans[i];
        cout << "YES\n"; 
        for(int i : real_ans) cout << i << " "; cout << "\n"; 
        return; 
    }

    for(int l = pos_cnt, r, cur = -1; l < n; l = r, cur -= 2) { 
        r = l + 1; 
        ans[l] = cur; 
        while(r < n && v[l].first == v[r].first) { 
            ans[r] = cur; 
            r++; 
        }
        add(0, v[l].first - 1, 2, ans);     
        add(0, v[l].first - 1, r - l, tot); 
    }
    rep(i,1,pos_cnt) tot[i] += tot[i - 1], ans[i] += ans[i - 1]; 
    vi real_ans(n); 
    
    
    rep(i,0,pos_cnt) { 
        if(tot[i] != v[i].first) { 
            cout << "NO\n"; return; 
        }
    }
    
    rep(i,0,pos_cnt) { 
        if(ans[i] == 0) { 
            rep(j,0,pos_cnt) ans[j] ++; 
            rep(j,pos_cnt,n) ans[j] --; 
        }
    }

    rep(i,0,n) real_ans[v[i].second] = ans[i];
    cout << "YES\n"; 
    for(int i : real_ans) cout << i << " " ; cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
