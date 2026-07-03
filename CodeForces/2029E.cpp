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

const int N = 400'000 + 10; 
int mp[N]; 

void solve() {
	int n; cin >> n; 
    vi v(n); rep(i,0,n) cin >> v[i]; 
    sort(all(v)); 
    v.erase(unique(all(v)), v.end()); 
    int primes_cnt = 0; 
    n = sz(v); 
    rep(i,0,n) { 
        int x = v[i]; 
        if(mp[x] == x) primes_cnt++; 
    }
    if(primes_cnt >= 2) { 
        cout << "-1\n"; 
        return; 
    }

    if(primes_cnt == 0) { 
        cout << "2\n"; 
        return; 
    }

    if(mp[v[0]] != v[0]) { 
        cout << "-1\n"; 
        return; 
    }
    int pr = v[0]; 
    rep(i,1,n) { 
        if(v[i] > pr && v[i] < 2 * pr) { 
            cout << "-1\n"; return; 
        }
        // es >= q 2 * pr 
        if(v[i] % 2 == 0) continue; 
        if(v[i] - mp[v[i]] < 2 * pr) { 
            cout << "-1\n"; return; 
        }
    }
    cout << pr << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    rep(i,2,N) { 
        if(mp[i] == 0) { 
            mp[i] = i; 
            for(int j = i * 2; j < N; j += i) { 
                if(mp[j] == 0) mp[j] = i; 
            }
        }
    }

	int tt; cin >> tt; 
	while(tt--) solve();
}
