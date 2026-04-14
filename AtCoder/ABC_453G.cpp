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

class PersistentSegtree {
private:
	struct Node {
		ll sum = 0;
		int l = 0, r = 0;
	};

	const int n;
	vector<Node> tree;
	int timer = 1;

	Node join(int l, int r) { return Node{tree[l].sum + tree[r].sum, l, r}; }

	int build(int tl, int tr, const vector<int> &arr) {
		if (tl == tr) {
			tree[timer] = {arr[tl], 0, 0};
			return timer++;
		}

		int mid = (tl + tr) / 2;
		tree[timer] = join(build(tl, mid, arr), build(mid + 1, tr, arr));

		return timer++;
	}

	int set(int v, int pos, int val, int tl, int tr) {
		if (tl == tr) {
			tree[timer] = {val, 0, 0};
			return timer++;
		}

		int mid = (tl + tr) / 2;
		if (pos <= mid) {
			tree[timer] = join(set(tree[v].l, pos, val, tl, mid), tree[v].r);
		} else {
			tree[timer] = join(tree[v].l, set(tree[v].r, pos, val, mid + 1, tr));
		}

		return timer++;
	}

	ll range_sum(int v, int ql, int qr, int tl, int tr) {
		if (qr < tl || tr < ql) { return 0ll; }
		if (ql <= tl && tr <= qr) { return tree[v].sum; }

		int mid = (tl + tr) / 2;
		return range_sum(tree[v].l, ql, qr, tl, mid) +
		       range_sum(tree[v].r, ql, qr, mid + 1, tr);
	}

public:
    // MX_NODES = 2 * n + q * (3 + __lg(n)); 
	PersistentSegtree(int n, int MX_NODES) : n(n), tree(MX_NODES) {}
	int build(const vector<int> &arr) { return build(0, n - 1, arr); }
	int set(int root, int pos, int val) { return set(root, pos, val, 0, n - 1); }
	ll range_sum(int root, int l, int r) { return range_sum(root, l, r, 0, n - 1); }
	int add_copy(int root) {
		tree[timer] = tree[root];
		return timer++;
	}
};


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int n, m, qq; cin >> n >> m >> qq; 
    PersistentSegtree st(m, 2 * m + m + qq * (3 + __lg(m))); 
    vi roots(n); 
    roots[0] = st.build(vi(m, 0)); 
    rep(i,1,n) roots[i] = st.add_copy(roots[0]); 

    while(qq--) { 
        int q; cin >> q; 
        if(q == 1) { 
            int x, y; cin >> x >> y; 
            x--, y--; 
            roots[x] = st.add_copy(roots[y]); 
        }else if(q == 2) { 
            int x, y, z; cin >> x >> y >> z; x--, y--; 
            roots[x] = st.set(roots[x], y, z); 
        }else { 
            int x, l, r; cin >> x >> l >> r; 
            x--, l--, r--; 
            cout << st.range_sum(roots[x], l, r) << "\n"; 
        }
    }

}
