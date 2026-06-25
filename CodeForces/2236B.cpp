#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n, k; cin >> n >> k ;
    string s; cin >> s; 
    for(int i = 0; i + k < n; i++) { 
        if(s[i] == '1') { 
            s[i] ^= 1; 
            s[i + k] ^= 1; 
        }
    }   
    if(count(s.begin(), s.end(), '1')) cout << "NO\n"; 
    else cout << "YES\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
