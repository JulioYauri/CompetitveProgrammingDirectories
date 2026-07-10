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

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T> 
struct Point{
    typedef Point P ;  
    T x, y; 
    explicit Point(T x=0, T y=0) : x(x), y(y) { }
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(double(dist2())); }
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    P rotate(double a) const { // en radianes  
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); 
    }
    friend ostream& operator<<(ostream &os, P p) { 
        return os << "(" << p.x << "," << p.y << ")"; 
    }
};

using P = Point<ll>; 

// retorna el convex_hull en clock-wise
vector<P> convex_hull(vector<P> points) {
    int n = sz(points);
    sort(all(points), [](P p1, P p2){
        return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
    });
    vector<P> hull; 
    rep(it,0,2) { // la primera halla el hull superior
        int S = sz(hull);
        rep(i,0,n) {
            while(sz(hull) >= S + 2) {
                P A = hull.end()[-2]; 
                P B = hull.end()[-1]; 
                // el <= incluye puntos colineales 
                if(A.cross(B, points[i]) < 0) break; 
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        hull.pop_back(); // derecha e izquierda se repiten 
        reverse(all(points));
    }
    return hull; 
}


using pt = Point<double>; 
vector<pt> circleLine(pt c, double r, pt a, pt b) {
	pt ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	pt h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

template<class P>
double lineDist(P a, P b, P p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}

pt to_d(P p) { return pt(p.x, p.y); }


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; 
    ll r; 
    cin >> n >> r; 
    cout << fixed << setprecision(15); 

    vector<P> pts(n); 
    rep(i,0,n) cin >> pts[i].x >> pts[i].y; 

    if(n == 1) { 
        cout << 0.0 << "\n"; return 0; 
    }

    pts = convex_hull(pts); 
    reverse(pts.begin() + 1, pts.end()); 
    pt ori(0,0); 
    if(sz(pts) == 2) { 
        pt seg = to_d(pts[0] - pts[1]).perp(); 
        auto inters = circleLine(ori, r, ori, ori + seg); 
        double mx = 0; 
        for(auto p : inters) mx = max(mx, lineDist(to_d(pts[0]), to_d(pts[1]), p)); 
        double area = (pts[0] - pts[1]).dist() * mx / 2.0 ; 
        cout << area << "\n"; 
        return 0; 
    }

    n = sz(pts); 
    vector<pt> poly(n); 
    rep(i,0,n) poly[i] = to_d(pts[i]); 
    double extra = 0; 
    rep(i,0,n) { 
        double quito = 0; 
        rep(j,1,n) { 
            int i2 = (i + j >= n ? i + j - n : i + j); 
            pt seg = (poly[i2] - poly[i]).perp(); 
            auto inters = circleLine(ori, r, ori, ori + seg); 
            for(auto p : inters) { 
                if(poly[i].cross(poly[i2], p) < 1e-8) { 
                    double area = poly[i].cross(p, poly[i2]) / 2.0; 
                    if(area - quito > extra) extra = area - quito ; 
                }
            }    
            quito += (poly[i].cross(poly[i2], poly[(i2 + 1) % n])) / 2.0; 
        }
    }
    double area = 0 ; 
    rep(i,1,n-1) area += poly[0].cross(poly[i], poly[i + 1]); 
    area /= 2; 
    cout << area + extra << "\n"; 
}
