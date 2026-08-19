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

int m, n;
vl dp_before, dp_cur;
const int MAXN = 6000 + 10; 
int dp[MAXN][MAXN]; 
long long C(int i, int j) { 
    if(i > j) return 0; 
    return dp[i][j]; 
}  

void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    pair<long long, int> best = {LLONG_MAX, -1};
    rep(k,optl,min(mid,optr)+1) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

ll solve() {
    dp_before.assign(n,0);
    dp_cur.assign(n,0);
    rep(i,0,n) dp_before[i] = C(0, i);
    rep(i,1,m) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }
    return dp_before[n - 1];
}

void solve2() {
    int N, K; cin >> N >> K; 
    vi v(N); rep(i,0,N) cin >> v[i]; 
    if(N == K) { 
        cout << "0\n"; return; 
    }
    // tomo k + 1 segmentos 
    n = N; 
    m = K + 1; 

    rep(i,0,N) dp[i][i] = 0; 
    rep(i,1,N) dp[i - 1][i] = (v[i - 1] > v[i]); 
    rep(len,3,N+1) { 
        rep(l,0,N) { 
            int r = l + len - 1; 
            if(r >= N) break; 
            dp[l][r] = dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1] + (v[l] > v[r]); 
        }
    }   
    cout << solve() << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve2();
}
