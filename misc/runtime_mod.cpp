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
// const ll mod = (int)1e9 + 7;
//const ll mod = 998244353;

// noshi91 さんの実行時 modint (https://noshi91.hatenablog.com/entry/2019/03/31/174006)
class runtime_modint {
  using u64 = std::uint_fast64_t;

  static u64 &mod() {
    static u64 mod_ = 0;
    return mod_;
  }

public:
  u64 a;

  runtime_modint(const u64 x = 0) : a(x % get_mod()) {}
  u64 &value() noexcept { return a; }
  const u64 &value() const noexcept { return a; }
  runtime_modint operator+(const runtime_modint rhs) const {
    return runtime_modint(*this) += rhs;
  }
  runtime_modint operator-(const runtime_modint rhs) const {
    return runtime_modint(*this) -= rhs;
  }
  runtime_modint operator*(const runtime_modint rhs) const {
    return runtime_modint(*this) *= rhs;
  }
  runtime_modint operator/(const runtime_modint rhs) const {
    return runtime_modint(*this) /= rhs;
  }
  runtime_modint &operator+=(const runtime_modint rhs) {
    a += rhs.a;
    if (a >= get_mod()) {
      a -= get_mod();
    }
    return *this;
  }
  runtime_modint &operator-=(const runtime_modint rhs) {
    if (a < rhs.a) {
      a += get_mod();
    }
    a -= rhs.a;
    return *this;
  }
  runtime_modint &operator*=(const runtime_modint rhs) {
    a = a * rhs.a % get_mod();
    return *this;
  }
  runtime_modint &operator/=(runtime_modint rhs) {
    u64 exp = get_mod() - 2;
    while (exp) {
      if (exp % 2) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }

  static void set_mod(const u64 x) { mod() = x; }
  static u64 get_mod() { return mod(); }
};

using mint = runtime_modint;

int main(){

    ll mod = 10;
    mint::set_mod(mod);

    mint A = 12;
    mint B = 34;

    cout << (A+B).value() << endl;

    mod = 11;
    mint::set_mod(mod);

    A = 12;
    B = 34;

    cout << (A+B).value() << endl;

    return 0;
}