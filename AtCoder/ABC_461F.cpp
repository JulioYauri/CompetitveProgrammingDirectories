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

const int mod = 998244353; 
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int mul(ll a, ll b) { return a * b % mod; }

const int N = 4000  ; 
int f[N]; 

ll n; 
vl divs;
vvi dd; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    f[0] = 1; 
    rep(i,1,N) f[i] = mul(f[i - 1], i); 

    cin >> n;   
    for(ll i = 1; i * i <= n; i++) { 
        if(n % i == 0) { 
            divs.push_back(i); 
            if(i * i != n) divs.push_back(n / i); 
        }
    }
    sort(all(divs)); 
    auto get_pos = [&] (ll x) { 
        return lower_bound(all(divs), x) - divs.begin() ; 
    };

    dd.resize(sz(divs)); 
    rep(i,0,sz(dd)) { 
        rep(j,0,i+1) if(divs[i] % divs[j] == 0) dd[i].push_back(j); 
    }
    // cerr << "divs: "; 
    // for(auto i : divs) cerr << i << " " ; cerr << "\n"; 
    int m = sz(divs); 
    pii nil = {0, 0}; 
    vector<vii> dp(m, vii(m, nil)); 
    // cnt, sum 
    rep(i,0,m) dp[i][i] = {1, divs[i] % mod} ;  
    int ans = 0; 
    for(int len = 1; ; len++) { 
        rep(last,0,m) ans = add(ans, dp[m - 1][last].second);
        bool change = false; 
        vector ndp(m, vii(m, nil)); 
        rep(cur_mul,0,m) { 
            rep(cur_last,0,m) if(dp[cur_mul][cur_last] != nil) { 
                ll rest = n / divs[cur_mul]; 
                int pos1 = get_pos(rest); 
                auto &my_divs = dd[pos1];
                int pos2; 
                { 
                    int lo = -1, hi = sz(my_divs) ; 
                    while(hi - lo > 1) { 
                        int mi = lo + hi >> 1; 
                        if(divs[my_divs[mi]] <= divs[cur_last]) lo = mi; 
                        else hi = mi; 
                    }
                    pos2 = hi; 
                }
                int cnt = dp[cur_mul][cur_last].first; 
                int sum = dp[cur_mul][cur_last].second; 
                rep(i,pos2,sz(my_divs)) { 
                    ll nxt_div = divs[my_divs[i]]; 
                    int nxt_mult_pos = get_pos(divs[cur_mul] * nxt_div); 
                    int nxt_div_pos = my_divs[i]; 
                    int extra_cnt = mul(cnt, len + 1); 
                    ndp[nxt_mult_pos][nxt_div_pos].first = add(ndp[nxt_mult_pos][nxt_div_pos].first, 
                        extra_cnt);
                    ndp[nxt_mult_pos][nxt_div_pos].second = add(ndp[nxt_mult_pos][nxt_div_pos].second, 
                        add(mul(sum, len + 1), mul(extra_cnt, nxt_div % mod)));
                    change = true; 
                }
            }
        }
        swap(dp, ndp); 
        if(!change) break;
    }
    cout << ans << "\n"; 
}     

