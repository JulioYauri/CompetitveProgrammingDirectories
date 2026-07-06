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

vector<string> ans; 
bool check(string num) { 
    int i = stoi(num); 
    return i >= 11 && i <= 19; 
}
string cur = "", ss = "19"; 
bool ok() { 
    return check(cur.substr(0,2)) && cur[2] == '9';
}
void dfs(const string &num, int pos_in_num, int available) { 
    // cerr << "cur: " << cur << "\n"; 
    // cerr << "    size: " << sz(cur) << "\n"; 
    if(sz(cur) >= 3) { 
        if(!ok()) return ; 
    }
    if(pos_in_num == sz(num) && available == 0) { 
        ans.push_back(cur); 
        return ;
    }
    if(pos_in_num < sz(num)) { 
        cur.push_back(num[pos_in_num]); 
        dfs(num, pos_in_num + 1, available) ; 
        cur.pop_back(); 
    }
    if(available > 0) { 
        for(char nxt : ss) { 
            cur.push_back(nxt) ;
            dfs(num, pos_in_num, available - 1); 
            cur.pop_back(); 
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s; cin >> s; 
    cerr << "sz(s) : " << sz(s) << "\n"; 
    int need = 11 - sz(s); 
    if(need < 0) { 
        cout << "0\n"; return 0; 
    }
    dfs(s, 0, need); 
    // cerr << "need: " << need << "\n"; 
    sort(all(ans)) ; 
    ans.erase(unique(all(ans)), ans.end()); 
    cout << sz(ans) << "\n"; 
    for(auto s : ans) cout << s << "\n"; 
}
