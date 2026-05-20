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

using pt = Point<ll> ; 
vector<pt> convex_hull(vector<pt> points) {
    int n = sz(points);
    sort(all(points), [](pt p1, pt p2){
        return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
    });
    vector<pt> hull; 
    rep(it,0,2) { // la primera halla el hull superior
        int S = sz(hull);
        rep(i,0,n) {
            while(sz(hull) >= S + 2) {
                pt A = hull.end()[-2]; 
                pt B = hull.end()[-1]; 
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

vector<int> prefix_function(vector<tuple<ll,ll,ll>> s) {
    int n = sz(s);
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n, m; cin >> n >> m; 
    vector<pt> A(n), B(m); 
    rep(i,0,n) cin >> A[i].x >> A[i].y; 
    rep(i,0,m) cin >> B[i].x >> B[i].y; 
    A = convex_hull(A); 
    B = convex_hull(B); 

    if(sz(A) != sz(B)) { 
        cout << "NO\n"; return 0; 
    }

    if(sz(A) == 2) { 
        ll d_a = (A[0] - A[1]).dist2(); 
        ll d_b = (B[0] - B[1]).dist2(); 
        cout << (d_a == d_b ? "YES\n" : "NO\n"); 
        return 0; 
    }

    auto work = [&](vector<pt> &poly) { 
        reverse(poly.begin() + 1, poly.end()); 
        vector<tuple<ll,ll,ll>> res; 
        rep(i,0,sz(poly)) { 
            pt p = poly[i], p2 = poly[(i + 1) % sz(poly)], p3 = poly[(i + 2) % sz(poly)]; 
            ll len = (p2 - p).dist2(); 
            ll cross = (p2 - p).cross(p3 - p2); 
            ll dot = (p2 - p).dot(p3 - p2); 
            ll g = gcd(cross, dot); cross /= g, dot /= g; 
            res.emplace_back(len, cross, dot);  
        }
        return res; 
    };
    vector<tuple<ll,ll,ll>> a = work(A), b = work(B); 
    const ll inf = 1LL << 62; 
    int b_siz = sz(b); 
    b.emplace_back(inf, inf, inf); 
    rep(i,0,2) for(auto x : a) b.push_back(x); 

    vi pi = prefix_function(b); 
    rep(i,b_siz,sz(b)) { 
        if(pi[i] == b_siz) { 
            cout << "YES\n" ; return 0; 
        }
    }
    cout << "NO\n"; 
}   

