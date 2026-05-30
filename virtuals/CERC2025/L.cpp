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

    vector<pair<string, int> > v(3); 
    rep(i,0,3) { 
        cin >> v[i].first; 
        v[i].second = i + 1; 
    }

    sort(all(v)) ; 
    do { 
        string cur = ""; 
        vi who ; 
        for(auto [s, i] : v) { 
            cur += s; 
            who.push_back(i); 
            if(cur == "cerc") { 
                cout << "YES\n"; 
                cout << sz(who) << "\n"; 
                for(int x : who) cout << x << " "; cout << "\n"; 
                return 0;
            }
        }
    }while(next_permutation(all(v))); 
    cout << "NO\n"; 
}   