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

void solve(){
    int n; cin >> n;
    vvi a(3, vi(2));
    rep(i, 0, 3){
        string s; cin >> s;
        int on = count(all(s), '1');
        int ze = count(all(s), '0');
        a[i][0] = ze;
        a[i][1] = on;
    }

    int mx = 0;
    rep(j, 0, 2){
        int mn = n;
        rep(i, 0, 3) mn = min(mn, a[i][j]);
        mx = max(mx, mn);
    }

    cout << mx << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt; cin >> tt;
    while(tt--) solve();
}