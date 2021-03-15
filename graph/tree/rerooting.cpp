#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
//const ull mod = 1e9 + 7;
const ll mod = 1e9 + 7;
#define REP(i,n) for(int i=0;i<(int)n;++i)

// debug
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

template<class S, class T> ostream& operator << (ostream& os, const pair<S, T> v){
  os << "(" << v.first << ", " << v.second << ")"; return os;
}
template<class T> ostream& operator << (ostream& os, const vector<T> v){
  for(int i = 0; i < (int)v.size(); i++){if(i > 0){os << " ";} os << v[i];} return os;
}
template<class T> ostream& operator << (ostream& os, const vector<vector<T>> v){
  for(int i = 0; i < (int)v.size(); i++){if(i > 0){os << endl;} os << v[i];} return os;
}
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }

// conversion number to bit
string num2bit(ll num, ll len){
  string bit = "";
  REP(i, len){
    bit += char('0'+(num>>i & 1));
  }
  return bit;
}


// 全方位木DP
// https://ei1333.hateblo.jp/entry/2018/12/21/004022 の下の方のやつ
// https://codeforces.com/contest/1294/problem/F で色々試行錯誤したので見るといいかも
// 細かい部分はノートを見ると分かりやすいので見るべし

// F はマージするための関数
// G は子から値を持ち上げるための関数
// Edge の data には辺の属性を入れる（辺の長さなど）
// 辺をセットして build() すると，edge の dp に部分木ごとの値が入る

template< typename sum_t, typename key_t >
struct ReRooting {
  struct Edge {
    int to;
    key_t data;
    sum_t dp, ndp;
  };

  using F = function< sum_t(sum_t, sum_t) >;
  using G = function< sum_t(sum_t, key_t) >;

  // subdp: 一度目のdfsの結果を保持する配列
  // dp: 二度目のdfsの後，結果を各頂点でマージした値を保持する配列
  vector< vector< Edge > > g;
  const F f;
  const G gg;
  const sum_t ident;
  vector< sum_t > subdp, dp;

  ReRooting(int V, const F f, const G g, const sum_t &ident)
      : g(V), f(f), gg(g), ident(ident), subdp(V, ident), dp(V, ident) {}

  // add_edge は危険なので使わない方が良い
  // u->v に重み d の有向辺を追加するのではなく，
  // u->v と v->u の両方に重み d の有向辺を追加する
  // void add_edge(int u, int v, const key_t &d) {
  //   g[u].emplace_back((Edge) {v, d, ident, ident});
  //   g[v].emplace_back((Edge) {u, d, ident, ident});
  // }

  // u->v に重み d の有向辺を追加し，
  // v->u に重み e の有向辺を追加する
  void add_edge_bi(int u, int v, const key_t &d, const key_t &e) {
    g[u].emplace_back((Edge) {v, d, ident, ident});
    g[v].emplace_back((Edge) {u, e, ident, ident});
  }

  // 一度目のdfs
  void dfs_sub(int idx, int par) {
    for(auto &e : g[idx]) {
      if(e.to == par) continue;
      dfs_sub(e.to, idx);
      subdp[idx] = f(subdp[idx], gg(subdp[e.to], e.data));
    }
  }

  // 二度目のdfs
  void dfs_all(int idx, int par, const sum_t &top) {
    sum_t buff{ident};
    for(int i = 0; i < (int) g[idx].size(); i++) {
      auto &e = g[idx][i];
      e.ndp = buff;
      e.dp = gg(par == e.to ? top : subdp[e.to], e.data);
      buff = f(buff, e.dp);
    }
    dp[idx] = buff;
    buff = ident;
    for(int i = (int) g[idx].size() - 1; i >= 0; i--) {
      auto &e = g[idx][i];
      if(e.to != par) dfs_all(e.to, idx, f(e.ndp, buff));
      e.ndp = f(e.ndp, buff);
      buff = f(buff, e.dp);
    }
  }

  vector< sum_t > build() {
    dfs_sub(0, -1);
    dfs_all(0, -1, ident);
    return dp;
  }
};

int main(){
	// verified @ http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=jp
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    if(n==1){
    	cout << 0 << endl;
    	return 0;	
    }

    auto f1 = [](int a, int b){
    	return max(a, b);
    };

    auto f2 = [](int a, int data){
    	return a+data;
    };

    ReRooting<int, int> RR(n, f1, f2, 0);

    REP(i, n-1){
    	int s, t, w;
    	cin >> s >> t >> w;
    	RR.add_edge_bi(s, t, w, w);
    }
    RR.build();

    int res = 0;
    REP(i, n){
        if(RR.g[i].size()==1){
            chmax(res, RR.g[i][0].dp);
        }else{
            vector<int> tmp;
            REP(j, RR.g[i].size()){
                tmp.push_back(RR.g[i][j].dp);
            }
            sort(tmp.rbegin(), tmp.rend());
            //cout << tmp << endl;
            chmax(res, tmp[0] + tmp[1]);
        }
    }
    cout << res << endl;
    return 0;
}