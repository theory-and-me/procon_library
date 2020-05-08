#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
const ull mod = 1e9 + 7;
#define REP(i,n) for(int i=0;i<(int)n;++i)

//debug
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

/*
https://ei1333.github.io/luzhiled/snippets/structure/segment-tree.html より．
要素のモノイド(T, f)に加えて，作用素のモノイド(E, h)も考える．
g は g(t, e) で作用素 e を要素（というか区間） t に作用させた結果を表す．
遅延セグ木に乗るための条件は，

(1) g(f(x, y), a) = f(g(x, a), g(x, a))
区間をマージしてから作用素を作用させたもの = 作用素を作用させてから区間をマージしても結果は変わらない

(2) g(g(x, a), b) = g(x, h(a, b))
要素 a に対して作用素 b，作用素 c の順番で作用させたもの = 作用素 b と作用素 c を合成してから要素 a に作用させたもの

(3) e を E の単位元とすると g(x, e) = x
作用素の単位元を作用させても要素は変化しない

Ex1. range min, range add (Starry Sky Tree)
このとき，
T, E はいずれも int
f(x, y) = min(x, y)
g(x, a) = x + a
h(a, b) = a + b
M1 = +\infty
OM0 = 0
となる．

Ex2. range min, range update
T: int
E: int
f(x, y) = min(x, y)
g(x, a) = x (a==e のとき), a (それ以外)
h(a, b) = a (b==e のとき), b (それ以外)
M1 = +\infty
OM0 = (作用素として絶対に出てこない値)
となる．
update が可換ではない（つまりhが可換ではない）ことに注意！

Ex3. range sum, range add (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G)
ちょっとややこしいことをする必要がある（参考: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3874218#1）
T: int のタプル．(区間の和, 区間の長さ)
E: int
f((x, y), (z, w)) = (x+y, z+w)
g((x, y), a) = ((x+a*y, y), a)
h(a, b) = a+b
M1 = (0, 0)
OM0 = 0
となる．
*/

template< typename Monoid, typename OperatorMonoid, typename F, typename G, typename H >
struct LazySegmentTree {
  // std::function は遅いので使わないことを推奨
  //using F = function< Monoid(Monoid, Monoid) >;
  //using G = function< Monoid(Monoid, OperatorMonoid) >;
  //using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;

  int sz, height;
  vector< Monoid > data;
  vector< OperatorMonoid > lazy;
  const F f;
  const G g;
  const H h;
  const Monoid M1;
  const OperatorMonoid OM0;


  // n: サイズ
  // f: 二つの区間をマージする二項演算
  // g: 要素と作用素をマージする二項演算
  // h: 作用素同士をマージする二項演算
  // M1: モノイドの単位元
  // OM0: 作用素の単位元

  // 初期化を忘れない！x を初期値とすると
  // REP(i, n) seg[i].set(x);
  // seg.build();

  // 初期化なしだとM1で初期化される
  // range sum をするときは，M1は(0, 0)だが初期化は(0, 1)であることに注意！

  LazySegmentTree(int n, const F f, const G g, const H h,
                  const Monoid &M1, const OperatorMonoid OM0)
      : f(f), g(g), h(h), M1(M1), OM0(OM0) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    data.assign(2 * sz, M1);
    lazy.assign(2 * sz, OM0);
  }

  void set(int k, const Monoid &x) {
    data[k + sz] = x;
  }

  void build() {
    for(int k = sz - 1; k > 0; k--) {
      data[k] = f(data[2 * k + 0], data[2 * k + 1]);
    }
  }

  inline void propagate(int k) {
    if(lazy[k] != OM0) {
      lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
      lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      data[k] = reflect(k);
      lazy[k] = OM0;
    }
  }

  inline Monoid reflect(int k) {
    return lazy[k] == OM0 ? data[k] : g(data[k], lazy[k]);
  }

  inline void recalc(int k) {
    while(k >>= 1) data[k] = f(reflect(2 * k + 0), reflect(2 * k + 1));
  }

  inline void thrust(int k) {
    for(int i = height; i > 0; i--) propagate(k >> i);
  }

  void update(int a, int b, const OperatorMonoid &x) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) lazy[l] = h(lazy[l], x), ++l;
      if(r & 1) --r, lazy[r] = h(lazy[r], x);
    }
    recalc(a);
    recalc(b);
  }

  Monoid query(int a, int b) {
    thrust(a += sz);
    thrust(b += sz - 1);
    Monoid L = M1, R = M1;
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) L = f(L, reflect(l++));
      if(r & 1) R = f(reflect(--r), R);
    }
    return f(L, R);
  }

  Monoid operator[](const int &k) {
    return query(k, k + 1);
  }

  template< typename C >
  int find_subtree(int a, const C &check, Monoid &M, bool type) {
    while(a < sz) {
      propagate(a);
      Monoid nxt = type ? f(reflect(2 * a + type), M) : f(M, reflect(2 * a + type));
      if(check(nxt)) a = 2 * a + type;
      else M = nxt, a = 2 * a + 1 - type;
    }
    return a - sz;
  }

  template< typename C >
  int find_first(int a, const C &check) {
    Monoid L = M1;
    if(a <= 0) {
      if(check(f(L, reflect(1)))) return find_subtree(1, check, L, false);
      return -1;
    }
    thrust(a + sz);
    int b = sz;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) {
        Monoid nxt = f(L, reflect(a));
        if(check(nxt)) return find_subtree(a, check, L, false);
        L = nxt;
        ++a;
      }
    }
    return -1;
  }


  template< typename C >
  int find_last(int b, const C &check) {
    Monoid R = M1;
    if(b >= sz) {
      if(check(f(reflect(1), R))) return find_subtree(1, check, R, true);
      return -1;
    }
    thrust(b + sz - 1);
    int a = sz;
    for(b += sz; a < b; a >>= 1, b >>= 1) {
      if(b & 1) {
        Monoid nxt = f(reflect(--b), R);
        if(check(nxt)) return find_subtree(b, check, R, true);
        R = nxt;
      }
    }
    return -1;
  }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    return 0;
}