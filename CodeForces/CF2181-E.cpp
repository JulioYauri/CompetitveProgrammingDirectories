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
    vii p, v(n); 
    rep(i,0,n) { 
        int f, s; cin >> f >> s; 
        p.emplace_back(f, 0); 
        p.emplace_back(s, 1); 
        v[i] = {f, s}; 
    }

    if(n == 1) { 
        cout << v[0].first - 1 + abs(v[0].second - v[0].first) << "\n"; 
        return; 
    }

    sort(all(p)); 
    int last_l = -1, med = p[n - 1].first; 
    rep(i,0,n) { 
        if(p[i].second == 1) last_l = i; 
    }
    ll ans = 0; 
    if(last_l == -1) {
        // ffffff ssssss 
        int m1 = p[n - 1].first, m2 = p[n].first; 
        bool same = false; 
        rep(i,0,n) if(v[i] == make_pair(m1,m2)) same = true; 
        if(!same) { 
            ll total = p[n].first - 1; 
            rep(i,0,n-1) total -= 2 * p[i].first; 
            rep(i,n+1,2*n) total += 2 * p[i].first;  
            cout << total << "\n"; return; 
        }   

        { // comienzo en p[n - 1], termino en p[n + 1]
            ll total = - 1; 
            rep(i,0,n-1) total -= 2 * p[i].first; 
            rep(i,n,2*n) total += (i == n + 1 ? 1 : 2) * p[i].first; 
            ans = max(ans, total); 
        }

        { // comienzo en p[n - 2], termino en p[n]
            ll total = -1; 
            rep(i,0,n) if(i != n - 2) total -= 2 * p[i].first; 
            rep(i,n,2*n) total += (i == n ? 1 : 2) * p[i].first; 
            ans = max(ans, total);  
        }

        { // comieno en p[n - 1] y bajo, termino bajando a p[n]
            ll total = 2 * p[n - 1].first - 1 - p[n].first; 
            rep(i,0,n-1) total -= 2 * p[i].first; 
            rep(i,n+1,2*n) total += 2 * p[i].first; 
            ans = max(ans, total); 
        }

        cout << ans << "\n"; 
        return; 
    } 
    
    // primero toco un f > med, termino en s <= med
    { 
        ll total = med - 1; 
        rep(i,0,n) total += (med - p[i].first) * 2; 
        rep(i,n,2*n) total += (p[i].first - med) * 2; 
        total -= (med - p[last_l].first); 
        ans = max(total, ans); 
    }

    // primero toco un f <= med, termino en s > med 
    {
        ll total = 0; 
        int f = -1, s = -1; 
        rep(i,0,n) { 
            if(p[i].second == 0) f = p[i].second; 
            total += 2 * (med - p[i].first); 
        }
        if(f != -1) { 
            rep(i,n,2*n) { 
                if(p[i].second == 1 && s == -1) s = p[i].second; 
                total += 2 * (p[i].first - med); 
            }   
            ans = max(ans, f - 1 + total - (med - f) + s - med) ; 
        }
    } 
    // comienzo y termino en > med  
    { 
        ll total = 0;   
        rep(i,0,n) total += 2 * (med - p[i].first); 
        int s = -1; 
        rep(i,n,2*n) { 
            total += 2 * (p[i].first - med); 
            if(p[i].second == 1 && s == -1) s = p[i].first; 
        }
        if(s != -1) { 
            ans = max(ans, total - 2 * (med - p[n - 1].first) + med - (s - med) - 1 ) ; 
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
