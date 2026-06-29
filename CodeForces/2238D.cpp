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

const int N = 1'000'000 + 10; 
int mp[N]; 

void solve() {
	int n; cin >> n; 
    int total = 0, exp_sum = 0 ; 
    while(n > 1) { 
        int p = mp[n]; 
        total ++; 
        while(n % p == 0) { 
            n /= p; 
            exp_sum++; 
        }
    }
    cout << total + exp_sum - 1 << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    rep(i,0,N) mp[i] = i; 
    rep(i,2,N) { 
        if(mp[i] == i) { 
            for(int j = 2 * i; j < N; j += i) mp[j] = i ; 
        }
    }

	int tt; cin >> tt; 
	while(tt--) solve();
}
