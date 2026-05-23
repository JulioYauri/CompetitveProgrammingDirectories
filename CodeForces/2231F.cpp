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

bool is_sq(int x) { 
    int sq = max(0, int(sqrt(x)) - 3); 
    while(sq * sq < x) sq++; 
    return sq * sq == x; 
}

void solve() {
    int n, qq; cin >> n >> qq; 
    vector<vii> d2(n * 2 + 10); 
    vi sq; for(int i = 1; i * i <= n; i++) sq.push_back(i * i); 
    rep(i,0,sz(sq)) rep(j,i,sz(sq)) { 
        d2[sq[i] + sq[j]].emplace_back(sq[i], sq[j]);  
    } 
    auto test = [&](int src, int step1, int step2) { 
        src += step1 ; 
        if(src <= 0 || src > n) return false; 
        src += step2; 
        return src > 0 && src <= n; 
    }; 
    while(qq--) { 
        int a, b; cin >> a >> b; 
        if(is_sq(b - a)) { 
            cout << "1\n"; 
            continue; 
        }   
        bool ok = false; 
        for(int c = 1; c * c <= n; c++) { 
            if(a - c * c >= 1 && is_sq(b - (a - c * c))) { 
                ok = true; break; 
            }
            if(b + c * c <= n && is_sq(b + c * c - a)) { 
                ok = true; break; 
            }
            if(a + c * c <= n && is_sq(abs(b - (a + c * c)))) { 
                ok = true; break; 
            }
        }
        if(ok) { 
            cout << "2\n"; 
            continue; 
        }
        for(int c = 1; c * c <= n; c++) { 
            int g1 = b - a - c * c; 
            if(g1 > 0 && g1 < sz(d2) && sz(d2[g1])) { 
                ok = true; break ;
            }
            // retrocedo c * c, avanzo p + q
            if(b - a + c * c < sz(d2)) { 
                for(auto [p, q] : d2[b - a + c * c]) { 
                    if(a - c * c > 0) { 
                        ok = true; 
                        break; 
                    }
                    if(test(a,p,-c*c) || test(a,q,p)  || test(a,q,-c*c)) { 
                        ok = true; 
                        break; 
                    } 
                }
            }
            // avanzo c * c, retrocedo p + q (-p-q)
            if(a + c * c - b > 0 && a + c * c - b < sz(d2)) { 
                for(auto [p, q] : d2[a + c * c - b]) { 
                    if(a + c * c <= n) { 
                        ok = true; 
                        break; 
                    }
                    if(test(a,-p,-q) || test(a,-p,c*c) || test(a,-q,c*c)) { 
                        ok = true; 
                        break; 
                    }
                }
            }
            if(ok) break; 
        }
        cout << (ok ? 3 : 4) << "\n"; 
    }
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();

}
