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

struct Line {
	mutable double k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(double x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static constexpr double inf = 1e40 ; 
	double div(double a, double b) { return a / b; }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(double k, double m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	double query(double x) {
        if(empty()) return -inf; 
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

struct LCMin{ 
    LineContainer lc; 
    void add(double m, double b) { lc.add(-m, -b) ; }
    double query(double x) { return -lc.query(x); }
};

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    LCMin min_x, min_y; 
    LineContainer max_x, max_y; 
    const double INF = 1e40  ; 
    double max_const_x = -INF, min_const_x = INF, max_const_y = -INF, min_const_y = INF; 
    rep(i,0,n) { 
        int x, y, vx, vy; cin >> x >> y >> vx >> vy; 
        if(vx == 0) { 
            min_const_x = min(min_const_x, double(x)); 
            max_const_x = max(max_const_x, double(x)); 
        }else{ 
            max_x.add(vx, x); 
            min_x.add(vx, x); 
        }   
        if(vy == 0) { 
            min_const_y = min(min_const_y, double(y));
            max_const_y = max(max_const_y, double(y)); 
        }else{ 
            max_y.add(vy, y); 
            min_y.add(vy, y); 
        }
    }

    // cerr << fixed << setprecision(3); 
    auto test = [&](double x) { 
        double X = max(max_x.query(x), max_const_x) - min(min_x.query(x), min_const_x); 
        double Y = max(max_y.query(x), max_const_y) - min(min_y.query(x), min_const_y); 
        return X * Y; 
    };  

    double ans = test(0);
    for(auto &lc : { min_x.lc, min_y.lc, max_x, max_y }) { 
        for(auto &l : lc) { 
            if(l.p >= 0) ans = min(ans, test(l.p)); 
        }
    }
    cout << fixed << setprecision(12) << ans << "\n"; 

}
