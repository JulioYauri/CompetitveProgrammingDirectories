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

const int N = 3000 + 10; 
const int inf = 1000000; 
int memo[N][3]; 
bool vis[N][3]; 
vi vals = {1, 11, 111, 1111};

tuple<int,int,int,int> from[N][3]; 
void update(int n, int last, int left_val, int left_sgn, int right_val, int right_sgn) { 
    from[n][last] = tie(left_val, left_sgn, right_val, right_sgn); 
}

int dp(int n, int last) {
    int &h = memo[n][last]; 
    if(vis[n][last]) return h;
    rep(left_sgn,0,3) { 
        rep(right_sgn,0,3) { 
            rep(left_val,1,n) { 
                if(last == 1) { //  +  
                    int total = dp(left_val, left_sgn) + 1 + dp(n - left_val, right_sgn); 
                    if(total < h) update(n, last, left_val, left_sgn, n - left_val, right_sgn), h = total; 
                }else{  
                    if(n % left_val != 0 || left_val == 1) continue; 
                    int total = dp(left_val, left_sgn) + 1 + dp(n / left_val, right_sgn); 
                    total += (left_sgn == 1 ? 2 : 0); 
                    total += (right_sgn == 1 ? 2 : 0);
                    if(total < h) update(n, last, left_val, left_sgn, n / left_val, right_sgn), h = total; 
                }
            }
        }
    }
    vis[n][last] = true;  
    return h;
}           

string ans; 
void dfs(int n, int last) { 
    if(last == 0) { 
        ans += (to_string(n)); 
        return ;
    }
    auto [left_val, left_sgn, right_val, right_sgn] = from[n][last]; 
    if(last == 1) { 
        dfs(left_val, left_sgn); 
        ans.push_back('+'); 
        dfs(right_val, right_sgn); 
    }else{ 
        if(left_sgn == 1) ans.push_back('('); 
        dfs(left_val, left_sgn); 
        if(left_sgn == 1) ans.push_back(')'); 
        ans.push_back('*'); 
        if(right_sgn == 1) ans.push_back('('); 
        dfs(right_val, right_sgn); 
        if(right_sgn == 1) ans.push_back(')'); 
    }
}   

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    rep(i,0,n+1) rep(j,0,3) memo[i][j] = inf; 
    int len = inf, last_sgn = -1; 
    rep(i,0,n+1) vis[i][0] = true; 
    rep(i,0,4) { 
        memo[vals[i]][0] = i + 1; 
        rep(j,0,3) vis[vals[i]][j] = true; 
    } 
    rep(sg,0,3) { 
        int cur = dp(n, sg); 
        if(cur < len) { 
            len = cur; 
            last_sgn = sg; 
        }
    }
    dfs(n, last_sgn); 
    cout << ans << "\n"; 
}  
