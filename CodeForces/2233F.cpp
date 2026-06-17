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

vi get_divs(int x) { 
    vi d; 
    for(int i = 1; i * i <= x; i++) { 
        if(x % i == 0) { 
            d.push_back(i); 
            if(i * i != x) d.push_back(x / i); 
        }
    }
    sort(all(d)); 
    return d; 
}

const int NAX = 1500 ; 
ll memo[NAX][NAX]; 
vi a_divs, b_divs; 
int n, a, b; 

vi a_divs_divs[NAX], b_divs_divs[NAX]; 

ll dp(int i, int j) { 
    if(i == 0 && j == 0) return 0; // 1 1  
    ll &h = memo[i][j]; 
    if(h != -1) return h; 
    ll ans = 1LL << 62; 
    int cur_a = a_divs[i], cur_b = b_divs[j];
    for(int a_div_idx : a_divs_divs[i]) { // divs de a_div[i] 
        for(int b_div_idx : b_divs_divs[j]) { // divs de b_div[j]
            if(a_div_idx == i && b_div_idx == j) continue; 
            ans = min(ans, dp(a_div_idx, b_div_idx) + max(cur_a / a_divs[a_div_idx], cur_b / b_divs[b_div_idx])); 
        }   
    }
    return h = ans; 
}

signed main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> a >> b; 
    int g = gcd(a, b); 
    a /= g; 
    b /= g; 
    a_divs = get_divs(a), b_divs = get_divs(b); 
    rep(i,0,sz(a_divs)) { 
        rep(j,0,i+1) { 
            if(a_divs[i] % a_divs[j] == 0) a_divs_divs[i].push_back(j); 
        }
    }
    rep(i,0,sz(b_divs)) { 
        rep(j,0,i+1) { 
            if(b_divs[i] % b_divs[j] == 0) b_divs_divs[i].push_back(j); 
        }
    }
    memset(memo, -1, sizeof(memo)); 
    cout << dp(sz(a_divs) - 1, sz(b_divs) - 1) << "\n"; 
}
