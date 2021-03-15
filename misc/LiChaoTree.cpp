#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(ll i=0;i<(ll)n;i++)
#define dump(x)  cerr << "Line " << __LINE__ << ": " <<  #x << " = " << (x) << "\n";
#define spa << " " <<
#define fi first
#define se second
#define ALL(a)  (a).begin(),(a).end()
#define ALLR(a)  (a).rbegin(),(a).rend()

using ld = long double;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<ld, ld>;

template<typename T> using V = vector<T>;
template<typename T> using P = pair<T, T>;
template<typename T> vector<T> make_vec(size_t n, T a) { return vector<T>(n, a); }
template<typename... Ts> auto make_vec(size_t n, Ts... ts) { return vector<decltype(make_vec(ts...))>(n, make_vec(ts...)); }
template<class S, class T> ostream& operator << (ostream& os, const pair<S, T> v){os << "(" << v.first << ", " << v.second << ")"; return os;}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { for (auto &e : v) os << e << ' '; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<vector<T>> &v){ for(auto &e : v){os << e << "\n";} return os;}
struct fast_ios { fast_ios(){ cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; } fast_ios_;

template <class T> void UNIQUE(vector<T> &x) {sort(ALL(x));x.erase(unique(ALL(x)), x.end());}
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }
void fail() { cout << -1 << '\n'; exit(0); }
inline int popcount(const int x) { return __builtin_popcount(x); }
inline int popcount(const ll x) { return __builtin_popcountll(x); }
template<typename T> void debug(vector<vector<T>>&v,ll h,ll w){for(ll i=0;i<h;i++)
{cerr<<v[i][0];for(ll j=1;j<w;j++)cerr spa v[i][j];cerr<<"\n";}};
template<typename T> void debug(vector<T>&v,ll n){if(n!=0)cerr<<v[0];
for(ll i=1;i<n;i++)cerr spa v[i];
cerr<<"\n";};

const ll INF = (1ll<<62);
// const ld EPS   = 1e-10;
// const ld PI    = acos(-1.0);
const ll mod = (int)1e9 + 7;
//const ll mod = 998244353;

// https://ei1333.github.io/library/structure/convex-hull-trick/li-chao-tree.cpp
// コンストラクタに求めうるxの集合とINFを与える
// 場合によっては座圧いるかも？
template< typename T >
struct LiChaoTree {
  struct Line {
    T a, b;

    Line(T a, T b) : a(a), b(b) {}

    inline T get(T x) const { return a * x + b; }

    inline bool over(const Line &b, const T &x) const {
      return get(x) < b.get(x);
    }
  };

  vector< T > xs;
  vector< Line > seg;
  int sz;

  LiChaoTree(const vector< T > &x, T INF) : xs(x) {
    sz = 1;
    while(sz < xs.size()) sz <<= 1;
    while(xs.size() < sz) xs.push_back(xs.back() + 1);
    seg.assign(2 * sz - 1, Line(0, INF));
  }

  void update(Line &x, int k, int l, int r) {
    int mid = (l + r) >> 1;
    auto latte = x.over(seg[k], xs[l]), malta = x.over(seg[k], xs[mid]);
    if(malta) swap(seg[k], x);
    if(l + 1 >= r) return;
    else if(latte != malta) update(x, 2 * k + 1, l, mid);
    else update(x, 2 * k + 2, mid, r);
  }

  void update(T a, T b) { // ax+b
    Line l(a, b);
    update(l, 0, 0, sz);
  }

  T query(int k) { // xs[k]
    const T x = xs[k];
    k += sz - 1;
    T ret = seg[k].get(x);
    while(k > 0) {
      k = (k - 1) >> 1;
      ret = min(ret, seg[k].get(x));
    }
    return ret;
  }
};


// verified @ https://atcoder.jp/contests/dp/tasks/dp_z
int main(){

    ll n, c;
    cin >> n >> c;
    V<ll> h(n);
    REP(i, n) cin >> h[i];

    V<ll> dp(n);
    dp[0] = 0;
    V<ll> init;
    REP(i, 1010101) init.push_back(i);
    LiChaoTree<ll> lct(init, INF);
    lct.update(-2*h[0], h[0]*h[0]+dp[0]);

    for(ll i=1;i<n;i++){
        dp[i] = lct.query(h[i]) + h[i] * h[i] + c;
        lct.update(-2*h[i], h[i]*h[i]+dp[i]);
    }
    cout << dp[n-1] << endl;

    return 0;
}