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
    string smallestPalindrome(string s, int k) {
        int siz = s.size(); 
        string my_s(s.begin(), s.begin() + siz / 2); 
        sort(my_s.begin(), my_s.end()); 

        vector<int> cnt(26); 
        long long have = 1;
        int i, total;  
        for(i = int(my_s.size()) - 1, total = 1; i >= 0; i--, total++) { 
            int who = (my_s[i] - 'a'); 
            cnt[who]++;     
            have *= total; 
            have /= cnt[who]; 
            if(have >= k) break; 
        }
        if(have < k) return ""; 
        for(; i < int(my_s.size()); i++, total--) { 
            for(int place = 0; place < 26; place++) { 
                if(cnt[place] == 0) continue; 
                long long cur_count = have * cnt[place] / total; 
                if(cur_count < k) k-= cur_count; 
                else { 
                    my_s[i] = ('a' + place); 
                    have = have * cnt[place] / total ; 
                    cnt[place]--; 
                    break;
                }
            }
        }
        for(int i = 0, j = int(s.size()) - 1; i < int(my_s.size()); i++, j--) s[j] = my_s[i], s[i] = my_s[i]; 
        return s; 
    }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    Solution solver; 
    string s; cin >> s; 
    int k; cin >> k ;
    cout << solver.smallestPalindrome(s, k) << "\n"; 

}
