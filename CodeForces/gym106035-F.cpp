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
using P = Point<ll> ; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    int n; cin >> n; 
    vector<P> v(n); rep(i,0,n) cin >> v[i].x >> v[i].y; 

    ll ans = LLONG_MAX; 
    rep(i,0,n) { 
        ll mx = 0 ; 
        rep(j,0,n) if(j != i) mx = max(mx, (v[i] - v[j]).dist2()); 
        ans = min(ans, mx); 
    }

    vector<P> other = v; 
    vl D(n); 
    rep(i,0,n) { 
        sort(all(other), [&](auto &p1, auto &p2){ 
            return (p1 - v[i]).dist2() < (p2 - v[i]).dist2(); 
        });
        // for(auto p : other) cerr << p << "\n"; 
        rep(j,1,n) { 
            ll his = 1; 
            for(int k = n - 1; k >= 1; k--) { 
                if(j == k) continue; 
                ans = min(ans, his + (other[k] - v[i]).dist2()); 
                his = max(his, (other[k] - other[j]).dist2()); 
            }
        }
    }
    cout << ans << "\n"; 
}
