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

template< typename T >
struct edge {
  int src, to;
  T cost;

  edge(int to, T cost) : src(-1), to(to), cost(cost) {}

  edge(int src, int to, T cost) : src(src), to(to), cost(cost) {}

  edge &operator=(const int &x) {
    to = x;
    return *this;
  }

  operator int() const { return to; }
};

template< typename T >
using Edges = vector< edge< T > >;
template< typename T >
using WeightedGraph = vector< Edges< T > >;
using UnWeightedGraph = vector< vector< int > >;
template< typename T >
using Matrix = vector< vector< T > >;

template< typename T >
Matrix< T > WarshallFloyd_matrix(WeightedGraph< T > &g, T INF) {
  const ll V = g.size();
  Matrix<ll> D(V, vector<ll>(V, INF));
  REP(i, V) D[i][i] = 0;

  for(int i=0;i<V;i++){
      for(auto &e: g[i]){
          D[i][e.to] = e.cost;
      }
  }

  for(int k = 0; k < (int)D.size(); k++) {
    for(int i = 0; i < (int)D.size(); i++) {
      for(int j = 0; j < (int)D.size(); j++) {
        if(D[i][k] == INF || D[k][j] == INF) continue;
        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
      }
    }
  }
  return D;
}

// verified @ http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll V, E;
    cin >> V >> E;

    const ll INF = (1ll<<60);
    WeightedGraph<ll> G(V);

    REP(i, E){
        ll u, v, d;
        cin >> u >> v >> d;
        G[u].emplace_back(v, d);
    }
    
    auto D = WarshallFloyd_matrix(G, INF);

    REP(i, V){
        if(D[i][i]<0){
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }

    REP(i, V){
        REP(j, V){
            if(D[i][j] == INF) cout << "INF";
            else cout << D[i][j];

            if(j<V-1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}