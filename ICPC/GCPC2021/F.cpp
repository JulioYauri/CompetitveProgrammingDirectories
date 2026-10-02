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
    friend istream& operator>>(istream &is, P &p) { 
        return is >> p.x >> p.y; 
    }
};

using P = Point<ll> ; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    P p0, pn; 
    cin >> p0 >> pn; 

    int n; cin >> n; 
    vector<P> up(n), down(n); 
    rep(i,0,n) { 
        int x; cin >> x; 
        cin >> down[i].y >> up[i].y; 
        up[i].x = down[i].x = x; 
    }
    up.push_back(pn); 
    down.push_back(pn); 
    n++; 

    
    deque<P> sup, sdown; 
    vector<P> ans; 
    sup = sdown = { p0 }; 
    rep(i,0,n) { 
        while(sz(sup) >= 2 && up[i].cross(sup.end()[-1], sup.end()[-2]) >= 0) { 
            sup.pop_back(); 
        } 
        sup.push_back(up[i]); 
        while(sz(sdown) >= 2 && down[i].cross(sdown.end()[-1], sdown.end()[-2]) <= 0) { 
            sdown.pop_back(); 
        }
        sdown.push_back(down[i]); 

        if(sz(sup) == 2 && sz(down) == 2) continue;     

        if(sz(sup) == 2 && up[i].cross(sdown[0], sdown[1]) <= 0) { 
            while(sz(sdown) >= 2 && up[i].cross(sdown[0], sdown[1]) < 0) { 
                ans.push_back(sdown[0]); 
                sdown.pop_front(); 
            }
            sup = { sdown[0], up[i] } ; 
        }else if(sz(sdown) == 2 && down[i].cross(sup[0], sup[1]) >= 0) { 
            while(sz(sup) >= 2 && down[i].cross(sup[0], sup[1]) > 0) { 
                ans.push_back(sup[0]); 
                sup.pop_front(); 
            }
            sdown = { sup[0], down[i] }; 
        }
    }   
    for(auto p : ans) cout << p.x << " " << p.y << "\n"; 
    for(auto p : sup) cout << p.x << " " << p.y << "\n";  
}
