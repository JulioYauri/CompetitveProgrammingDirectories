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

const int NAX = 50; 
int memo[NAX][NAX]; 
int dp(int a, int b) { 
    int &h = memo[a][b]; 
    if(h != -1) return h; 
    bool losing_exists = false; 
    rep(i,1,a+1) { 
        int nxt_a = a - i; 
        int play = dp(min(nxt_a, b), max(nxt_a, b)); 
        if(play == 0) losing_exists = true; 
    }
    rep(i,1,b+1) { 
        int nxt_b = b - i; 
        int play = dp(min(nxt_b, a), max(nxt_b, a)); 
        if(play == 0) losing_exists = true; 
    }
    rep(i,1,min(a,b)+1) { 
        if(dp(a - i, b - i) == 0) losing_exists = true; 
    }
    return h = losing_exists; 
}

void brute(){ 
    memset(memo, -1, sizeof(memo)); 
    memo[0][0] = 0; 
    cerr << "lossss\n"; 
    rep(i,0,NAX) rep(j,i,NAX) { 
        if(dp(i, j) == 0) cerr << i << " " << j << "\n"; 
    }
}

const int N = 1000000 + 4;  
int a[N], by_dif[N]; 
bool vis[N]; 
const int inf = 1<<29; 
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    // brute(); 
    rep(i,0,N) a[i] = inf; 
    a[0] = 0; 
    vis[0] = true; 
    int dif = 1;
    by_dif[0] = 0;  
    vii losing_states; 
    rep(i,1,N) if(!vis[i]) { 
        vis[i] = true; 
        a[i] = i + dif; 
        if(i + dif < N) { 
            vis[i + dif] = true; 
            a[i + dif] = i; 
        } 
        losing_states.emplace_back(i, i + dif); 
        by_dif[dif] = i; 
        dif++; 
    }

    int x, y; 
    while(cin >> x >> y) { 
        if(x == 0 && y == 0) return 0; 
        if(a[x] == y || a[y] == x) { 
            cout << "0\n"; continue; 
        }
        cout << "1\n"; 
        { 
            int d = y - x; 
            int sol_x = by_dif[d], sol_y = sol_x + d; 
            if(sol_x < x && sol_y < y) { 
                cout << sol_x << " " << sol_y << "\n"; 
            }
        }
        if(a[x] < y) { 
            int p1 = x, p2 = a[x]; 
            if(p1 > p2) swap(p1, p2); 
            cout << p1 << " " << p2 << "\n"; 
        }else if(a[y] < x) { 
            int p1 = y, p2 = a[y];
            if(p1 > p2) swap(p1, p2); 
            cout << p1 << " " << p2 << "\n";  
        }
    }    
}
