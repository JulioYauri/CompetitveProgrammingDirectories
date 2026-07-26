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
    void rd() { cin >> x >> y; }
};


const double pi = acos(-1); 
using pt = Point<double>  ; 
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m; cin >> n >> m; 
    double r, a; cin >> r >> a; 
    a = pi * a / 180.0 ; 
    
    vector<pt> poly(n); rep(i,0,n) poly[i].rd(); 
    vector<pt> exh(m); rep(i,0,m) exh[i].rd(); 

    vector<double> ans(m + 1); 
    rep(i,0,n) { 
        pt from = poly[i], to = poly[(i + 1) % n], v = to - from; 
        vector<pair<double,int>> evs; 
        for(auto q : exh) { 
            pt p = q - from ; 
            double x = v.dot(p) / v.dist(); 
            double y = abs(v.cross(p)) / v.dist(); 
            double beg = 0, ending = v.dist(); 
            if(r < y) continue; 
            double ss = sqrt(r * r - y * y); 
            beg = max(beg, x - ss); 
            ending = min(ending, x + ss); 
            ending = min(ending, x - y / tan(a)); 
            if(beg < ending) { 
                evs.emplace_back(beg, 1); 
                evs.emplace_back(ending, -1); 
            }
        }
        int total = 0; 
        double last = 0 ; 
        sort(all(evs)); 
        for(auto [dis, val] : evs) { 
            if(total >= 0) ans[total] += dis - last; 
            total += val; 
            last = dis; 
        }
        ans[0] += v.dist() - last; 
    }
    cout << fixed << setprecision(14) ; 
    for(auto x : ans) cout << x << "\n"; 
}
