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
const double pi = acos(-1); 
using P = Point<ll> ;
using pt = Point<double> ;
bool circleInter(pt a,pt b,double r1,double r2,pair<pt,pt>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	pt vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	pt mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

struct Seg { 
    ll o, h; 
    double l, r, area, total_area = 0; 
    Seg(ll o, ll h, double l, double r, double area) : o(o), h(h), l(l), r(r), area(area) { }
    bool contains(Seg &rhs) { return o - h <= rhs.o - rhs.h; }
    bool inter(Seg &rhs) { 
        ll X = (o - rhs.o), Y = rhs.h; 
        if(h * h - X * X <= Y * Y) { // columna
            l = rhs.r; 
            return true; 
        }else{ // curva  
            pair<pt,pt> * foo = new pair<pt,pt>; 
            pt my_c(o, 0), his_c(rhs.o, 0); 
            assert(circleInter(my_c, his_c, h, rhs.h, foo)); 
            pt wh = foo -> first; 
            if(wh.y < 0) wh = foo -> second; 
            if(wh.x < rhs.l) return false; 
            rhs.r = wh.x; 
            l = wh.x; 
            return true; 
        }
    }
    double recalc() { 
        double big_angle = acos(double(o - r) / h); 
        double small_angle = acos(double(o - l) / h);
        double l_h = sqrtl(h * h - (o - l) * (o - l)) ;  
        double S = small_angle * h * h / 2 - (o - l) * l_h / 2; 
        S = big_angle * h * h / 2 - S ; 
        double r_h = sqrtl(h * h - (o - r) * (o - r)) ; 
        S -= r_h * (o - r) / 2; 
        return area = S; 
    }
};



signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cout << fixed << setprecision(12) ; 
    int n; cin >> n; 
    vector<Seg> st; 
    rep(i,0,n) { 
        ll x, height; cin >> x >> height;
        Seg cur(x, height, x - height, x, 0); 
        double &total = cur.total_area; 
        while(sz(st)) { 
            if(cur.contains(st.back())) {
                st.pop_back(); 
                continue; 
            } 
            if(x - height >= st.back().o) break; 
            if(!cur.inter(st.back())) { 
                st.pop_back(); 
                continue; 
            }
            double &his = st.back().total_area; 
            his -= st.back().area; 
            his += st.back().recalc(); 
            total = his; 
            break; 
        }
        st.push_back(cur); 
        total += cur.recalc(); 
        cout << total << "\n"; 
    }
}
