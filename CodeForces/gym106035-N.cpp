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

const int N = 2000 * 2000 + 4; 
const int S = 27; 
int t[N][S], out[N];
bool ex[N];  
int ct = 0; 

void add(const string & s) { 
    int node = 0; 
    for(char c : s) { 
        int x = c - 'a'; 
        if(!t[node][x]) t[node][x] = ++ct, out[node]++; 
        node = t[node][x]; 
    }    
    ex[node] = true; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    string first; 
    rep(i,0,n) { 
        string s; cin >> s; 
        if(first.empty()) first = s; 
        add(s); 
    }

    int node = 0, pos = 0, ans = 0; 
    while(pos < sz(first)) { 
        if(out[node] == 1) { 
            if(ex[node]) { 
                ans++; 
                node = t[node][first[pos] - 'a']; 
                pos++; 
                continue; 
            }
            while(pos < sz(first) && out[node] == 1 && !ex[node]) { 
                int ch = first[pos] - 'a'; 
                node = t[node][ch]; 
                pos++; 
            }
            ans++; 
        }else{ 
            ans++; 
            node = t[node][first[pos] - 'a']; 
            pos++; 
        }
    }
    cout << ans << "\n"; 
}

