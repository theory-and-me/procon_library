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
using pll = pair<long, long>;
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

// BiT
// 0-indexed で操作できるが，内部では1-indexedで持っていることに注意
// 基本的には segment tree の使用を推奨，メモリ・定数倍がヤバイ時に使用
template< typename T >
struct BIT {
  vector< T > data;

  BIT(int sz) {
    data.assign(++sz, 0);
  }

  // 閉区間 [0, k] の和を求める
  T sum(int k) {
    T ret = 0;
    for(++k; k > 0; k -= k & -k) ret += data[k];
    return (ret);
  }

  // 閉区間 [k, l] の和を求める
  T segment_sum(int k, int l){
      T ret = 0;
      ret += sum(l);
      ret -= sum(k-1);
      return (ret);
  }

  // 要素 k に x を加える
  void add(int k, T x) {
    for(++k; k < (int)data.size(); k += k & -k) data[k] += x;
  }

  // 要素 k を x の変更
  void update(int k, T x){
      T tmp = segment_sum(k, k);
      add(k, x-tmp);
  }

  // 二分探索 [0, k]　の和が w 以上になるような最小の k を求める
  // 値が全て0以上じゃないと無理
  // 存在しなければ sz-1 を返す
  // w<=0 のときは -1 を返す
  int lower_bound(T w){
      if(w<=0) return -1;

      int sz = data.size();
      int x = 0, r = 1;
      while(r < sz-1) r = (r << 1);
      for(int len = r; len > 0; len = (len >> 1)){
          if(x + len <= sz-1 and data[x + len] < w){
              w -= data[x + len];
              x += len;
          }
      }
      return x;
  }

  // 全ての要素をprint
  void print(){
      cout << "Line" <<  __LINE__  << ": BIT = ";
      for(int i=0;i<(int)data.size()-1;i++) cout << segment_sum(i, i) << " ";
      cout << "\n";
  }
};

// point add, range sum
// verified @ http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
// int main(){

//     ll n, q;
//     cin >> n >> q;

//     BIT<ll> bit(n);

//     REP(_, q){
//         ll c, x, y;
//         cin >> c >> x >> y;
//         x--, y--;
//         bit.print();
//         if(c) cout << bit.segment_sum(x, y) << "\n";
//         else y++, bit.add(x, y);
//     }

//     return 0;
// }

// binary search
// verified @ https://atcoder.jp/contests/arc033/tasks/arc033_3
// int main(){

//     ll Q;
//     cin >> Q;

//     BIT<ll> bit(202020);

//     REP(_, Q){
//         ll T, X;
//         cin >> T >> X;
//         if(T == 1){
//             X--;
//             bit.update(X, 1);
//         }else{
//             int k = bit.lower_bound(X);
//             cout << k+1 << "\n";
//             bit.update(k, 0);
//         }
//     }

//     return 0;
// }

// TO DO: verify @ https://codeforces.com/contest/1354/problem/D

int main(){

    ll n, q;
    cin >> n >> q;
    V<ll> a(n);
    REP(i, n) cin >> a[i];

    const ll MA = 1010101;
    BIT<ll> bit(MA);

    REP(i, n) bit.add(a[i], 1);

    REP(_, q){
        ll k;
        cin >> k;
        if(k<0){
            k *= -1;
            ll val = bit.lower_bound(k);
            bit.add(val, -1);
        }else{
            bit.add(k, 1);
        }
    }

    ll val = bit.lower_bound(1);
    if(val==MA) val = 0;
    cout << val << "\n";

    return 0;
}
