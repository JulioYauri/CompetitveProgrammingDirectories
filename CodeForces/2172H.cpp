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

template<class T> 
vi cyclic_sort(T& v, int limit, int step) { 
    int n = sz(v); 
    vi c(n), cn(n), cnt(max(n, 300)); 
    vl p(n), pn(n); 
    rep(i,0,n) cnt[v[i]] ++; 
    rep(i,1,sz(cnt)) cnt[i] += cnt[i - 1]; 
    for(int i = n - 1; i >= 0; i--) p[--cnt[v[i]]] = i; 
    c[p[0]] = 0; 
    int classes = 1; 
    rep(i,1,n) { 
        if(v[p[i]] != v[p[i - 1]]) classes++; 
        c[p[i]] = classes - 1; 
    } 
    if(limit == 1) return c;
    for(int cur_siz = 2, h = 0; cur_siz <= limit; cur_siz *= 2, h++) { 
        rep(i,0,n) { 
            pn[i] = ((p[i] - 1LL * step * (1 << h)) % n + n) % n ; 
        } 
        fill(all(cnt), 0); 
        rep(i,0,n) cnt[c[pn[i]]]++; 
        rep(i,1,classes) cnt[i] += cnt[i - 1]; 
        for(int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i]; 
        cn[p[0]] = 0; 
        classes = 1; 
        rep(i,1,n) { 
            pii cur = {c[p[i]], c[(p[i] + 1LL * step * (1 << h)) % n]}; 
            pii prev = {c[p[i - 1]], c[(p[i - 1] + 1LL * step * (1 << h)) % n]}; 
            if(cur != prev) classes++; 
            cn[p[i]] = classes - 1; 
        }
        swap(c, cn); 
    }
    return c; 
}

template<class T> 
T apply_perm(T cur, vi perm) { 
    T ans(sz(cur), 0); 
    rep(i,0,sz(cur)) ans[i] = cur[perm[i]]; 
    return ans; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int k, t; cin >> k >> t; 
    string s; cin >> s ; 
    vi perm(1 << k); iota(all(perm), 0); 

    t %= k; 
    rep(_,0,t) { 
        vi np(1 << k); 
        for(int i = 0, l = 0, r = 1 << (k - 1); r < (1 << k); l++, r++) { 
            np[i++] = perm[l]; 
            np[i++] = perm[r]; 
        }
        perm = np; 
    }
    int siz = (1 << t), step = (1 << (k - t)); 
    vi sorted_segs = cyclic_sort(s, siz, step);     
    vi final_sort = cyclic_sort(sorted_segs, (1 << k) / siz, 1); 

    int beg = -1; 
    rep(i,0,sz(final_sort)) { 
        if(final_sort[i] == 0) { 
            beg = i; 
            break; 
        }
    }   
    rotate(s.begin(), s.begin() + beg, s.end()); 
    s = apply_perm(s, perm); 
    cout << s << "\n"; 

}
