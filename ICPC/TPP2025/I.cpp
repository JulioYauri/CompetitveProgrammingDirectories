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

const int N = 100'000 + 10; 
struct Node { 
    ll sum; 
    int c4, c2, c1, oth; 
    Node(ll sum_ = 0, int c4_ = 0, int c2_ = 0, int c1_ = 0, int oth_ = 0) : 
        sum(sum_), c4(c4_), c2(c2_), c1(c1_), oth(oth_) { }

    Node operator+(const Node& rhs) const { 
        Node res; 
        res.sum = sum + rhs.sum; 
        res.c4 = c4 + rhs.c4; 
        res.c2 = c2 + rhs.c2; 
        res.c1 = c1 + rhs.c1; 
        res.oth = oth + rhs.oth; 
        return res; 
    }
} t[N * 4];
int lz[N * 4]; 
int arr[N]; 

Node calc(int x) { 
    Node res; 
    if(x == 1) res.c1 = 1; 
    else if(x == 2) res.c2 = 1; 
    else if(x == 4) res.c4 = 1; 
    else res.oth = 1; 
    res.sum = x; 
    return res; 
}

void build(int v, int l, int r) { 
    if(l == r) { 
        t[v] = calc(arr[l]); 
        return; 
    }
    int m = l + r >> 1; 
    build(v * 2, l, m); 
    build(v * 2 + 1, m + 1, r); 
    t[v] = t[v * 2] + t[v * 2 + 1]; 
}


void apply(int v) { 
    Node &my = t[v]; 
    Node new_; 
    new_.c1 = my.c2; 
    new_.c4 = my.c1; 
    new_.c2 = my.c4; 
    new_.sum = new_.c1 + 2LL * new_.c2 + 4LL * new_.c4; 
    my = new_; 
}

void push(int v) { 
    if(lz[v] == 0) return; 
    rep(i,0,lz[v]) apply(v * 2), apply(v * 2 + 1); 
    lz[v * 2] = (lz[v * 2] + lz[v]) % 3; 
    lz[v * 2 + 1] = (lz[v * 2 + 1] + lz[v]) % 3; 
    lz[v] = 0; 
}

void update(int v, int tl, int tr, int l, int r) { 
    if(l > r) return; 
    if(t[v].oth > 0) { 
        if(tl == tr) { 
            int cur = t[v].sum; 
            if(cur % 2 == 0) cur /= 2; 
            else cur = cur * 3 + 1; 
            t[v] = calc(cur); 
            return; 
        }
        int tm = tl + tr >> 1; 
        update(v * 2, tl, tm, l, min(r, tm)); 
        update(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r); 
        t[v] = t[v * 2] + t[v * 2 + 1]; 
    }else{ 
        if(tl == l && r == tr) { 
            apply(v); 
            lz[v] = (lz[v] + 1) % 3; 
            return; 
        }
        push(v); 
        int tm = tl + tr >> 1; 
        update(v * 2, tl, tm, l, min(r, tm)); 
        update(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r); 
        t[v] = t[v * 2] + t[v * 2 + 1]; 
    }
}

ll query(int v, int tl, int tr, int l, int r) { 
    if(l > r) return 0; 
    if(l == tl && r == tr) return t[v].sum; 
    push(v); 
    int tm = tl + tr >> 1; 
    return query(v * 2, tl, tm, l, min(r, tm)) 
        + query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r); 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    rep(i,0,n) cin >> arr[i]; 
    build(1, 0, n - 1); 
    int qq; cin >> qq; 
    while(qq--) { 
        string s; cin >> s;
        int l, r; cin >> l >> r; 
        if(s[0] == 'Q') cout << query(1, 0, n - 1, l , r) << "\n"; 
        else update(1, 0, n - 1, l, r); 
    }

}
