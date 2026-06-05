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

int ask(int l, int r) { 
    cout << "? " << r - l + 1 << " "; 
    rep(i,l,r+1) cout << i << " "; cout << endl ;
    int q; cin >> q; 
    return q; 
}

void solve() {
    int n; cin >> n; 
    n = 2 * n + 1; 
    int first_occ = -1; 
    { 
        int lo = 1, hi = n + 1; 
        while(hi - lo > 1) { 
            int mi = lo + hi >> 1; 
            int have = ask(mi, n), len = n - mi + 1; 
            if((len - have) % 2 == 0) hi = mi; 
            else lo = mi; 
        }
        first_occ = lo; 
    }
    int last_occ = -1; 
    { 
        int lo = 0, hi = n; 
        while(hi - lo > 1) { 
            int mi = lo + hi >> 1; 
            int have = ask(1, mi), len = mi; 
            if((len - have) % 2 == 0) lo = mi; 
            else hi = mi; 
        }
        last_occ = hi; 
    }
    int mid_occ = -1 ; 
    { 
        int lo = first_occ, hi = last_occ; 
        while(hi - lo > 1) { 
            int mi = lo + hi >> 1; 
            int with = ask(first_occ, mi), without = ask(first_occ + 1, mi); 
            if(with == without + 1) lo = mi; 
            else hi = mi; 
        }
        mid_occ = hi; 
    }
    cout << "! " << first_occ << " " << mid_occ << " " << last_occ << endl; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
