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

void ps(vector<vl>& d) { 
    int n = sz(d); 
    rep(i,0,n) rep(j,0,n) cerr << d[i][j] << " \n"[j == n - 1]  ; 
}

struct ft2 { 
    int n; 
    vvi ft; 
    ft2(int n) : n(n)  { 
        ft.assign(n + 1, vi(n + 1, 0)); 
    }
    void upd(int i0, int j0, int v){
        for(int i=i0+1;i<=n;i+=i&-i)
        for(int j=j0+1;j<=n;j+=j&-j)
            ft[i][j]+=v;
    }
    int get(int i0, int j0){
        int r=0;
        for(int i=i0;i;i-=i&-i)
        for(int j=j0;j;j-=j&-j)
            r+=ft[i][j];
        return r;
    }
    int get_sum(int i0, int j0, int i1, int j1){
        i1++; j1++; 
        return get(i1,j1)-get(i1,j0)-get(i0,j1)+get(i0,j0);
    }
};

void solve() {
	int n, qq; cin >> n >> qq; 
    vector a(n, vl(n)); 
    rep(i,0,n) rep(j,0,n) cin >> a[i][j]; 
    rep(i,0,n) rep(j,0,n) { 
        int x; cin >> x; 
        a[i][j] -= x; 
    }
    
    vector l(n, vl(n)), u(n, vl(n)); 
    rep(i,0,n) rep(j,1,n) l[i][j] = a[i][j] - a[i][j - 1]; 
    rep(i,1,n) rep(j,0,n) u[i][j] = a[i][j] - a[i - 1][j]; 

    vector ddl(n, vl(n)), ddu(n, vl(n)); 
    rep(i,0,n) rep(j,1,n) ddl[i][j] = u[i][j] - u[i][j - 1]; 
    rep(i,1,n) rep(j,0,n) ddu[i][j] = l[i][j] - l[i - 1][j]; 

    ft2 dl(n), du(n); 
    rep(i,0,n) rep(j,1,n) if(ddl[i][j]) dl.upd(i, j, 1); 
    rep(i,1,n) rep(j,0,n) if(ddu[i][j]) du.upd(i, j, 1); 


    auto upd_hor = [&](int r, int c1, int c2, ll x) { 
        if(c1 < n) { 
            if(ddl[r][c1] != 0) dl.upd(r, c1, -1); 
            ddl[r][c1] += x; 
            if(ddl[r][c1] != 0) dl.upd(r, c1, 1); 
        }
        if(c2 < n) { 
            if(ddl[r][c2] != 0) dl.upd(r, c2, -1); 
            ddl[r][c2] -= x; 
            if(ddl[r][c2] != 0) dl.upd(r, c2, 1); 
        }
    };

    auto upd_ver = [&](int c, int r1, int r2, ll x) { 
        if(r1 < n) { 
            if(ddu[r1][c] != 0) du.upd(r1, c, -1) ; 
            ddu[r1][c] += x; 
            if(ddu[r1][c] != 0) du.upd(r1, c, 1); 
        }
        if(r2 < n) { 
            if(ddu[r2][c] != 0) du.upd(r2, c, -1); 
            ddu[r2][c] -= x;
            if(ddu[r2][c] != 0) du.upd(r2, c, 1);  
        }
    };    

    while(qq--) { 
        char c; cin >> c; 
        if(c == 'U') { 
            int r1, c1, r2, c2, x;
            cin >> r1 >> c1 >> r2 >> c2 >> x; 
            r1--, c1--, r2--, c2--; 
            if(r1 < n) upd_hor(r1, c1, c2 + 1, x); 
            if(r2 + 1 < n) upd_hor(r2 + 1, c1, c2 + 1, -x); 
            if(c1 < n) upd_ver(c1, r1, r2 + 1, x); 
            if(c2 + 1 < n) upd_ver(c2 + 1, r1, r2 + 1, -x);
        }else{ 
            int r1, c1, r2, c2; 
            cin >> r1 >> c1 >> r2 >> c2 ; 
            bool ok = true;
            r1--, c1--, r2--, c2--; 
            if(dl.get_sum(r1+1, c1+1, r2, c2)) ok = false;  
            if(du.get_sum(r1+1, c1+1, r2, c2)) ok = false; 
            cout << (ok ? "Yes\n" : "No\n"); 
        }   
    }
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
