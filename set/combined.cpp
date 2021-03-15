#include <bits/stdc++.h>

#include <algorithm>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder

#include <cassert>
#include <vector>

namespace atcoder {

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    segtree(int n) : segtree(std::vector<S>(n, e())) {}
    segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace atcoder

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

// 以下の機能をサポートしたデータ構造 acl/segtree を利用 値が大きい場合は座圧が必要
// 1. insert_val(int v): 値 v を S に挿入
// 2. delete_val(int v): 値 v を S から削除
// 3. get_kth(int k): S の中の k 番目の値を出力

int op_for_kth(int a, int b) {return a+b;}
int e_for_kth() {return 0;}
int target_for_kth;
bool f_for_kth(int v){return v < target_for_kth;}
const int v_max = 2000000; // [0, 1, ..., v_max-1] を扱える
V<int> init_for_kth(v_max+1, 0);
segtree<int, op_for_kth, e_for_kth> seg_for_kth(init_for_kth);

struct dynamic_kth_segtree{

    // 実装内部では1-indexedで扱っていることに注意．これは，acl/segtree の f(e()) = true という要件を満たすため

    void insert_val(int v){
        int tmp = seg_for_kth.get(v+1);
        seg_for_kth.set(v+1, tmp+1);
    };

    void delete_val(int v){
        int tmp = seg_for_kth.get(v+1);
        assert(tmp>0);
        seg_for_kth.set(v+1, tmp-1);
    }

    int get_kth(int k){
        // k は 1-indexed
        target_for_kth = k;
        ll tmp = seg_for_kth.max_right<f_for_kth>(0);
        if(tmp-1 == v_max) return -1;
        else return tmp-1;
    };

    void enumerate_elements(){
        // S の中身を全て表示
        // O(v_max) かかることに注意
        for(int i=0;i<v_max+1;i++){
            int v = seg_for_kth.get(i);
            for(int j=0;j<v;j++) cout << i-1 << " ";
        }
        cout << "\n";
    };
};


// int main(){
//     // EXAMPLE

//     dynamic_kth_segtree dks;
//     dks.insert_val(3);
//     dks.insert_val(6);
//     dks.insert_val(10);

//     dks.enumerate_elements();

//     // cout << dks.get_kth(0) << endl; // fail f(0) = false のため 
//     cout << dks.get_kth(1) << endl;
//     cout << dks.get_kth(2) << endl;
//     cout << dks.get_kth(3) << endl;

//     dks.delete_val(6);

//     cout << dks.get_kth(1) << endl;
//     cout << dks.get_kth(2) << endl;
//     cout << dks.get_kth(3) << endl; // 要素がk個未満の場合はvmax+1を返す

//     dks.enumerate_elements();
//     return 0;
// }

int main(){
    ll n, q;
    cin >> n >> q;

    dynamic_kth_segtree dks;

    REP(i, n){
        ll a;
        cin >> a;
        dks.insert_val(a);
    }
    while(q--){
        ll k;
        cin >> k;
        if(k>0){
            dks.insert_val(k);
        }else{
            ll v = dks.get_kth(-k);
            dks.delete_val(v);
        }
    }

    ll res = dks.get_kth(1);
    cout << (res == -1 ? 0 : res) << endl;

    return 0;
}
