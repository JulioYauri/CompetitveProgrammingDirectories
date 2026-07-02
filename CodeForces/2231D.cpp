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

const ll inf = 1'000'000'000'000LL; 

void solve() {
    int n; cin >> n; 
    string s; cin >> s; 
    vl a(n); rep(i,0,n) cin >> a[i]; 
    vl c(n); rep(i,0,n) cin >> c[i]; 

    if(!is_sorted(all(c))) { 
        cout << "No\n"; return; 
    }

    ll last_sum = 0; 
    for(int l = 0, r = 1; l < n; l = r) { 
        r = l + 1; 
        while(r < n && c[r] == c[l]) r++; 
        if(s[l] == '0') { 
            a[l] = c[l] - last_sum; 
            s[l] = '1'; 
        }else{ 
            if(last_sum + a[l] != c[l]) { 
                cout << "No\n"; return; 
            }
        }
        if(r < n) { 
            int missing = 0; 
            rep(i,l,r) missing += (s[i] == '0'); 
            if(missing == 0) { 
                bool ok = true; 
                rep(i,l,r) { 
                    last_sum += a[i]; 
                    if(last_sum > c[l]) { 
                        ok = false; 
                        break; 
                    }
                }
                if(s[r] == '1') { 
                    if(last_sum + a[r] != c[r]) ok = false; 
                }
                if(!ok) { 
                    cout << "No\n"; return; 
                }
            }else{ 
                if(s[r] == '1') { 
                    ll have = last_sum; 
                    rep(i,l,r) { 
                        if(s[i] == '1') have += a[i]; 
                    }
                    ll missing_sum = c[r] - a[r] - have; 
                    int last_missing = -1, first_missing = -1; 
                    rep(i,l,r) { 
                        if(s[i] == '0') { 
                            last_missing = i; 
                            if(first_missing == -1) first_missing = i; 
                        } 
                    }
                    bool ok = true; 
                    if(first_missing == last_missing) { 
                        a[first_missing] = missing_sum; 
                    }else{ 
                        a[first_missing] = -inf; 
                        a[last_missing] = inf + missing_sum; 
                    }
                    rep(i,l,r) { 
                        last_sum += a[i]; 
                        if(last_sum > c[l]) ok = false; 
                    }
                    if(!ok) { 
                        cout << "No\n"; return; 
                    }
                }else{ 
                    bool first_done = false; 
                    rep(i,l,r) { 
                        if(s[i] == '0') { 
                            if(first_done) a[i] = 0; 
                            else { 
                                a[i] = -inf; 
                                first_done = true; 
                            }
                        }
                        last_sum += a[i]; 
                        if(last_sum > c[l]) { 
                            cout << "No\n"; return; 
                        }
                    }
                }
            }
        }else{ 
            bool first_done = false; 
            rep(i,l,r) { 
                if(s[i] == '0') { 
                    if(first_done) a[i] = 0; 
                    else { 
                        a[i] = -inf; 
                        first_done = true; 
                    }
                }
                last_sum += a[i]; 
                if(last_sum > c[l]) { 
                    cout << "No\n"; return; 
                }
            }
        }
    }
    cout << "Yes\n"; 
    rep(i,0,n) cout << a[i] << " "; 
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
