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

const int N = 400000 + 10; 
int n, d, k, ct;
int deg[N]; 
vii edges;  
void add(int u, int v) { 
    deg[u]++; 
    deg[v]++; 
    edges.emplace_back(u, v); 
}
void solve(int node, int dep) { 
    if(node > n || dep == 0 || sz(edges) == n - 1) return; 
    while(deg[node] < k && sz(edges) < n - 1) { 
        int to = ct++; 
        if(to <= n) { 
            add(node, to); 
            solve(to, dep - 1); 
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cin >> n >> d >> k ; d++;  
    if(n == 1) { 
        cout << "NO\n"; 
        return 0;  
    }

    if(n == 2) { 
        if(d != 2) cout << "NO\n"; 
        else { 
            cout << "YES\n"; 
            cout << "1 2\n";     
        } 
        return 0; 
    }

    if(d > n) { 
        cout << "NO\n"; return 0; 
    }
    rep(i,1,d) add(i, i + 1); 
    ct = d + 1; 
    rep(i,2,d) { 
        int available = min(i - 1, d - i);  
        solve(i, available);
    }
    if(sz(edges) == n - 1 && *max_element(deg, deg + n + 1) <= k) { 
        cout << "YES\n"; 
        for(auto [u, v] : edges) cout << u << " " << v << "\n"; 
    }else cout << "NO\n"; 

}
