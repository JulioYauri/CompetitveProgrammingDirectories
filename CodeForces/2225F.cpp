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


struct SuffixArray {
	vi sa, lcp;
    string s; 
	SuffixArray(string& s_, int lim=256) : s(s_) { // or basic_string<int>
        int n = s.size() + 1, k = 0, a, b;
		vi x(s.begin(), s.end()), y(n), ws(max(n, lim)), rank(n);
		x.push_back(0), sa = lcp = y, iota(sa.begin(), sa.end(), 0);
        s.push_back('$');
		for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(y.begin(), y.end(), n - j);
			for(int i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(ws.begin(), ws.end(), 0);
			for(int i = 0; i < n; i++) ws[x[i]]++;
			for(int i = 1; i < lim; i++) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			for(int i = 1; i < n; i++) {
                a = sa[i - 1];
                b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
		}
		for(int i = 1; i < n; i++) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);

	}
};

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};


void solve() {
    int n, len, k; cin >> n >> len >> k ; 
    string s; cin >> s; 
    if(1LL * len * k > n) { 
        cout << "NO\n"; return; 
    }
    if(k == 1) { 
        cout << "YES\n" << s << "\n"; 
        return; 
    }

    SuffixArray SA(s); 
    auto &sa = SA.sa, &lcp = SA.lcp; 
    vi pos_in_sa(n + 1); 
    rep(i,0,n+1) pos_in_sa[sa[i]] = i; 
    RMQ rmq(lcp); 

    auto is_greater = [&](int l1, int r1, int l2, int r2) -> bool { 
        int p1 = pos_in_sa[l1], p2 = pos_in_sa[l2]; 
        if(p1 > p2) swap(p1, p2); 
        int max_common = rmq.query(p1 + 1, p2 + 1); 
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1; 
        if(len1 == len2) { 
            if(max_common >= len1) return false; 
            return s[l1 + max_common] > s[l2 + max_common]; 
        }
        if(len1 > len2) { 
            max_common = min(max_common, len2); 
            if(max_common == len2) return true; 
            return s[l1 + max_common] > s[l2 + max_common]; 
        }else{ 
            max_common = min(max_common, len1); 
            if(max_common == len1) return false; 
            return s[l1 + max_common] > s[l2 + max_common]; 
        }
    };

    int l = 0, r = (n - 1) - len * (k - 1);
    rep(cl,len,n-len+1) { 
        int pref = cl / len, need = max(k - 1 - pref, 0); 
        int cr = (n - 1) - len * need; 
        if(cr - cl + 1 >= len && is_greater(cl, cr, l, r)){ 
            l = cl; 
            r = cr; 
        }
    }
    cout << "YES\n"; 
    rep(i,l,r+1) cout << s[i]; 
    cout << "\n"; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt; 
	while(tt--) solve();
}
