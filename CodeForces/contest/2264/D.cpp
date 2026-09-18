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

string brute(int n) { 
    int mn = 10000000;
    string ans;  
    string s(n, '0'); 
    rep(i,0,n) { 
        fill(all(s), '0'); 
        s[i] = '1'; 
        int total = 0; 
        rep(l,0,n) { 
            rep(r,l,n) { 
                int odd = 0, even = 0; 
                rep(ii,l,r+1) { 
                    if(i >= l && i <= r) { 
                        if(i % 2) odd ++; 
                        else even ++; 
                    }
                }
                if(abs(odd - even) % 3 == 0) total++; 
            }
        }
        if(total < mn) { 
            mn = total; 
            ans = s; 
        }
    }
    rep(i,0,n) { 
        rep(j,i+1,n) { 
            fill(all(s), '0'); 
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
            if(total < mn) { 
                mn = total; 
                ans = s; 
            } 
        }
    }

    rep(i,0,n) { 
        rep(j,i+1,n) { 
            rep(k,j+1,n) {         
                fill(all(s), '0'); 
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
                if(total < mn) { 
                    mn = total; 
                    ans = s; 
                } 
            }
        }
    }
    return ans; 
}

void solve() {
    int n; cin >> n; 
    if(n < 8) { 
        cout << brute(n) << "\n"; 
        return; 
    }
    int c6 = n / 6 * 6 ; 
    int a, b, c; 
    a = b = c = c6 / 3 - 1; 
    if(n % 6 == 0) { 

    }else if(n % 6 == 1) { 
        a++; 
    }else if(n % 6 == 2) { 
        a++, c++; 
    }else if(n % 6 == 3) { 
        a++, c += 2; 
    }else if(n % 6 == 4) { 
        a += 2, b += 2; 
    }else if(n % 6 == 5) { 
        a += 2, b += 2, c ++; 
    }
    string ans(1, '1'); 
    ans += string(a, '0'); 
    ans.push_back('1'); 
    ans += string(b, '0'); 
    ans.push_back('1'); 
    ans += string(c, '0'); 
    cout << ans << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
