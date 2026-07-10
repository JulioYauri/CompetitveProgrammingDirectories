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

// treap
// O(logN)
struct Node {
	Node *l = 0, *r = 0;
	ll val; 
    int y, c = 1;
	Node(int val) : val(val), y(rand()) {}
	void recalc();
};

int cnt(Node* n) { return n ? n -> c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

template<class F> void each(Node* n, F f) {
	if (n) { each(n -> l, f); f(n -> val); each(n -> r, f); }
}

pair<Node*, Node*> split(Node* n, ll k) {
	if (!n) return {};
	if (n -> val >= k) { // "n->val >= k" for lower_bound(k)
		auto pa = split(n->l, k);
		n -> l = pa.second;
		n -> recalc();
		return {pa.first, n};
	} else {
		auto pa = split(n -> r, k); // and just "k"
		n -> r = pa.first;
		n -> recalc();
		return {n, pa.second};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l -> y > r -> y) {
		l -> r = merge(l -> r, r);
		l -> recalc();
		return l;
	} else {
		r -> l = merge(l, r -> l);
		r -> recalc();
		return r;
	}
}

Node* ins(Node* t, Node* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, k; cin >> n >> k; 
    vi h(n + 1), a(n + 1); 
    rep(i,1,n+1) cin >> h[i]; 
    rep(i,1,n+1) cin >> a[i]; 
    
    vector<pair<ll,int>> d(n); 
    vl pr(n + 1) ; 
    rep(i,1,n+1) {  
        ll diff = h[i] - a[i]; 
        d[i - 1] = {diff, i}; 
        pr[i] = (diff < 0 ? diff * k : diff); 
        pr[i] += pr[i - 1]; 
    }

    set<int> poss { 0, n + 1 }; 
    sort(all(d)); 
    reverse(all(d)); 
    vector<vector<pair<ll, int>>> smaller_query(n + 1), greater_query(n + 1); 
    for(auto [val, pos] : d) { 
        if(val < 0) break ; 
        auto ptr = poss.insert(pos).first; 
        int left_pos = *prev(ptr), right_pos = *next(ptr); 
        if( pos - left_pos < right_pos - pos ) { 
            rep(i,left_pos,pos) { 
                ll goal = pr[i] + 1LL * val * (k + 1); 
                greater_query[pos].emplace_back(goal, 1); 
                if(right_pos <= n) { 
                    greater_query[right_pos].emplace_back(goal, -1); 
                }
            }
        }else{ 
            rep(i,pos,right_pos) { 
                ll goal = pr[i] - 1LL * val * (k + 1); 
                smaller_query[pos].emplace_back(goal, 1);
                smaller_query[left_pos].emplace_back(goal, -1); 
            }
        }
    }

    ll ans = 0; 
    Node* t1 = nullptr, *l = nullptr, *r = nullptr; 
    rep(i,0,n+1) { 
        for(auto [q, mul] : smaller_query[i]) { 
            tie(l, r) = split(t1, q + 1); 
            ans += 1LL * mul * cnt(l); 
            t1 = merge(l, r); 
        }
        tie(l, r) = split(t1, pr[i]); 
        Node* new_val = new Node(pr[i]); 
        t1 = merge(merge(l, new_val), r); 
    }
    t1 = nullptr;  
    for(int i = n; i >= 0; i--) {
        tie(l, r) = split(t1, pr[i]);
        Node* new_val = new Node(pr[i]);  
        t1 = merge(merge(l, new_val), r); 
        for(auto [q, mul] : greater_query[i]) { 
            tie(l, r) = split(t1, q); 
            ans += 1LL * mul * cnt(r); 
            t1 = merge(l, r); 
        }
    }
    cout << ans << "\n"; 
}
