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

template<class T> 
struct Point { 
    typedef Point P ; 
    T x, y; 
    explicit Point(T x = 0, T y = 0) : x(x), y(y) { }
    P operator+(P p) const { return P(x+p.x, y+p.y) ; }
    P operator-(P p) const { return P(x-p.x, y-p.y) ; }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(dist2()); }
    P perp() const { return P(-y, x); }
};

using P = Point<double> ; 

double ccRadius(const P& A, const P& B, const P& C) { 
    return (B - A).dist() * (C - B).dist() * (A - C).dist() / 
            abs((B - A).cross(C - A)) / 2; 
}

P ccCenter(const P& A, const P& B, const P& C) { 
    P b = C - A, c = B - A; 
    return A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2; 
}

pair<P, double> mec(vector<P> ps) { 
    shuffle(all(ps), mt19937(time(0)));
    P o = ps[0]; 
    double r = 0, EPS = 1 + 1e-8; 
    rep(i,0,sz(ps)) if((o - ps[i]).dist() > r * EPS) { 
        o = ps[i], r = 0; 
        rep(j,0,i) if((o - ps[j]).dist() > r * EPS) { 
            o = (ps[i] + ps[j]) / 2; 
            r = (o - ps[i]).dist(); 
            rep(k,0,j) if((o - ps[k]).dist() > r * EPS) { 
                o = ccCenter(ps[i], ps[j], ps[k]) ; 
                r = (o - ps[i]).dist(); 
            }
        }
    }
    return {o, r}; 
}

void solve(int n) { 
    vector<P> ps(n); 
    rep(i,0,n) cin >> ps[i].x >> ps[i].y; 
    double rad; cin >> rad; 
    auto [pt, min_rad] = mec(ps); 
    if(min_rad <= rad) cout << "The polygon can be packed in the circle.\n";
    else cout << "There is no way of packing that polygon.\n"; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; 
    while(cin >> n) { 
        if(n == 0) return 0; 
        solve(n); 
    }
}
