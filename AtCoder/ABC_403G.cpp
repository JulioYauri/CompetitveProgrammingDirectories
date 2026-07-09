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
	int val, y, c = 1;
	ll odd, even; 
    Node(int val) : val(val), y(rand()), odd(val), even(0) {}
	void recalc();
};

int cnt(Node* n) { return n ? n -> c : 0; }
void Node::recalc() {
    odd = even = 0; 
    if(l) { 
        odd = l -> odd; 
        even = l -> even; 
    }
    if(cnt(l) % 2 == 0) odd += val; 
    else even += val; 
    if(r) { 
        if(cnt(l) % 2) { 
            odd += r -> odd; 
            even += r -> even; 
        }else{ 
            odd += r -> even; 
            even += r -> odd; 
        }
    }
    c = cnt(l) + cnt(r) + 1; 
}

pair<Node*, Node*> split(Node* n, int k) {
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


// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}

const int mod = 1'000'000'000; 

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
    int qq; cin >> qq; 
    ll z = 0; 
    Node *t = nullptr; 
    while(qq--) { 
        int y; cin >> y; 
        int x = (y + z) % mod + 1; 
        auto [l, r] = split(t, x) ;
        Node* new_val = new Node(x); 
        t = merge(merge(l, new_val), r); 
        cout << t -> odd << "\n"; 
        z = t -> odd; 
    }
}
