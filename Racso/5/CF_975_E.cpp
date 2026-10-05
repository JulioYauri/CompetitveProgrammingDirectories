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

using D = long double; 
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
    D angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    P rotate(D a) const { // en radianes  
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); 
    }
    friend ostream& operator<<(ostream &os, P p) { 
        return os << "(" << p.x << "," << p.y << ")"; 
    }
};

using P = Point<ll>; 
using pt = Point<D>; 
pt pd(P p) { return pt(p.x, p.y); }

pt polygonCenter(const vector<pt>& v) {
	pt res(0, 0); D A = 0;
	for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++) {
		res = res + (v[i] + v[j]) * D(v[j].cross(v[i]));
		A += v[j].cross(v[i]);
	}
	return res / A / 3;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); 
    cout << fixed << setprecision(10) ; 
    cerr << fixed << setprecision(5) ; 
	
    int n, qq; cin >> n >> qq; 
    vector<P> poly_(n); 
    rep(i,0,n) cin >> poly_[i].x >> poly_[i].y; 
    P first = poly_[0] ; 
    rep(i,0,n) poly_[i] = poly_[i] - first; 

    vector<pt> poly(n); 
    rep(i,0,n) poly[i] = pd(poly_[i]); 
    pt cen = polygonCenter(poly); 
    for(auto &p : poly) p = p - cen; 

    vector<pair<int,pt>> pts; 
    pts.emplace_back(0, (poly[0])); 
    pts.emplace_back(1, (poly[1])); 

    auto get_pos = [&](int idx) -> pt {
        auto [pin_id, pin] = pts[0]; 
        pt real_wh = pt(0,0) - (poly[pin_id]);    
        D ang = atan2(real_wh.cross(pt(0, -1)), real_wh.dot(pt(0, -1))); 
        
        pt real_vec = (poly[idx]) - (poly[pin_id]); 
        pt cur_vec = real_vec.rotate(ang); 
        return pin + cur_vec; 
    };

    bool move_done = false; 
    while(qq--) { 
        int tp; cin >> tp; 
        if(tp == 1) { 
            int f, t; 
            cin >> f >> t;    
            f--, t--; // quito de f y pongo en t 
            if(move_done) { 
                if(f == pts[0].first) { // nuevo pin  
                    swap(pts[0], pts[1]) ; 
                }
                auto new_t = get_pos(t); 
                pts[1] = { t, new_t } ; 
            }else{ 
                if(f == pts[0].first) { 
                    swap(pts[0], pts[1]); 
                }
                auto new_t = get_pos(t);
                pts[1] = { t, new_t } ; 
                move_done = true; 
            }
        }else { 
            int idx; cin >> idx; 
            idx--;
            if(move_done) { 
                pt ans = get_pos(idx) + cen + pd(first); 
                cout << ans.x << " " << ans.y << "\n"; 
            }else{ 
                pt ans = (poly[idx]) + cen + pd(first); 
                cout << ans.x << " " << ans.y << "\n"; 
            }
        }
    }

}
