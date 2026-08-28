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
    bool up() { 
        return (y == 0 ? x > 0 : y > 0); 
    }
};

using P = Point<ll> ; 

template<class Fun> 
int extreme(const vector<P>& poly, Fun dir) { 
    int n = sz(poly), low = 0, low_sgn; 
    auto nx = [&](int i) { return i + 1 == n ? 0 : i + 1 ; };
    auto pr = [&](int i) { return i ? i - 1 : n - 1; };
    auto vertexCmp = [&](int i, int j) { 
        return sgn(dir(poly[j]).cross(poly[j] - poly[i]));
    };
    auto isExtreme = [&](int i , int &i_sgn) { 
        return (i_sgn = vertexCmp(nx(i), i)) >= 0 && vertexCmp(i, pr(i)) < 0 ; 
    };

    for(int high = isExtreme(0, low_sgn) ? 1 : n; low + 1 < high;) { 
        int mid = (low + high) / 2, mid_sgn; 
        if(isExtreme(mid, mid_sgn)) return mid; 
        if(low_sgn != mid_sgn ? low_sgn < mid_sgn
                : low_sgn == vertexCmp(low, mid)) high = mid; 
        else low = mid, low_sgn = mid_sgn; 
    }
    return low ; 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int n; cin >> n; 
    vector<P> poly(n); 
    rep(i,0,n) cin >> poly[i].x >> poly[i].y; 

    vector<pair<P, int> > evs; 
    int m; cin >> m; 
    rep(i,1,m+1) { 
        P p; cin >> p.x >> p.y; 
        int i1 = extreme(poly, [&](P a){ return a - p; }); 
        int i2 = extreme(poly, [&](P a){ return p - a; }); 
        P e1 = p - poly[i1], e2 = p - poly[i2]; 
        if(e1.cross(e2) < 0) swap(e1, e2); 
        evs.emplace_back(e1, +i); 
        evs.emplace_back(e2, -i);     
    }

    sort(all(evs), [](auto p1, auto p2) { 
        if(p1.first.up() == p2.first.up()) { 
            if(p1.first.cross(p2.first) == 0) return p1.second > 0 ; 
            return p1.first.cross(p2.first) > 0 ; 
        }else{ 
            return p1.first.up(); 
        }
    });
    vector<bool> vis(m + 1, false); 
    int cur = 0; 
    for(auto [f, s] : evs) { 
        int pos = abs(s); 
        if(vis[pos]) continue; 
        if(s < 0) cur++; 
        vis[pos] = true; 
    }

    int ans = cur; 
    for(auto [f, s] : evs) { 
        if(s > 0) cur++; 
        else cur--; 
        ans = max(ans, cur); 
    }
    cout << ans << "\n"; 
}
