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

string ss = "ACGT"; 
int get_id(char c) { 
    rep(i,0,sz(ss)) if(c == ss[i]) return i; 
    return -1; 
}

struct AC {     
    vvi trie; 
    vi suflink, dict; 
    vi term;
    int ct, n, sigma; 
    AC(int n, int sigma = 30) : n(n), sigma(sigma) { 
        trie.assign(n + 10, vi(sigma, 0)) ; 
        suflink.resize(n + 10);
        term.resize(n + 10);  
        dict.resize(n + 10); 
        ct = 0; 
    }
    void add(const string& s, int id) { 
        int cur = 0; 
        for(char c : s) { 
            int now = get_id(c); 
            if(!trie[cur][now]) trie[cur][now] = ++ct; 
            cur = trie[cur][now];  
        }
        term[cur] = id; 
    }   
    void bfs(int src) { 
        queue<int> q; q.push(src); 
        while(sz(q)) { 
            int u = q.front(); q.pop(); 
            int lnk = suflink[u]; 
            if(term[lnk]) { 
                dict[u] = lnk; 
            }else{ 
                dict[u] = dict[lnk]; 
            }
            rep(c,0,sigma) { 
                if(trie[u][c]) { 
                    suflink[trie[u][c]] = (u == 0 ? 0 : trie[lnk][c]); 
                    q.push(trie[u][c]); 
                }else trie[u][c] = (u == 0 ? 0 : trie[lnk][c]); 
            }
        }
    }

};


const int N = 500'000 + 10; 
const int B = 325; 
int bb[B][B]; 
int mn[B]; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    string t; cin >> t; 
    AC ac(N, 5); 
    int m; cin >> m;
    vector<string> strs(m);  
    rep(i,0,m) {
        cin >> strs[i];  
        ac.add(strs[i], i + 1); 
    }

    int n = sz(t); 
    vector qs(n, vii());
    int qq; cin >> qq; 
    rep(_,0,qq) { 
        int l, r; 
        cin >> l >> r; 
        l--, r--; 
        qs[r].emplace_back(l, _); 
    }

    const int inf = 1'000'000 ; 
    rep(i,0,B) { 
        rep(j,0,B) bb[i][j] = inf; 
        mn[i] = inf; 
    }

    auto upd = [&](int pos, int val) { 
        bb[pos / B][pos % B] = min(bb[pos / B][pos % B], val); 
        mn[pos / B] = min(mn[pos / B], val); 
    };  

    auto qry = [&](int l, int r) { 
        int lb = l / B, rb = r / B;
        if(lb == rb) { 
            int ans = inf;  
            rep(i,l%B,r%B + 1) ans = min(ans, bb[lb][i]);  
            return ans; 
        }
        int ans = inf; 
        while(l / B == lb) ans = min(ans, bb[lb][l++ % B]); 
        while(r / B == rb) ans = min(ans, bb[rb][r-- % B]);     
        while(l / B <= r / B) ans = min(ans, mn[l / B]), l += B; 
        return ans; 
    };

    ac.bfs(0); 
    int cur = 0; 
    vi ans(qq, -1); 
    int idx = 0 ; 
    for(char c : t) { 
        int id = get_id(c); 
        cur = ac.trie[cur][id]; 
        int u = cur; 

        if(ac.term[u] != 0) { 
            int who = ac.term[u]; 
            int siz = sz(strs[who - 1]);
            upd(idx - siz + 1, who); 
        }
        while(u > 0) { 
            u = ac.dict[u]; 
            if(u == 0) break; 
            int who = ac.term[u]; 
            if(who == 0) break;
            int siz = sz(strs[who - 1]);
            upd(idx - siz + 1, who);
        }

        for(auto [l, qi] : qs[idx]) { 
            ans[qi] = qry(l, idx); 
        }

        idx++; 
    }

    for(int i : ans) cout << (i == inf ? -1 : i) << "\n"; 

}
