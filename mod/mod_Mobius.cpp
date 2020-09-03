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

template <std::uint_fast64_t Modulus> class modint {
  // long long から modint を作るときは必ず正の数にしてからコンストラクタに入れること！ 
  // そうしないとバグります
  using u64 = std::uint_fast64_t;

public:
  u64 a;

  constexpr modint(const u64 x = 0) noexcept : a(x % Modulus) {}
  constexpr u64 &value() noexcept { return a; }
  constexpr const u64 &value() const noexcept { return a; }
  constexpr modint operator+(const modint rhs) const noexcept {
    return modint(*this) += rhs;
  }
  constexpr modint operator-(const modint rhs) const noexcept {
    return modint(*this) -= rhs;
  }
  constexpr modint operator*(const modint rhs) const noexcept {
    return modint(*this) *= rhs;
  }
  constexpr modint operator/(const modint rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint rhs) noexcept {
    a += rhs.a;
    if (a >= Modulus) {
      a -= Modulus;
    }
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (a < rhs.a) {
      a += Modulus;
    }
    a -= rhs.a;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    a = a * rhs.a % Modulus;
    return *this;
  }
  constexpr modint &operator/=(modint rhs) noexcept {
    u64 exp = Modulus - 2;
    while (exp) {
      if (exp % 2) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }
};
using mint = modint<mod>;

template <class T, class U> constexpr T power(T x, U exp) {
  T ret = static_cast<T>(1);
  while (exp) {
    if (exp % static_cast<U>(2) == static_cast<U>(1))
      ret *= x;
    exp /= static_cast<U>(2);
    x *= x;
  }
  return ::std::move(ret);
}

template<typename T> 
vector<T> Mobius(int m, T inv_one){
    // inv_one は-1に相当
	vector<bool> is_prime(m+1, true);
    vector<T> meb(m+1, 1);
    meb[0] = 0;
    meb[1] = 1;
    is_prime[0] = false;
    is_prime[1] = false;
    REP(i, m+1){
    	if(!is_prime[i]) continue;
    	for(int j=2;j*i<=m;j++){
    		is_prime[i*j] = false;
    	}
    	for(int j=1;j*i<=m;j++){
    		meb[i*j] *= inv_one;
    		if(j%i == 0) meb[i*j] = 0;
    	}
    }
    return meb;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);



    return 0;
}