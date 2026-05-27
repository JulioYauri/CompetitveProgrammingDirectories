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

const int N = 1'000'000 + 8; 
struct node{ 
    int mn, mx; 
    node() { mn = mx = 0; }
    node(int mn, int mx) : mn(mn), mx(mx) { }
    void add(int l) { 
        mn += l; 
        mx += l; 
    }
    node operator+(const node& rhs) const { 
        node res; 
        res.mx = max(mx, rhs.mx); 
        res.mn = min(mn, rhs.mn); 
        return res; 
    }
};
node t[N * 4]; 
int lazy[N * 4];

void push(int v) { 
    if(!lazy[v]) return ; 
    t[v * 2].add(lazy[v]) ; 
    t[v * 2 + 1].add(lazy[v]); 
    lazy[v * 2] += lazy[v]; 
    lazy[v * 2 + 1] += lazy[v]; 
    lazy[v] = 0; 
}

void upd(int v, int tl, int tr, int l, int r, int add) { 
    if(l > r) return ; 
    if(tl == l && r == tr) { 
        t[v].add(add); 
        lazy[v] += add; 
        return; 
    }
    push(v); 
    int tm = tl + tr >> 1; 
    upd(v * 2, tl, tm, l, min(r, tm), add); 
    upd(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, add); 
    t[v] = t[v * 2] + t[v * 2 + 1]; 
}

node nil ; 
node query(int v, int tl, int tr, int l, int r) { 
    if(l > r) return nil; 
    if(l == tl && r == tr) return t[v]; 
    push(v); 
    int tm = tl + tr >> 1; 
    return query(v * 2, tl, tm, l, min(r, tm)) +   
            query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r); 
}

int cur_val[N]; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    nil.mx = -8 * N; 
    nil.mn = 8 * N; 

    int n; cin >> n; 
    string com; cin >> com;

    int siz = 0, csiz = 1; 
    for(char c : com) { 
        if(c == 'R') csiz++; 
        if(c == 'L') csiz--; 
        siz = max(siz, csiz);  
    }
    siz += 3; 

    int ptr = 0, ans = 0; 
    for(char c : com) { 
        if(c == 'R')  { 
            ptr++; 
            cout << ans << " "; 
            continue; 
        } 
        else if(c == 'L') { 
            ptr--; 
            ptr = max(ptr, 0); 
            cout << ans << " "; 
            continue; 
        } 
        else if(c == '(') { 
            int cur = cur_val[ptr]; 
            upd(1,0,siz-1,ptr,siz-1,1-cur); 
            cur_val[ptr] = 1; 
        }else if(c == ')') { 
            int cur = cur_val[ptr]; 
            upd(1,0,siz-1,ptr,siz-1,-1-cur); 
            cur_val[ptr] = -1; 
        }else{ 
            int cur = cur_val[ptr]; 
            upd(1,0,siz-1,ptr,siz-1,-cur); 
            cur_val[ptr] = 0 ; 
        }
        node last = query(1,0,siz-1,siz-1,siz-1); 
        node q = query(1,0,siz-1,0,siz-1); 
        if(q.mn == 0 && last.mn == 0) ans = q.mx; 
        else ans = -1;
        cout << ans << " ";  
    }   
    cout << "\n"; 
}
