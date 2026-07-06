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

int LIM = 35000, qs = 0; 
int qsiz = 0; 
int add(int a) { 
    cout << "+ " << a << endl; 
    qsiz++; 
    qs++; 
    assert(qs < LIM); 
    int x; cin >> x; 
    return x; 
}
int rem() { 
    cout << "-" << endl; 
    qsiz--;
    qs++; 
    assert(qs < LIM);  
    int x; cin >> x; 
    return x; 
}

const int N = 500 + 5; 
int group[N];
vi ans[N]; 
vi vals; 
void solve(int l, int r, const vi& reps) { 
    int n = r - l + 1; 
    if(n == 0) return; 
    if(n == 1) { // l = r 
        ans[reps[0]].push_back(vals[l]); 
        return; 
    }
    int m = l + r >> 1;
    int cur_diffs = 0; 
    rep(i,l,m+1) cur_diffs = add(vals[i]); 
    vi L_reps; 
    for(int x : reps) {     
        int new_diffs = add(x); 
        if(new_diffs != cur_diffs + 1) L_reps.push_back(x);
        cur_diffs = new_diffs; 
    }
    while(qsiz > 0) rem(); 

    cur_diffs = 0; 
    rep(i,m+1,r+1) cur_diffs = add(vals[i]); 
    vi R_reps; 
    for(int x : reps) { 
        int new_diffs = add(x); 
        if(new_diffs != cur_diffs + 1)  R_reps.push_back(x); 
        cur_diffs = new_diffs ; 
    }
    while(qsiz > 0) rem(); 

    solve(l, m, L_reps); 
    solve(m + 1, r, R_reps); 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    vi reps;
    int last_diffs = 0;  
    rep(i,1,n+1) { 
        int cur_diffs = add(i); 
        if(cur_diffs == last_diffs + 1) { 
            reps.push_back(i); 
            ans[i].push_back(i);  
        } else vals.push_back(i); 
        last_diffs = cur_diffs; 
    }
    while(qsiz > 0) rem(); 

    solve(0, sz(vals) - 1, reps); 
    
    cout << "! " << sz(reps) << endl ; 
    int cnt = 0 ; 
    for(int x : reps) { 
        cout << sz(ans[x]) << " "; 
        for(int y : ans[x]) cout << y << " ", cnt++ ; 
        cout << endl; 
    }
    assert(cnt == n); 
}
