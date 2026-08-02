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

class Solution {
public:
    vector<int> countTasks(vector<int>& tasks, vector<int>& shifts) {
        int n = tasks.size(), m = shifts.size(); 
        vector<long long> pref(n); 
        for(int i = 0; i < n; i++) pref[i] = tasks[i]; 
        for(int i = 1; i < n; i++) pref[i] += pref[i - 1] ; 
        
        auto sum = [&](int l, int r) {
            if(l > r) return 0LL; 
            if(l == 0) return pref[r]; 
            return pref[r] - pref[l - 1]; 
        };

        int cur_task = 0; 
        long long done = 0; 
        vector<int> ans(m); 
        for(int i = 0; i < m; i++) {
            // cerr << "i: " << i << "\n"; 
            long long remaining = tasks[cur_task] - done; 
            if(remaining > shifts[i]) {
                done += shifts[i]; 
                ans[i] = n - cur_task; 
            }else{
                shifts[i] -= remaining; 
                cur_task++;
                // cerr << "shifts[i] : " << shifts[i] << "\n"; 
                if(cur_task == n) {
                    ans[i] = 0; 
                    done = 0; 
                    cur_task = 0; 
                    continue; 
                }
                
                done = 0; 
                int lo = cur_task - 1, hi = n; 
                while(hi - lo > 1) {
                    int mi = (lo + hi) / 2; 
                    if(shifts[i] >= sum(cur_task, mi)) lo = mi; 
                    else hi = mi; 
                }
                // cerr << "lo, hi: " << lo << " " << hi << "\n";
                // lo apunta al ultimo >=, hi el primero q no termine 
                if(lo == cur_task - 1) {
                    done = shifts[i]; 
                    ans[i] = n - cur_task; 
                }else if(hi == n) {
                    done = 0; 
                    cur_task = 0; 
                    ans[i] = 0; 
                }else{
                    done = shifts[i] - sum(cur_task, lo); 
                    cur_task = hi; 
                    ans[i] = n - cur_task ; 
                }
            }
        }
        return ans; 
    }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	

    Solution solver; 
    vi tasks = {1, 4, 4} ; 
    vi shifts = {9, 1, 4} ;
    
    // tasks = {2,3,4}, shifts = {20,4,5};
    // tasks = {4, 2}, shifts = {3, 6, 1};
    
    auto sol = solver.countTasks(tasks, shifts);
    for(auto i : sol) cerr << i << " "; cerr << "\n"; 
}
