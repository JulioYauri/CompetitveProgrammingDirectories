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

const int p = 1'000'000'000 + 9; 
const int m1 = 998244353; 
const int m2 = 1'000'000'000 + 7; 
int add(int a, int b, const int &m) { return a + b >= m ? a + b - m : a + b; }
int sub(int a, int b, const int &m) { return a < b ? a - b + m : a - b; }
int mul(ll a, ll b, const int &m) { return a * b % m; }

struct Z { 
    int a, b; 
    Z (int a = 0, int b = 0) : a(a), b(b) { }
    Z operator+(const Z& rhs) const { return Z(add(a, rhs.a, m1), add(b, rhs.b, m2)); }
    Z operator-(const Z& rhs) const { return Z(sub(a, rhs.a, m1), sub(b, rhs.b, m2)); }
    Z operator*(const Z& rhs) const { return Z(mul(a, rhs.a, m1), mul(b, rhs.b, m2)); }
    bool operator==(const Z& rhs) const { return a == rhs.a && b == rhs.b ; }
};

Z helper(p, p);
Z nil(0, 0); 
const int LIM = 26; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n, qq; cin >> n >> qq; 
    string s; cin >> s; 

    vector<Z> pows(n); 
    pows[0] = Z(1, 1); 
    rep(i,1,n) pows[i] = helper * pows[i - 1]; 

    vector<vector<Z>> prs(LIM, vector<Z>(n)); 
    rep(i,0,n) { 
        int pos = s[i] - 'a'; 
        prs[pos][i] = pows[i]; 
    }

    rep(i,0,LIM) rep(j,1,n) prs[i][j] = prs[i][j - 1] + prs[i][j]; 

    vvi poss(LIM); 
    rep(i,0,n) poss[s[i] - 'a'].push_back(i) ;
    
    while(qq--) { 
        int l, r; cin >> l >> r; 
        l--, r--; 
        vii cnts(LIM); 
        rep(i,0,LIM) { 
            cnts[i].first = i; 
            cnts[i].second = upper_bound(all(poss[i]), r) - lower_bound(all(poss[i]), l); 
        }
        
        int mx = 0; 
        rep(j,0,LIM) mx = max(mx, cnts[j].second); 
        vi here; 
        rep(i,0,LIM) if(cnts[i].second == mx) here.push_back(i); 
        vi to(LIM, -1); 
        rep(i,0,sz(here)) { 
            rep(j,0,sz(here)) { 
                if(i == j) continue; 
                int u = here[i], v = here[j]; 
                Z u_hash = prs[u][r] - (l == 0 ? nil : prs[u][l - 1]); 
                Z v_hash = prs[v][r] - (l == 0 ? nil : prs[v][l - 1]); 
                if(u_hash * helper == v_hash) { 
                    to[u] = v; 
                }
            }
        }   
        vi memo(LIM, -1); 
        auto dp = [&](auto &&self, int u) { 
            if(u == -1) return 0; 
            if(memo[u] != -1) return memo[u]; 
            if(to[u] == -1) return 1; 
            return 1 + self(self, to[u]); 
        };  
        int ans = 0; 
        rep(i,0,LIM) ans = max(ans, dp(dp, i)); 
        cout << ans << "\n"; 
    }
}
