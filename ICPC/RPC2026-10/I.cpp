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
    double r; cin >> r; 

    vector<P> v(n); 
    rep(i,0,n) cin >> v[i].x >> v[i].y ;

    sort(all(v), [](auto p1, auto p2) { 
        if(p1.y == p2.y) return p1.x < p2.x; 
        return p1.y < p2.y; 
    }); 

    const double inf = 1e30 ; 
    int ans = 1; 
    rep(b,0,n) { 
        vector<P> cur(v.begin() + b + 1, v.end()); 
        if(cur.empty()) continue; 
        sort(all(cur), [&](auto p1, auto p2) { 
            return v[b].cross(p1, p2) < 0; 
        }); 
        int siz = sz(cur); 
        vector dp(siz, vector<double>(siz + 1, inf)); 
        rep(i,0,siz) { 
            dp[i][1] = 2.0 * (cur[i] - v[b]).dist(); 
            rep(j,i+1,siz) { 
                int cnt = 1; 
                rep(k,i+1,j) { 
                    if(cur[j].cross(cur[i], cur[k]) >= 0) cnt++; 
                }
                double seg = (cur[i] - v[b]).dist(); 
                rep(tot,1,siz+1) { 
                    if(tot + cnt <= siz) { 
                        dp[j][tot + cnt] = min(dp[j][tot + cnt], dp[i][tot] - seg + 
                                (v[b] - cur[j]).dist() + (cur[j] - cur[i]).dist()) ; 
                    }
                }
            }
        }
        rep(i,0,siz) rep(j,0,siz+1) if(dp[i][j] < r + 1e-8) ans = max(ans, j + 1); 
    }
    cout << ans << "\n"; 
}
