#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define rep(i,a,b) for(int i = (a) ; i < (b) ; i++)

using namespace ::std;
using ll = long long;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef pair<int , int> pii;
typedef vector<pii> vii;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n; 
    string s; cin >> s; 
    vi a, b;
    int p = 0; 
    while(p < n - 1) { 
        int c1 = (s[p] - '0'), c2 = (s[p + 1] - '0'); 
        if(c1 == c2) { 
            a.push_back(p); 
            b.push_back(p + 1); 
            p += 2; 
        }else{ 
            if(p + 2 >= n) break ;
            int c3 = (s[p + 2] - '0'); 
            if(c3 == c2) { 
                a.push_back(p + 1); 
                b.push_back(p + 2); 
                p += 3; 
                continue; 
            }
            // c3 = c1 -> busco la primera apar de c2 
            int ptr = p + 2, lim = min(n, p + 5); 

            while(ptr < lim && (s[ptr] - '0') != c2) ptr++; 
            if(ptr == lim) { 
                a.push_back(p); 
                b.push_back(p + 2); 
                p += 3; 
            }else{ 
                a.push_back(p); 
                a.push_back(p + 1); 
                b.push_back(p + 2); 
                b.push_back(ptr); 
                p = ptr + 1; 
            }
        }
    }
    cout << sz(a) << "\n"; 
    for(int i : a) cout << i << " " ; cout << "\n"; 
    for(int i : b) cout << i << " " ; cout << "\n"; 
    // for(int i : a) cerr << s[i] ; cerr << "\n"; 
    // for(int i : b) cerr << s[i] ; cerr << "\n"; 

}