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

const int N = 495; 
const int NAX = N * N; 
using D = array<int,5>; 
vector<D> v; 
vi val; 
int get_id(int i, int j) { return i * N + j ; }
vi adj[NAX];
int state[NAX], cnt[NAX]; 
int indeg[NAX];  

int calc(D d) { 
    int ans = 0 ; 
    for(int i = 4, pot = 1; i >= 0; i--, pot *= 9)  { 
        ans += pot * d[i]; 
    }
    return ans; 
}

void ps(D d) { 
    for(int i : d) cerr << i << " "; 
}


void solve() {
	int w; cin >> w; 
    D h1{ }, h2{ }; 
    rep(i,0,8) { 
        int x; cin >> x; 
        h1[x]++; 
    }
    rep(i,0,8) { 
        int x; cin >> x; 
        h2[x]++; 
    }
    if(w == 1) swap(h1, h2);
    int val1 = calc(h1), val2 = calc(h2) ; 
    int i1 = lower_bound(all(val), val1) - val.begin(); 
    int i2 = lower_bound(all(val), val2) - val.begin(); 
    int who = get_id(i1, i2); 
    vector<string> vv = { "Alice\n", "Bob\n" } ; 
    cout << (state[who] == -1 ? "Deal\n" : state[who] == 1 ? vv[w] : vv[w ^ 1]); 
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int total = 0 ; 
    D h{ }; 
    rep(i0,0,9) { 
        rep(i1,0,9) { 
            rep(i2,0,9){ 
                rep(i3,0,9) { 
                    rep(i4,0,9) { 
                        if(i0 + i1 + i2 + i3 + i4 == 8) { 
                            h = {i0, i1, i2, i3, i4}; 
                            v.push_back(h); 
                        }
                    }
                }
            }
        }
    }
    sort(all(v)); 
    val.resize(sz(v)); 
    rep(i,0,sz(v)) val[i] = calc(v[i]); 

    memset(state, -1, sizeof(state)); 
    D nh { } ; 

    rep(i,0,sz(v)) { 
        rep(j,0,sz(v)) { 
            rep(my,1,5) if(v[i][my]) { 
                rep(his,1,5) if(v[j][his]) { 
                    nh = v[i]; 
                    nh[my]--; 
                    nh[(my + his) % 5]++; 
                    int val3 = calc(nh); 
                    int i3 = lower_bound(all(val), val3) - val.begin(); 
                    // i1, i2 -> i3, i2
                    int a = get_id(i, j), b = get_id(j, i3) ; 
                    adj[b].push_back(a); 
                    indeg[a]++; 
                }
            }        
        }
    }

    queue<int> q; 
    rep(i,0,NAX) { 
        if(indeg[i] == 0) { 
            if(v[i / N][0] == 8) { 
                state[i] = 1; 
            }else { 
                state[i] = 0 ;   
            }  
            q.push(i); 
        }
    }

    while(sz(q)) { 
        int u = q.front(); q.pop(); 
        if(state[u] == 0) { 
            for(int v : adj[u]) { 
                if(state[v] == -1) { 
                    state[v] = 1; 
                    q.push(v); 
                }
            }
        }else{ 
            for(int v : adj[u]) { 
                if(state[v] == -1) { 
                    cnt[v]++; 
                    if(cnt[v] == indeg[v]) { 
                        state[v] = 0; 
                        q.push(v); 
                    }
                }
            }
        }
    }

	int tt; cin >> tt; 
	while(tt--) solve();
}
