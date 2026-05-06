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

struct Z { 
	ll val; 
	int i; 
	Z(ll val, int i) : val(val), i(i) { }
	bool operator<(Z rhs) const { return tie(val, i) < tie(rhs.val, rhs.i); }
	bool operator==(Z rhs) const { return tie(val, i) == tie(rhs.val, rhs.i); }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    vi a(n); rep(i,0,n) cin >> a[i]; 
    sort(all(a)) ; 
    vl d(n - 1); 
    rep(i,0,sz(d)) d[i] = a[i + 1] - a[i]; 

	set<Z> ss; 
	vi L(sz(d)), R(sz(d));
	rep(i,0,sz(d)) { 
		ss.emplace(d[i], i); 
		L[i] = i - 1; 
		R[i] = (i + 1 == sz(d) ? -1 : i + 1); 
	}

	ll total = 0; 
	set<int> alive; rep(i,0,sz(d)) alive.insert(i); 
	auto del = [&](int i) { 
		ss.erase({d[i], i}); 
		alive.erase(i); 
		if(L[i] != -1) R[L[i]] = R[i]; 
		if(R[i] != -1) L[R[i]] = L[i]; 
	};

	rep(i,0,n/2) {
		auto [val, pos] = *ss.begin(); ss.erase(ss.begin()); 
		total += val ; 
		if(L[pos] == -1) {  
			if(R[pos] != -1) { 
				L[R[pos]] = -1; 
				del(R[pos]);   
			} 
		}else if(R[pos] == -1) { 
			if(L[pos] != -1) { 
				R[L[pos]] = -1; 
				del(L[pos]);  
			} 
		}else{ 
			int l = L[pos], r = R[pos]; 
			del(l); 
			del(r);   
			d[pos] = d[l] + d[r] - val; 
			ss.emplace(d[pos], pos); 
		}
		cout << total << " "; 
	}
	cout << "\n"; 
}
