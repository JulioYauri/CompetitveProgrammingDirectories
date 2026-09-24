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
    int n; cin >> n; 
    map<int, vector<string>> mp; 

    rep(i,0,n) { 
        string s(n, '0'); 
        s[i] = '1'; 
        int total = 0; 
        rep(l,0,n) { 
            rep(r,l,n) { 
                int odd = 0, even = 0; 
                if(i >= l && i <= r) { 
                        if(i % 2) odd ++; 
                        else even ++; 
                    }
                if(abs(odd - even) % 3 == 0) total++; 
            }
        }
        mp[total].push_back(s);
    }

    rep(i,0,n) { 
        rep(j,i+1,n) { 
            string s(n, '0'); 
            s[i] = s[j] = '1'; 
            int total = 0; 
            rep(l,0,n) { 
                rep(r,l,n) { 
                    int odd = 0, even = 0; 
                    if(i >= l && i <= r) { 
                        if(i % 2) odd++; 
                        else even++; 
                    }
                    if(j >= l && j <= r) { 
                        if(j % 2) odd++; 
                        else even++; 
                    }
                    if(abs(odd - even) % 3 == 0) total++; 
                }
            }
            mp[total].push_back(s); 
        }
    }

    rep(i,0,n) { 
        rep(j,i+1,n) { 
            rep(k,j+1,n) { 
                string s(n, '0'); 
                s[i] = s[j] = s[k] = '1'; 
                int total = 0; 
                rep(l,0,n) { 
                    rep(r,l,n) { 
                        int odd = 0, even = 0; 
                        if(i >= l && i <= r) { 
                            if(i % 2) odd++; 
                            else even++; 
                        }
                        if(j >= l && j <= r) { 
                            if(j % 2) odd++; 
                            else even++; 
                        }
                        if(k >= l && k <= r) { 
                            if(k % 2) odd++; 
                            else even++; 
                        }
                        if(abs(odd - even) % 3 == 0) total++; 
                    }
                }
                mp[total].push_back(s); 
            }
        }
    }
    cerr << "n: " << n << "\n";
    auto [f, s] = *mp.begin(); 
    cerr << f << " \n " ; 
    for(auto ss : s) { 
        if(ss[0] == '1') { 
            // cerr << ss << "\n" ;  
            vi pos; 
            rep(i,0,n) { 
                if(ss[i] == '1') pos.push_back(i); 
            }
            rep(i,1,sz(pos)) cerr << pos[i] - pos[i - 1] - 1 << " " ; 
            cerr << n - pos.back() - 1 << "\n"; 
        }
    } 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
