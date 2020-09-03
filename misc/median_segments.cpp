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

template< typename Monoid >
struct SegmentTree {
  using F = function< Monoid(Monoid, Monoid) >;

  int sz;
  vector< Monoid > seg;

  const F f;
  const Monoid M1;

  // n: 要素数，F: モノイド間の演算，M1: 演算の単位元
  // F は無名関数で渡す
  SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz, M1);
  }

  // k番目の要素にxを代入
  void set(int k, const Monoid &x) {
    seg[k + sz] = x;
  }

  // 構築
  void build() {
    for(int k = sz - 1; k > 0; k--) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  // k番目の値をxに変更
  void update(int k, const Monoid &x) {
    k += sz;
    seg[k] = x;
    while(k >>= 1) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  // 区間[a, b)に関して演算して結果を返す
  Monoid query(int a, int b) {
    Monoid L = M1, R = M1;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) L = f(L, seg[a++]);
      if(b & 1) R = f(seg[--b], R);
    }
    return f(L, R);
  }

  // k番目の値を返す(set[k]でアクセス)
  Monoid operator[](const int &k) const {
    return seg[k + sz];
  }


  template< typename C >
  int find_subtree(int a, const C &check, Monoid &M, bool type) {
    while(a < sz) {
      Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
      if(check(nxt)) a = 2 * a + type;
      else M = nxt, a = 2 * a + 1 - type;
    }
    return a - sz;
  }


  template< typename C >
  //[a, x)がcheckを満たす最初の要素位置xを返す
  // 存在しない場合は-1を返すことに注意
  // Cには判定関数を入れる
  int find_first(int a, const C &check) {
    Monoid L = M1;
    if(a <= 0) {
      if(check(f(L, seg[1]))) return find_subtree(1, check, L, false);
      return -1;
    }
    int b = sz;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) {
        Monoid nxt = f(L, seg[a]);
        if(check(nxt)) return find_subtree(a, check, L, false);
        L = nxt;
        ++a;
      }
    }
    return -1;
  }

  //[x, b)がcheckを満たす最後の要素位置xを返す
  template< typename C >
  int find_last(int b, const C &check) {
    Monoid R = M1;
    if(b >= sz) {
      if(check(f(seg[1], R))) return find_subtree(1, check, R, true);
      return -1;
    }
    int a = sz;
    for(b += sz; a < b; a >>= 1, b >>= 1) {
      if(b & 1) {
        Monoid nxt = f(seg[--b], R);
        if(check(nxt)) return find_subtree(b, check, R, true);
        R = nxt;
      }
    }
    return -1;
  }
};

template<typename T>
ll median_segments(vector<T> &A, T x, bool median_type){

    // メディアンがx以上である区間の数を数える
    // 偶数長の配列の場合メディアンの取り方は二つあるので，median_typeで指定
    // median_type = true の時は[1, 2, 3, 4]のメディアンは2
    // median_type = false の時は[1, 2, 3, 4]のメディアンは3

    ll n = A.size();
    const ll MA = 2*n+10;
    SegmentTree<ll> seg(MA, [](ll a, ll b){return a+b;}, 0);
    ll geta = n+1;
    ll res = 0;
    ll S = 0;

    seg.update(S+geta, 1);
    for(int i=0;i<n;i++){
        ll val = (A[i]>=x ? 1 : -1);
        S += val;
        if(median_type) res += seg.query(0, S+geta);
        else res += seg.query(0, S+geta+1);
        ll tmp_val = seg[S+geta];
        seg.update(S+geta, tmp_val+1);
    }

    return res;
}

// verified @ https://codeforces.com/contest/1349/problem/B, https://atcoder.jp/contests/abc107/tasks/arc101_b
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    vector<ll> a = {1, 2, 3, 4};
    dump(median_segments(a, (ll)2, true))
    dump(median_segments(a, (ll)2, false))

    return 0;
}