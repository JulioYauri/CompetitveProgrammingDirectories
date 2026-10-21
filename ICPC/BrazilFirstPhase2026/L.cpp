#include<bits/stdc++.h>
#define sz(x) (int)(x.size())
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)

using ll = long long;
using namespace std;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<int, int> pii;
typedef vector<pii> vii;

const int N = 100; 

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<string> mz(N, string(N, '.')); 

    mz[0][0] = '*'; 

    for(int j = 3, p = 0; j < N; j += 2, p++) { 
        rep(i,1,N-1) mz[i][j] = '#'; 
        if(p % 2 == 1) mz[0][j] = '#'; 
        else mz[N - 1][j] = '#'; 
    }
    mz[61][0] = mz[61][2] = '#'; 

    for(int i = 59; i > 0; i-=2) {
        mz[i][1] = '#';  
        if(i % 4 == 1) mz[i][2] = '#'; 
        else mz[i][0] = '#'; 
    }

    mz[0].back() = 'X'; 
    for(int it = 0, i = 62; it < 10; it++, i += 4) { 
        mz[i][1] = '\\'; 
        mz[i + 1][0] = 'X'; 
        if(it == 9) mz[i + 1][0] = 'F'; 
        mz[i + 1][1] = '#'; 
        if(i + 2 < N) mz[i + 2][0] = '#';  
        if(i + 3 < N) mz[i + 3][2] = mz[i + 3][0] = '#'; 
    }
    int n = 100; 
    cout << n << " " << n << "\n"; 
    for(auto i : mz) cout << i << "\n"; 
}