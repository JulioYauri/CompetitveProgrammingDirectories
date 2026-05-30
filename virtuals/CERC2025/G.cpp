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

    int p; cin >> p;
    vii a;
    a.emplace_back(50, 1);
    a.emplace_back(25, 0);
    rep(i, 1, 21) a.emplace_back(i, 0);
    rep(i, 1, 21) a.emplace_back(2 * i, 1);
    rep(i, 1, 21) a.emplace_back(3 * i, 0);

    for(auto [x, f] : a) if(x == p && f){
        cout << "YES\n";
        cout << "1\n";
        cout << x << "\n";
        return 0;
    }

    for(auto [x1, f1] : a){
        for(auto [x2, f2] : a){
            if(x1 + x2 == p && f2){
                cout << "YES\n";
                cout << "2\n";
                cout << x1 << " " << x2 << "\n";
                return 0;
            }
        }
    }

    for(auto [x1, f1] : a){
        for(auto [x2, f2] : a){
            for(auto [x3, f3] : a){
                if(x1 + x2 + x3 == p && f3){
                    cout << "YES\n";
                    cout << "3\n";
                    cout << x1 << " " << x2 << " " << x3 << "\n";
                    return 0;
                }
            }
        }
    }

    cout << "NO\n";
}   