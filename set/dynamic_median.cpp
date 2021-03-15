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

template <typename T>
struct dynamic_median{
    // 値の追加クエリと中央値クエリを捌くデータ構造
    // 二つの priority_queue をバランスさせながら中央値を管理する
    // 座圧がいらないのが楽

    priority_queue<T> left;
    priority_queue<T, vector<T>, greater<T>> right;
    T l_sum = 0, r_sum = 0;

    dynamic_median(){}

    void add_val(T v){
        if((int)left.size() > (int)right.size()){
            T t = left.top();
            if(v >= t){
                right.push(v);
                r_sum += v;
            }else{
                left.pop();
                l_sum -= t;
                left.push(v);
                l_sum += v;
                right.push(t);
                r_sum += t;
            }
        }else{
            if(left.empty()){
                left.push(v);
                l_sum += v;
            }else{
                T t = right.top();
                if(v <= t){
                    left.push(v);
                    l_sum += v;
                }else{
                    right.pop();
                    r_sum -= t;
                    right.push(v);
                    r_sum += v;
                    left.push(t);
                    l_sum += t;
                }
            }
        }
    }

    T get_median(){
        assert(!left.empty());
        return left.top();
    }
};

// verified @ https://atcoder.jp/contests/abc127/tasks/abc127_f
int main(){

    ll Q;
    cin >> Q;

    dynamic_median<ll> dm;

    ll S = 0;
    ll t, a, b;
    while(Q--){
        cin >> t;
        t--;
        if(!t){
            cin >> a >> b;
            S += b;
            dm.add_val(a);
        }else{
            ll res = S;
            ll med = dm.get_median();
            res += (ll)(dm.left.size()) * med - dm.l_sum;
            res += -(ll)(dm.right.size()) * med + dm.r_sum;
            cout << med spa res << "\n";
        }
    }

    return 0;
}