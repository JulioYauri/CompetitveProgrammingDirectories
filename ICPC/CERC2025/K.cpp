#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define rep(i,a,b) for(int i = (a) ; i < (b) ; i++)

using namespace ::std;
using ll = long long;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef pair<int , int> pii;
typedef vector<pii> vii;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    if(n % 2) { 
        cout << "NO\n"; return 0; 
    }
    int sd = n / 2, dd = 2; 

    vvi sides(sd, vi(dd)); 
    int cur = 1; 
    rep(i,0,sd) rep(j,0,dd) sides[i][j] = cur++; 

    vii edges; 
    rep(i,0,sd) { 
        int u = sides[i].back(), v = sides[(i + 1) % sd].back(); 
        edges.emplace_back(u, v); 
        // cerr << "outside " << u << " " << v << "\n"; 
        u = sides[i][0], v = sides[(i + 2) % sd][0]; 
        edges.emplace_back(u, v);
        // cerr << "bet " << u << " " << v << "\n"; 
        for(int j = 1; j < dd; j++) { 
            u = sides[i][j], v = sides[i][j - 1]; 
            edges.emplace_back(u, v); 
            // cerr << "my " << u << " " << v << "\n";    
        }
    }
    cout << sz(edges) << "\n"; 
    for(auto [u, v] : edges) cout << u << " " << v << "\n"; 

}