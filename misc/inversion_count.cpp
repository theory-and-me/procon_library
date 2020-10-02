#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(ll i=0;i<(ll)n;i++)
#define dump(x)  cerr << "Line " << __LINE__ << ": \n" <<  #x << " = " << (x) << "\n";
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

template< typename T >
struct BIT {
  vector< T > data;

  BIT(int sz) {
    data.assign(++sz, 0);
  }

  // 閉区間 [0, k] の和を求める
  // k は（指定したsz）-1　までしか値を取れない
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

template<class T>
ll inversion_count(vector<T> &x, bool compress = false){
    // x の転倒数を計算
    // 座標圧縮が必要な場合，compress = true とする
    // 同じ値が含まれる場合は使えない，inversion_count_2 を使う

    int sz = x.size();

    if(compress){
        vector<T> y = x;
        UNIQUE(y);
        for(int i=0;i<sz;i++){
            x[i] = lower_bound(ALL(y), x[i]) - y.begin();
        }
    }

    const int MA = sz+1; // SHOULD BE EDITTED!!
    BIT<ll> bit(MA);

    ll res = 0;
    for(int i=0;i<sz;i++){
        res += bit.segment_sum(x[i]+1, MA-1);
        bit.add(x[i], 1);    
    }

    return res;
}

template<class T>
ll inversion_count_between(vector<T> &x, vector<T> &y){
    // x を y にするために必要な最小 swap 回数（転倒数）を計算
    // 同じ値が含まれても良い（最小のswap回数になる）
    // 座標圧縮も勝手にやってくれる
    // x を y にできない場合 -1 を返す
    // ちょっと遅い

    int sz = x.size();

    assert(sz = (int)y.size());

    BIT<ll> bit(sz);

    map<T, vector<int>> loc;
    for(int i=sz-1;i>=0;i--){
        loc[x[i]].push_back(i);
    }

    ll res = 0;
    for(int i=0;i<sz;i++){
        vector<int> &v = loc[y[i]];
        if(v.empty()) return -1;
        int id = v.back(); v.pop_back();
        res += id - bit.sum(id-1);
        bit.add(id, 1);
    }

    return res;
}

// verified @ http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D&lang=jp
int main(){

    ll n;
    cin >> n;
    V<ll> a(n);
    REP(i, n) cin >> a[i];

    // cout << inversion_count(a, 1) << endl;

    auto b = a;
    sort(ALL(b));
    cout << inversion_count_between(a, b) << endl;

    return 0;
}