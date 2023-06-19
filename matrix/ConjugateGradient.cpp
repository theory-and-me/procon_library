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

namespace matrix_ {
struct has_id_method_impl {
    template <class T_> static auto check(T_ *) -> decltype(T_::id(), std::true_type());
    template <class T_> static auto check(...) -> std::false_type;
};
template <class T_> struct has_id : decltype(has_id_method_impl::check<T_>(nullptr)) {};
} // namespace matrix_

template <typename T> struct matrix {
    int H, W;
    std::vector<T> elem;
    typename std::vector<T>::iterator operator[](int i) { return elem.begin() + i * W; }
    inline T &at(int i, int j) { return elem[i * W + j]; }
    inline T get(int i, int j) const { return elem[i * W + j]; }
    int height() const { return H; }
    int width() const { return W; }
    std::vector<std::vector<T>> vecvec() const {
        std::vector<std::vector<T>> ret(H);
        for (int i = 0; i < H; i++) {
            std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));
        }
        return ret;
    }
    operator std::vector<std::vector<T>>() const { return vecvec(); }
    matrix() = default;
    matrix(int H, int W) : H(H), W(W), elem(H * W) {}
    matrix(const std::vector<std::vector<T>> &d) : H(d.size()), W(d.size() ? d[0].size() : 0) {
        for (auto &raw : d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));
    }

    template <typename T2, typename std::enable_if<matrix_::has_id<T2>::value>::type * = nullptr>
    static T2 _T_id() {
        return T2::id();
    }
    template <typename T2, typename std::enable_if<!matrix_::has_id<T2>::value>::type * = nullptr>
    static T2 _T_id() {
        return T2(1);
    }

    static matrix Identity(int N) {
        matrix ret(N, N);
        for (int i = 0; i < N; i++) ret.at(i, i) = _T_id<T>();
        return ret;
    }

    matrix operator-() const {
        matrix ret(H, W);
        for (int i = 0; i < H * W; i++) ret.elem[i] = -elem[i];
        return ret;
    }
    matrix operator*(const T &v) const {
        matrix ret = *this;
        for (auto &x : ret.elem) x *= v;
        return ret;
    }
    matrix operator/(const T &v) const {
        matrix ret = *this;
        const T vinv = _T_id<T>() / v;
        for (auto &x : ret.elem) x *= vinv;
        return ret;
    }
    matrix operator+(const matrix &r) const {
        matrix ret = *this;
        for (int i = 0; i < H * W; i++) ret.elem[i] += r.elem[i];
        return ret;
    }
    matrix operator-(const matrix &r) const {
        matrix ret = *this;
        for (int i = 0; i < H * W; i++) ret.elem[i] -= r.elem[i];
        return ret;
    }
    matrix operator*(const matrix &r) const {
        matrix ret(H, r.W);
        for (int i = 0; i < H; i++) {
            for (int k = 0; k < W; k++) {
                for (int j = 0; j < r.W; j++) ret.at(i, j) += this->get(i, k) * r.get(k, j);
            }
        }
        return ret;
    }
    matrix &operator*=(const T &v) { return *this = *this * v; }
    matrix &operator/=(const T &v) { return *this = *this / v; }
    matrix &operator+=(const matrix &r) { return *this = *this + r; }
    matrix &operator-=(const matrix &r) { return *this = *this - r; }
    matrix &operator*=(const matrix &r) { return *this = *this * r; }
    bool operator==(const matrix &r) const { return H == r.H and W == r.W and elem == r.elem; }
    bool operator!=(const matrix &r) const { return H != r.H or W != r.W or elem != r.elem; }
    bool operator<(const matrix &r) const { return elem < r.elem; }
    matrix pow(int64_t n) const {
        matrix ret = Identity(H);
        bool ret_is_id = true;
        if (n == 0) return ret;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {
            if (!ret_is_id) ret *= ret;
            if ((n >> i) & 1) ret *= (*this), ret_is_id = false;
        }
        return ret;
    }
    std::vector<T> pow_vec(int64_t n, std::vector<T> vec) const {
        matrix x = *this;
        while (n) {
            if (n & 1) vec = x * vec;
            x *= x;
            n >>= 1;
        }
        return vec;
    };
    matrix transpose() const {
        matrix ret(W, H);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i, j);
        }
        return ret;
    }
    // Gauss-Jordan elimination
    // - Require inverse for every non-zero element
    // - Complexity: O(H^2 W)
    template <typename T2, typename std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const matrix<T2> &mtr, int h, int c) noexcept {
        int piv = -1;
        for (int j = h; j < mtr.H; j++) {
            if (mtr.get(j, c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))
                piv = j;
        }
        return piv;
    }
    template <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const matrix<T2> &mtr, int h, int c) noexcept {
        for (int j = h; j < mtr.H; j++) {
            if (mtr.get(j, c) != T2()) return j;
        }
        return -1;
    }
    matrix gauss_jordan() const {
        int c = 0;
        matrix mtr(*this);
        std::vector<int> ws;
        ws.reserve(W);
        for (int h = 0; h < H; h++) {
            if (c == W) break;
            int piv = choose_pivot(mtr, h, c);
            if (piv == -1) {
                c++;
                h--;
                continue;
            }
            if (h != piv) {
                for (int w = 0; w < W; w++) {
                    std::swap(mtr[piv][w], mtr[h][w]);
                    mtr.at(piv, w) *= -_T_id<T>(); // To preserve sign of determinant
                }
            }
            ws.clear();
            for (int w = c; w < W; w++) {
                if (mtr.at(h, w) != T()) ws.emplace_back(w);
            }
            const T hcinv = _T_id<T>() / mtr.at(h, c);
            for (int hh = 0; hh < H; hh++)
                if (hh != h) {
                    const T coeff = mtr.at(hh, c) * hcinv;
                    for (auto w : ws) mtr.at(hh, w) -= mtr.at(h, w) * coeff;
                    mtr.at(hh, c) = T();
                }
            c++;
        }
        return mtr;
    }
    int rank_of_gauss_jordan() const {
        for (int i = H * W - 1; i >= 0; i--) {
            if (elem[i] != 0) return i / W + 1;
        }
        return 0;
    }
    int rank() const { return gauss_jordan().rank_of_gauss_jordan(); }

    T determinant_of_upper_triangle() const {
        T ret = _T_id<T>();
        for (int i = 0; i < H; i++) ret *= get(i, i);
        return ret;
    }
    int inverse() {
        assert(H == W);
        std::vector<std::vector<T>> ret = Identity(H), tmp = *this;
        int rank = 0;
        for (int i = 0; i < H; i++) {
            int ti = i;
            while (ti < H and tmp[ti][i] == 0) ti++;
            if (ti == H) {
                continue;
            } else {
                rank++;
            }
            ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);
            T inv = _T_id<T>() / tmp[i][i];
            for (int j = 0; j < W; j++) ret[i][j] *= inv;
            for (int j = i + 1; j < W; j++) tmp[i][j] *= inv;
            for (int h = 0; h < H; h++) {
                if (i == h) continue;
                const T c = -tmp[h][i];
                for (int j = 0; j < W; j++) ret[h][j] += ret[i][j] * c;
                for (int j = i + 1; j < W; j++) tmp[h][j] += tmp[i][j] * c;
            }
        }
        *this = ret;
        return rank;
    }
    friend std::vector<T> operator*(const matrix &m, const std::vector<T> &v) {
        assert(m.W == int(v.size()));
        std::vector<T> ret(m.H);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++) ret[i] += m.get(i, j) * v[j];
        }
        return ret;
    }
    friend std::vector<T> operator*(const std::vector<T> &v, const matrix &m) {
        assert(int(v.size()) == m.H);
        std::vector<T> ret(m.W);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++) ret[j] += v[i] * m.get(i, j);
        }
        return ret;
    }
    std::vector<T> prod(const std::vector<T> &v) const { return (*this) * v; }
    std::vector<T> prod_left(const std::vector<T> &v) const { return v * (*this); }
    template <class OStream> friend OStream &operator<<(OStream &os, const matrix &x) {
        os << "[(" << x.H << " * " << x.W << " matrix)";
        os << "\n[column sums: ";
        for (int j = 0; j < x.W; j++) {
            T s = 0;
            for (int i = 0; i < x.H; i++) s += x.get(i, j);
            os << s << ",";
        }
        os << "]";
        for (int i = 0; i < x.H; i++) {
            os << "\n[";
            for (int j = 0; j < x.W; j++) os << x.get(i, j) << ",";
            os << "]";
        }
        os << "]\n";
        return os;
    }
    template <class IStream> friend IStream &operator>>(IStream &is, matrix &x) {
        for (auto &v : x.elem) is >> v;
        return is;
    }
};


template <typename T> matrix<T> ConjugateGradient(const matrix<T> &A, const matrix<T> &b, T epsilon){
    int N = A.height();
    matrix<T> x(N, 1);
    matrix<T> r = b - A * x;
    matrix<T> p = r;

    auto inner_product = [](const matrix<T> &first_vector, const matrix<T> &second_vector){
        return (first_vector.transpose() * second_vector).get(0, 0);
    };

    for(int k=0;;k++){
        T alpha = inner_product(r, p) / inner_product(p, A * p);
        x += p * alpha;
        r -= A * p * alpha;
        T beta = - inner_product(r, A * p) / inner_product(p, A * p);
        p *= beta;
        p += r;
        cerr << k << " th iteration:  r = " << inner_product(r, r) << endl; 

        if(sqrt(inner_product(r, r)) < epsilon * sqrt(inner_product(b, b))){
            cerr << "total iteration: " << k << endl; 
            break;
        }
    }

    return x;
}

int main(){

    matrix A(vector<vector<double>>{
        {6, 2}, 
        {2, 1}
    });

    matrix b(vector<vector<double>>{
        {5}, 
        {8}
    });

    auto x = ConjugateGradient(A, b, 1e-10);

    cout << x << endl;

    return 0;
}