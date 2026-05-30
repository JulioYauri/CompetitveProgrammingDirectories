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
    vi a(n);
    rep(i, 0, n) cin >> a[i];

    map<int, int> mp;
    rep(i, 0, n) mp[a[i]]++;

    int mn = *min_element(all(a));
    int mx = *max_element(all(a));

    int fmn = mp[mn];
    int fmx = mp[mx];

    int f5 = 0;
    for(auto [x, f] : mp){
        if(f > f5 && x != mn && x != mx) f5 = f;
        else if(f == f5 && x != mn && x != mx) f5 = f;
    }

    if (mx == 2*mn) {
        mp.erase(mp.find(mn));
        mp.erase(mp.find(mx));
    }

    vvi lines;
    while(sz(mp)){
        vi here;
        map<int, int> ret;
        for(auto [x, f] : mp){
            if(f > 1) ret[x] = f - 1;
            here.emplace_back(x);
        }
        mp = ret;
        lines.emplace_back(here);
    }


    if(mx == 2 * mn){
        vi response;
        // cerr << "caso doble\n";
        // cerr << "fmn " << fmn << " " << f5 << " " << fmx << " => ";
        if (fmn >= 1) {
            response.push_back(mn);
            fmn--;
        }

        bool last = false;
        if (fmx >= 1) last = true;
        fmx--;

        while (sz(lines) >= 2 && (fmn >= 1  || fmx >= 1)) {
            for (auto e : lines.back()) {
                response.push_back(e);
            }
            lines.pop_back();

            if (fmn >= 1) {
                response.push_back(mn);
                fmn--;
            } else {
                response.push_back(mx);
                fmx--;
            }
        }

        while (sz(lines) > 0) {
            for (auto e : lines.back()) response.push_back(e);
            lines.pop_back();
        }

        while (fmx >= 1) {
            response.push_back(mx);
            fmx--;
        }

        if (last) {
            response.push_back(mx);
        }

        reverse(all(response));
        while (fmn >= 1) {
            response.push_back(mn);
            fmn--;
        }
        reverse(all(response));

        int value = 0;
        int last2 = -10;
        for (auto e : response) {
            if (last2 >= e) value++;
            last2 = e;
        }

        cout << value << "\n";
        for (auto e : response) cout << e << " ";
    }else{
        cout << sz(lines) - 1 << "\n";
        for (auto& e : lines) {
            for (auto& ee : e) {
                cout << ee << " ";
            }
        }
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt; cin >> tt;
    while(tt--) solve();
}