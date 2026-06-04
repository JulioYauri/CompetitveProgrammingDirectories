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

const int N = 20 + 3; 
int a[N], n; 
vector<tuple<int,int,int>> ans; 
 
void go(int from, int to, int dep) {
    if(dep == -1) return ;
    int goal = dep - a[dep] - 1; 
    go(from, 6 - from - to, goal); 
    ans.emplace_back(dep, from, to); 
    if(goal == dep - 1) { 
        go(6-from-to, to, goal); 
    }else{ 
        go(6 - from - to, from, goal); 
        go(from, to, dep - 1); 
    }
}   

void solve() {
    cin >> n; 
    rep(i,0,n) cin >> a[i]; 
    rep(i,0,n) { 
        if(a[i] > i) { 
            cout << "NO\n"; return; 
        }
    } 
    ans.clear(); 
    go(1,3,n-1);
    cout << "YES\n"; 
    cout << sz(ans) << "\n"; 
    for(auto [id, from, to] : ans) cout << id + 1 << " " << from << " " << to << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
