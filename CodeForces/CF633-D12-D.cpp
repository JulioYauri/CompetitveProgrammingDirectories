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
    vi v(n); 
    map<ll,int> cnt; 
    rep(i,0,n) { 
        cin >> v[i]; 
        cnt[v[i]]++; 
    }

    int ans = count(all(v), 0);
    vi nv; 
    rep(i,0,n) { 
        if(v[i]) nv.push_back(v[i]); 
    } 
    if(ans) nv.push_back(0); 
    v = nv; 
    rep(i,0,sz(v)) rep(j,0,sz(v)) { 
        if(i == j) continue; 
        ll a = v[i], b = v[j]; 
        vl seq{a, b}; 
        cnt[a]--, cnt[b]--; 
        ll cur = a + b; 
        while(true) { 
            if(!cnt.count(cur) || cnt[cur]==0) break ;
            cnt[cur]--; 
            seq.push_back(cur); 
            cur = seq.back() + seq.end()[-2]; 
        }
        ans = max(ans, sz(seq)); 
        for(int x : seq) cnt[x]++ ; 
    }
    cout << ans << "\n"; 
}
