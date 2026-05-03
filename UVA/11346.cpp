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


void solve() { 
    double a, b, s; cin >> a >> b >> s;

    if(s == 0) { 
        cout << 100.0 << "%\n"; return ; 
    }
    
    double xp = s / b; 
    double my_area = 0; 
    if(xp < a) my_area = b * xp + (log(a) - log(xp)) * s;
    else my_area = b * a; 
    cout << 100 * (b * a - my_area) / (a * b) << "%\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    cout << fixed << setprecision(6); 
    int tt; cin >> tt; 
    while(tt--) solve() ; 

}
