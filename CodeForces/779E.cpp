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

int is_op(string& s) { 
    if(s == "XOR") return 1; 
    if(s == "AND") return 2; 
    if(s == "OR") return 3; 
    return 0; 
}

// string op(, int type) { 
//     string res(sz(a), '0') ; 
//     rep(i,0,)
// }

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m; cin >> n >> m; 
    map<string, int> id; id["?"] = -1; 
    vector<tuple<string, int, int> > value(n);  
    cin.ignore(); 
    rep(i,0,n) { 
        string line; getline(cin, line); 
        stringstream line_in(line); 
        string var, foo; line_in >> var >> foo; 
        id[var] = i;

        vector<string> vars; 
        while(line_in >> foo) vars.push_back(foo); 
        // for(auto s : vars) cerr << s << " " ; cerr << "\n"; 
        if(sz(vars) == 1) value[i] = {vars[0], -1, -1} ; 
        else value[i] = {vars[1], id[vars[0]], id[vars[2]]}; 
    }

    string ans_max, ans_min; 
    vi cur_val(n); 
    rep(bit,0,m) { 
        vi cnt; 
        rep(c,0,2) { 
            rep(i,0,n) { 
                auto [str, id1, id2] = value[i]; 
                int type = is_op(str); 
                if(type) { 
                    int l = (id1 == -1 ? c : cur_val[id1]); 
                    int r = (id2 == -1 ? c : cur_val[id2]); 
                    if(type == 1) cur_val[i] = (l ^ r); 
                    else if(type == 2) cur_val[i] = (l & r); 
                    else cur_val[i] = (l | r); 
                }else{ 
                    cur_val[i] = (str[bit] - '0') ; 
                }
            }
            cnt.push_back(accumulate(all(cur_val), 0)); 
        }
        if(cnt[0] < cnt[1]) { 
            ans_max.push_back('1'); 
            ans_min.push_back('0'); 
        }else if(cnt[0] > cnt[1]) { 
            ans_max.push_back('0'); 
            ans_min.push_back('1'); 
        }else { 
            ans_max.push_back('0'); 
            ans_min.push_back('0'); 
        }
    }
    cout << ans_min << "\n" << ans_max << "\n"; 
}
