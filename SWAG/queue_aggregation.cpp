#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;
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
template<typename T> void debug(vector<T>&v,ll n){if(n!=0)cerr<<v[0];
for(ll i=1;i<n;i++)cerr spa v[i];
cerr<<endl;};

template <class T, class Op> class queue_aggregation {
private:
  class node {
  public:
    T val, sum;
    node(const T &val, const T &sum) : val(val), sum(sum) {}
  };

  Op op;
  std::stack<node> front_stack, back_stack;

public:
  queue_aggregation(const Op &op = Op())
      : op(op), front_stack(), back_stack() {}

  bool empty() const { return front_stack.empty() && back_stack.empty(); }

  std::size_t size() const { return front_stack.size() + back_stack.size(); }

  T fold_all() const {
    assert(!empty());
    if (front_stack.empty()) {
      return back_stack.top().sum;
    } else if (back_stack.empty()) {
      return front_stack.top().sum;
    } else {
      return op(front_stack.top().sum, back_stack.top().sum);
    }
  }

  void push(const T &x) {
    if (back_stack.empty()) {
      back_stack.emplace(x, x);
    } else {
      T s{op(back_stack.top().sum, x)};
      back_stack.emplace(x, s);
    }
  }

  void pop() {
    assert(!empty());
    if (front_stack.empty()) {
      front_stack.emplace(back_stack.top().val, back_stack.top().val);
      back_stack.pop();
      while (!back_stack.empty()) {
        T s{op(back_stack.top().val, front_stack.top().sum)};
        front_stack.emplace(back_stack.top().val, s);
        back_stack.pop();
      }
    }
    front_stack.pop();
  }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);



    return 0;
}