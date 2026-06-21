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
    vector<string> g(2 * n + 1);
    rep(i,0,n) g[0].push_back(' '); 
    rep(i,0,n+1) g[0].push_back('_'); 
    int f = n - 1; 
    rep(i,1,n) { 
        g[i].resize(sz(g[i - 1]) + 1, ' '), g[i].back() = '\\'; 
        g[i][f--] = '/'; 
    } 
    g[n].resize(sz(g[n - 1]) + n + 2, ' ');
    g[n][sz(g[n - 1])] = '\\';
    g[n][f] = '/' ; 
    g[n + 1].resize(sz(g[n]), ' ');
    g[n + 1].back() = '/'; 
    g[n + 1][n + 1] = '\\'; 
    f = n + 2; 
    rep(i,n+2,sz(g)) { 
        g[i].resize(sz(g[i - 1]) - 1, ' '); 
        g[i][f++] = '\\'; 
        g[i].back() = '/'; 
    }
    
    // fila n 
    for(int i = 1; ;i++) { 
        if(g[n + 1][i] == '\\') break ;
        g[n][i] = '_'; 
    }
    for(int i = sz(g[n]) - 1; ; i--) { 
        if(g[n][i] == '\\') break ; 
        g[n][i] = '_'; 
    }
    for(int i = sz(g.back()) - 2; ; i--) { 
        if(g.back()[i] == '\\') break; 
        g.back()[i] = '_'; 
    }
    for(auto s : g) cout << s << "\n"; 
}
