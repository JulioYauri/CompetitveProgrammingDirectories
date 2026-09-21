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

/*
    Construir un árbol mientras calculo el MST (KRT?)
    El lca de dos nodos me daría el peso de la arista que usé cuando 
    pasaron a ser una componente
    En el árbol puedo guardar los tamaños de las componentes
    Casos: 
        - Si logran alcanzar el tamaño antes de unirse 
            -> Búsqueda binaria en el peso, hasta q los tamaños sumen más de k 
        - No lo logran, entonces se unen y luego: 
            -> Subir hasta que el tamaño de la componente sea >= k 
    Picante de implementar creo, nunca usé KRT, espero no sea muy yuca 
    nlogn + qlog2(n) debería pasar chill 
*/


struct UF{ 
    vi par, siz;
    UF(int n) { 
        par.resize(n + 1); 
        iota(all(par), 0); 
        siz.assign(n + 1, 1); 
    }    
    int get(int a) { return a == par[a] ? a : par[a] = get(par[a]); }
    bool unite(int a, int b) { 
        a = get(a); 
        b = get(b); 
        if(a == b) return false; 
        par[a] = b; 
        siz[b] += siz[a]; 
        return true; 
    }
};

const int N = 100'000 + 10;
const int LOG = 18;  
int n, m;
int ct; 
vi adj[N * 2];
int w[N * 2], cur_id[N], siz[N * 2]; 
int up[N * 2][LOG], dep[N * 2]; 

void dfs(int u) { 
    for(int v : adj[u]) { 
        dep[v] = dep[u] + 1; 
        up[v][0] = u; 
        dfs(v); 
    }
}

int lift(int u, int len) { 
    while(len) u = up[u][__builtin_ctz(len)], len &= (len - 1); 
    return u; 
}

int get_lca(int u, int v) { 
    if(dep[u] > dep[v]) swap(u, v); 
    v = lift(v, dep[v] - dep[u]); 
    if(u == v) return u; 
    for(int i = LOG - 1; i >= 0; i--) { 
        if(up[u][i] != up[v][i]) { 
            u = up[u][i]; 
            v = up[v][i]; 
        }
    }
    return up[u][0]; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    cin >> n >> m; 
    vii edges(m); 
    rep(i,0,m) cin >> edges[i].first >> edges[i].second; 

    UF uf(n);
    ct = n + 1;  
    rep(i,1,n+1) cur_id[i] = i, siz[i] = 1; 
    vi ws; 
    rep(i,1,m+1) { 
        auto [u, v] = edges[i - 1];  
        int u_rep = uf.get(u), v_rep = uf.get(v); 
        if(u_rep == v_rep) continue; 
        uf.unite(u, v); 
        
        int who = uf.get(u); 
        w[ct] = i; 
        siz[ct] = uf.siz[uf.get(u)]; 
        adj[ct].push_back(cur_id[u_rep]); 
        adj[ct].push_back(cur_id[v_rep]); 
        cur_id[who] = ct; 
        ws.push_back(i); 
        ct++; 
    }

    // ac[a] ya deber[i]an estar juntos todos
    int root = cur_id[uf.get(1)]; 
    dfs(root); 
    rep(lg,1,LOG) rep(i,1,ct) up[i][lg] = up[up[i][lg - 1]][lg - 1]; 

    int qq; cin >> qq; 
    while(qq--) { 
        int u, v, k; cin >> u >> v >> k; 
        int lca = get_lca(u, v); 
        int lo = -1, hi = sz(ws); 
        while(hi - lo > 1) { 
            int mi = lo + hi >> 1, max_we = ws[mi];
            bool same = false; 
            int total_u; { 
                int u2 = u; 
                for(int lg = LOG - 1; lg >= 0; lg--) { 
                    if(up[u2][lg] == 0 || w[up[u2][lg]] > max_we) continue; 
                    u2 = up[u2][lg]; 
                }
                if(dep[u2] <= dep[lca]) same = true; 
                total_u = siz[u2]; 
            }
            int total_v; { 
                int v2 = v; 
                for(int lg = LOG - 1; lg >= 0; lg--) { 
                    if(up[v2][lg] == 0 || w[up[v2][lg]] > max_we) continue; 
                    v2 = up[v2][lg]; 
                }
                if(dep[v2] <= dep[lca]) same = true; 
                total_v = siz[v2]; 
            }
            if(same) { 
                if(total_u >= k) hi = mi; 
                else lo = mi; 
            }else{ 
                if(total_u + total_v >= k) hi = mi; 
                else lo = mi; 
            }
        }
        cout << ws[hi] << "\n"; 
    }

}
