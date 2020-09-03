#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
typedef vector<vector<ll>> Graph;

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

bool bipartite_coloring(int now, int col, Graph &G, vector<int> &mark){
    //vector<int> mark(N, -1) を渡す！
    if(mark[now] != -1) return (mark[now] == col);
    mark[now] = col;
    bool ok = true;
    for(auto next: G[now]){
        ok &= bipartite_coloring(next, 1-col, G, mark);
    }
    return ok;
}

// https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_c
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;    
    Graph G(N);
    REP(i, M){
        ll u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<int> mark(N, -1);
    if(bipartite_coloring(0, 0, G, mark)){
        ll res = 0;
        int black = 0;
        REP(i, N) black += mark[i];
        res += black*(N-black);
        REP(now, N){
            for(auto next: G[now]){
                if(now>next and mark[now]!=mark[next]) res--;
            }
        }
        cout << res << endl;
    }else{
        cout << N*(N-1)/2 - M << endl;
    }


    return 0;
}