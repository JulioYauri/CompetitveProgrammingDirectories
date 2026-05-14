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

int extra(int place) { 
    if(place > 50) return 0; 
    if(place >= 11) return 51 - place; 
    if(place > 5) return (31 - place) * 2; 
    vi arr = {0, 80, 68, 62, 57, 53} ; 
    return arr[place]; 
}

int solve(vii v) { 
    sort(all(v)); 
    int n = sz(v); 
    int total = 10 * v[0].second; 
    total += 2 * extra(v[0].first); 
    if(sz(v) > 1) total += extra(v[1].first); 
    if(sz(v) > 2) total += extra(v[2].first); 
    return total ; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    vi r; 
    rep(i,0,3) { 
        int n; cin >> n; 
        vii v; 
        rep(j,0,n) { 
            string foo; cin >> foo; 
            int probs, place; 
            cin >> probs >> place; 
            v.emplace_back(place, probs); 
        }
        r.push_back(solve(v)); 
    }
    cout << r[0] * 4 + r[1] * 3 + r[2] * 2 << "\n"; 
}

