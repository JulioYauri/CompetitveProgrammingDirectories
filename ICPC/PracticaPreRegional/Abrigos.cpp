#include<bits/stdc++.h>
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define sz(x) (int)(x.size())

using namespace std;
using ll = long long;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vii; 

const double eps = 1e-10; 

void solve() { 
    int n, qq; cin >> n >> qq; 
    vector<double> v(n); 
    rep(i,0,n) { 
        int x; cin >> x;
        v[i] = x; 
    } 
    sort(all(v)); 
    while(qq--) { 
        int k, r;
        cin >> k >> r; 
        vector<double> pos(r); 
        rep(i,0,r) { 
            int x; cin >> x; 
            pos[i] = x; 
        } 
        sort(all(pos)); 
        double lo = 0, hi = 3e8 + 10; 
        int its = 6;  
        rep(it,0,100) {
            double mi = (lo + hi) / 2.0; 
            double last_x; 
            bool first_done = false; 
            int total = 0, cur = 0;
            rep(i,0,n) { 
                if(i > 0 && abs(v[i] - v[i - 1]) < 1e-6) { 
                    continue; 
                }
                while(cur < sz(pos) && pos[cur] < v[i]) cur++; 
                if(cur < sz(pos) && pos[cur] < v[i] + mi + eps)  { 
                    continue; 
                }
                if(cur - 1 >= 0 && v[i] < pos[cur - 1] + mi + eps) { 
                    continue; 
                }
                if(first_done) { 
                    if(last_x > v[i] && v[i] + mi + eps > last_x) { 
                        continue; 
                    }
                    if(last_x < v[i] && last_x + mi + eps > v[i]) { 
                        continue; 
                    }
                    total++; 
                    last_x = v[i] + mi; 
                }else{ 
                    total++; 
                    last_x = v[i] + mi; 
                    first_done = true; 
                }
            }
            if(total > k - r) lo = mi; 
            else hi = mi; 
        }
        cout << lo << " "; 
    }
    cout << "\n"; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(3); 
    int tt; cin >> tt; 
    while(tt--) solve(); 

}