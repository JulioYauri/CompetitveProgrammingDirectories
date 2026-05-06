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

struct Ev { 
    int h, pos; 
    bool bar; 
    Ev() : h(0), pos(0), bar(false) { }
    Ev(int h, int pos, bool bar) : h(h), pos(pos), bar(bar) { }
};

struct DSU{
	int n;
    vi par, sz, r, total; 
    DSU (int n_) : n(n_) {
        par.resize(n); 
        sz.assign(n, 1);
        total.assign(n, 1); 
        r.resize(n); 
        rep(i,0,n) par[i] = r[i] = i; 
    }

    int get(int a) { return par[a] == a ? a : par[a] = get(par[a]); }
    void unite(int a, int b) {
        a = get(a), b = get(b);
        if(a == b) return; 
        sz[a] += sz[b]; 
        r[a] = max(r[a], r[b]); 
        total[a] += total[b]; 
        par[b] = a; 
    }

};

const int N = 500'000 + 3; 
vector<Ev> evs[N]; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n; cin >> n; 
    vi b(n); 
    rep(i,0,n) { 
        cin >> b[i]; 
        evs[b[i]].emplace_back(b[i], i, 1); 
    }

    rep(i,0,n-1) { 
        int h; cin >> h;
        evs[h].emplace_back(h, i, 0); 
    }
    evs[n].emplace_back(n, n - 1, 0); 

    vi last_h(n, 0) ; 
    vi d(n), total(n, 1); 
    DSU dsu(n); 

    auto add = [&](int col_pos, int width, int q) { 
        int l = col_pos - width + 1; 
        if(width == 0 || q == 0) return; 
        d[l] += q; 
        if(col_pos + 1 < n) d[col_pos + 1] -= q; 
    };      

    rep(h,0,n+1) { 
        // cerr << "height: " << h << " ======= \n"; 
        if(evs[h].empty()) continue; 
        vi Rs; 
        for(auto e : evs[h]) if(e.bar) { 
            int id = dsu.get(e.pos), col = dsu.r[id]; 
            Rs.emplace_back(col); 
        }
        // cerr << "rs: " ; 
        // for(int i : Rs) cerr << i << " " ; cerr << "\n"; 
        for(int l = 0, r = 0; l < sz(Rs); l = r) { 
            while(r < sz(Rs) && Rs[l] == Rs[r]) r++; 
            int who = dsu.get(Rs[l]), col = dsu.r[who]; 
            add(col, dsu.total[who], h - last_h[col]); 
            last_h[col] = h; 
            dsu.total[who] -= (r - l); 
        }

        vi to_update;
        for(auto e : evs[h]) if(!e.bar) { 
            int who = dsu.get(e.pos), my = dsu.r[who]; 
            if(to_update.empty() || to_update.back() != my) to_update.push_back(my); 
            if(my + 1 < n) { 
                int nxt = dsu.get(my + 1), nxt_r = dsu.r[nxt]; 
                if(to_update.empty() || to_update.back() != nxt_r) to_update.push_back(nxt_r) ;  
            }
        }
        
        // cerr << "to update: "; 
        // for(int i : to_update) cerr << i << " " ; cerr << "\n";  
        
        for(int rpos : to_update) { 
            int who = dsu.get(rpos); 
            add(rpos, dsu.total[who], h - last_h[rpos]); 
        }

        for(auto e : evs[h]) if(!e.bar) { 
            int who = dsu.get(e.pos), my = dsu.r[who]; 
            if(my < n - 1) { 
                dsu.unite(e.pos, my + 1); 
                int his_r = dsu.r[dsu.get(my + 1)];
                last_h[his_r] = h;  
            }
        }
    }   
    rep(i,1,n) d[i] += d[i - 1]; 
    for(int i : d) cout << i << " " ; cout << "\n"; 
}
