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
struct Point { 
    typedef Point P; 
    T x, y; 
    explicit Point(T x=0, T y=0) : x(x), y(y) { }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator/(T d) const { return P(x / d, y / d); }
    P operator*(T d) const { return P(x * d, y * d); }
    P unit() const { return *this / dist() ; }
    P perp() const { return P(-y, x) ; }
    T dot(P p) const { return x * p.x + y * p.y ; }
    T cross(P p) const { return x * p.y - y * p.x ; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    void read() { cin >> x >> y; }
    double angle() { return atan2(y, x); }
    double dist() const { return sqrt(dist2()); }
};


template<class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
	P d = c2 - c1;
	double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < 0)  return {};
	vector<pair<P, P>> out;
	for (double sign : {-1, 1}) {
		P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
		out.push_back({c1 + v * r1, c2 + v * r2});
	}
	if (h2 == 0) out.pop_back();
	return out;
}

const double pi = acos(-1); 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    using P = Point<double>; 
    P c; c.read(); 
    P d; d.read(); 
    P b; b.read(); double rb; cin >> rb; 
    P a; a.read(); double ra; cin >> ra; 

    auto tan_cur = tangents(c, 0, a, ra); 
    auto tan_dest = tangents(d, 0, a, ra); 

    double ans = 1e18 ; 
    for(auto [_, pc] : tan_cur) { 
        for(auto [__, pd] : tan_dest) { 
            double th = (pc - a).angle() - (pd - a).angle(); 
            if(th < 0) th += 2 * pi; 
            th = min(th, 2 * pi - th); 
            ans = min(ans, th * ra); 
        }
    }
    cout << fixed << setprecision(10); 
    cout << ans + (tan_cur[0].second - c).dist() + (tan_dest[1].second - d).dist() << "\n"; 
}
