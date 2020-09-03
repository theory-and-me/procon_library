#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
//typedef vector<vector<ll>> Graph;

const ll mod = 1e9 + 7;
//const ll mod = 998244353;

#define REP(i,n) for(ll i=0;i<(ll)n;i++)
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define spa << " " <<
#define fi first
#define se second

template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }

template<class S, class T> ostream& operator << (ostream& os, const pair<S, T> v){
os << "(" << v.first << ", " << v.second << ")"; return os;
}
template<class T> ostream& operator << (ostream& os, const vector<T> v){
for(int i = 0; i < (int)v.size(); i++){if(i > 0){os << " ";} os << v[i];} return os;
}
template<class T> ostream& operator << (ostream& os, const vector<vector<T>> v){
for(int i = 0; i < (int)v.size(); i++){if(i > 0){os << endl;} os << v[i];} return os;
}

template<typename T> void debug(vector<vector<T>>&v,ll h,ll w){for(ll i=0;i<h;i++)
{cerr<<v[i][0];for(ll j=1;j<w;j++)cerr spa v[i][j];cerr<<endl;}};
void debug(vector<string>&v,ll h,ll w){for(ll i=0;i<h;i++)
{for(ll j=0;j<w;j++)cerr<<v[i][j];cerr<<endl;}};
template<typename T> void debug(vector<T>&v,ll n){if(n!=0)cerr<<v[0];
for(ll i=1;i<n;i++)cerr spa v[i];
cerr<<endl;};

string num2bit(ll num, ll len){
    string bit = "";
    REP(i, len){
    bit += char('0'+(num>>i & 1));
    }
    return bit;
}

vector<vector<int>> grid_bfs(const vector<string> &S, const char start, const char wall){
    // start 文字が入っているところから始まる多始点BFS
    // wall があるセルには入れない．この辺は適当に変更

    const int num_dir = 4;
    const int dx[] = {0, -1, 0, 1};
    const int dy[] = {1, 0, -1, 0}; 

    const int H = S.size();
    const int W = S[0].size();
    vector<vector<int>> dist(H, vector<int>(W, -1));
    queue<pair<int, int>> qu;

    // initialization
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(S[i][j] == start){
                qu.emplace(i, j);
                dist[i][j] = 0;
            }
        }
    }

    // BFS
    while(!qu.empty()){
        auto p = qu.front();qu.pop();
        for(int idx=0;idx<num_dir;idx++){
            int ni = p.first + dx[idx];
            int nj = p.second + dy[idx];

            if(ni<0 or nj<0 or ni>H-1 or nj>W-1) continue;
            if(dist[ni][nj] != -1) continue;
            if(S[ni][nj] == wall) continue;
            
            dist[ni][nj] = dist[p.first][p.second] + 1;
            qu.emplace(ni, nj);
        }
    }

    //debug(dist, H, W);
    return dist;
}

// verfied @ https://atcoder.jp/contests/abc151/tasks/abc151_d
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    REP(i, H) cin >> S[i];

    int ma = -1;
    REP(i, H){
        REP(j, W){
            if(S[i][j] == '#') continue;
            S[i][j] = 'S';
            auto dist = grid_bfs(S, 'S', '#');
            REP(k, H)REP(l, W) chmax(ma, dist[k][l]);
            S[i][j] = '.';

            /*
            cout << i spa j << endl;
            debug(dist, H, W);
            cout << endl;
            */
        }
    }
    
    cout << ma << endl;

    return 0;
}