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

const int N = 35 + 4; 
const int M = 20; 
int n, m, g; 
vector<string> ss; 
int c[M];

int val[N], ans = 0; 
string my; 
bool test() { 
    rep(i,0,n) { 
        if(val[i]) my[i] = ss[0][i]; 
        else my[i] = (ss[0][i] ^ 1); 
    }
    // cerr << "my: " << my << "\n"; 
    rep(j,1,m) { 
        int tot = 0; 
        rep(i,0,n) tot += (ss[j][i] == my[i]) ; 
        if(tot != c[j]) { 
            return false; 
        }
    }
    // cerr << "good\n"; 
    return true; 
}
void dfs(int have, int pos) { 
    if(have == g) { 
        ans += test(); 
        return; 
    }
    if(pos == n) return ;
    val[pos] = 1; 
    dfs(have + 1, pos + 1); 
    val[pos] = 0; 
    dfs(have, pos + 1); 
}   

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    cin >> n >> m; 
    ss.resize(m);
    my.assign(n, '0');  
    rep(i,0,m) cin >> ss[i] >> c[i]; 
    g = c[0]; 
    dfs(0, 0); 
    cout << ans << "\n"; 
}
