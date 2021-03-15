#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

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

// 以下の機能をサポートしたデータ構造 acl/segtree を利用
// 1. insert_val(int v): 値 v を S に挿入
// 2. delete_val(int v): 値 v を S から削除
// 3. get_kth(int k): S の中の k 番目の値を出力

int op(int a, int b) {return a+b;}
int e() {return 0;}
int target;
bool f(int v){return v < target;}


int main(){
    // not verified

    int v_max = 100000; // [1, 2, ..., v_max] を扱える
    V<int> init(v_max+1, 0);
    segtree<int, op, e> seg(init);

    auto insert_val = [&](int v){
        seg.set(v, 1);
    };

    auto delete_val = [&](int v){
        seg.set(v, 0);
    };

    auto get_kth = [&](int k){
        // k は 1-indexed
        target = k;
        ll tmp = seg.max_right<f>(0);
        return tmp;
    };

    auto enumerate_set = [&](){
        // S の中身を全て表示
        // O(v_max) かかることに注意
        for(int i=0;i<v_max+1;i++){
            if(seg.get(i)) cout << i << " ";
        }
        cout << "\n";
    };

    // example
    insert_val(3);
    insert_val(6);
    insert_val(10);

    enumerate_set();

    // cout << get_kth(0) << endl; // fail f(0) = false のため 
    cout << get_kth(1) << endl;
    cout << get_kth(2) << endl;
    cout << get_kth(3) << endl;

    delete_val(6);

    cout << get_kth(1) << endl;
    cout << get_kth(2) << endl;
    cout << get_kth(3) << endl; // 要素がk個未満の場合はvmax+1を返す

    enumerate_set();




    return 0;
}