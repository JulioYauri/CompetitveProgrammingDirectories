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
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(ll a, ll b) { return a * b % mod; }
int bp(int a, int e) { 
    int ans = 1; 
    while(e) { 
        if(e & 1) ans = mul(ans, a); 
        a = mul(a, a); 
        e >>= 1; 
    }
    return ans; 
}

const int N = 100'000 + 10; 
int f[N]; 

void solve() {
    int n; cin >> n; 
    vii v(n); 
    for(auto &[f, s] : v) { 
        cin >> f >> s; 
        if(f > s) swap(f, s); 
    }

    auto area = [&](pii x) { return 1LL * x.first * x.second; };
    sort(all(v), [&](pii l, pii r){ return area(l) > area(r); });

    vii st(1, v[0]); 
    vi cnts(1, 1); 
    rep(i,1,n) { 
        if(area(st.back()) == area(v[i])) { 
            if(st.back() == v[i]) { 
                cnts.back()++; 
                continue; 
            }
            cout << "0\n"; return; 
        }
        st.push_back(v[i]); 
        cnts.push_back(1); 
    }

    // cerr << "cnts: "; 
    // for(auto i : cnts) cerr << i << "\n"; 
    // cerr << "st: "; 
    // for(auto [f, s] : st) cerr << f << " " << s << "\n"; 

    vector<pair<pii,int>> dp; 
    if(st[0].first == st[0].second) { 
        dp.emplace_back(st[0], 1); 
    }else{ 
        dp.emplace_back(st[0], 1); 
        dp.emplace_back(make_pair(st[0].second, st[0].first), 1); 
    }

    rep(i,1,sz(st)) { 
        vector<pair<pii,int>> ndp; 
        int w = st[i].first, h = st[i].second; 
        int total = 0; 
        for(auto [ms, cnt] : dp) { 
            int last_w = ms.first, last_h = ms.second; 
            int ways_w = max(last_w - w + 1, 0);
            int ways_h = max(last_h - h + 1, 0); 
            int ways = mul(ways_w, ways_h); 
            total = add(total, mul(cnt, ways)); 
        }
        if(total > 0) { 
            ndp.emplace_back(make_pair(w, h), total); 
        }
        if(w != h) { 
            swap(w, h); 
            total = 0; 
            for(auto [ms, cnt] : dp) { 
                int last_w = ms.first, last_h = ms.second; 
                int ways_w = max(last_w - w + 1, 0);
                int ways_h = max(last_h - h + 1, 0); 
                int ways = mul(ways_w, ways_h);
                total = add(total, mul(cnt, ways)); 
            }
            if(total > 0) { 
                ndp.emplace_back(make_pair(w, h), total); 
            }   
        }
        swap(dp, ndp) ; 
        if(dp.empty()) { 
            cout << "0\n"; return; 
        }
    }
    int ans = 0; 
    for(auto [f, s] : dp) ans = add(ans, s); 
    for(auto x : cnts) ans = mul(ans, f[x]) ; 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    f[0] = 1; 
    rep(i,1,N) f[i] = mul(f[i - 1], i); 

	int tt; cin >> tt; 
	while(tt--) solve();
}
