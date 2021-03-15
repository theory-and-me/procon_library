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
struct DynamicKthPQ{
    T TINF, sum_L, sum_R;
    priority_queue<T, vector<T>, greater<T>> pq_R;
    priority_queue<T> pq_L;

    DynamicKthPQ(){
        TINF = numeric_limits<T>::max()/2;
        sum_L = 0;
        sum_R = 0;
    }

    // pq_LのサイズがKになるように調整
    // これが遅い場合使えないので注意
    void adjust_Kth(int K){
        assert(K > 0); // guarantee 1-indexed

        while((int)pq_L.size() < K){
            T tmp = pq_R.top();
            pq_R.pop();
            sum_R -= tmp;

            pq_L.push(tmp);
            sum_L += tmp;
        }

        while((int)pq_L.size() > K){
            T tmp = pq_L.top();
            pq_L.pop();
            sum_L -= tmp;

            pq_R.push(tmp);
            sum_R += tmp;
        }

        assert((int)pq_L.size() == K);

        return;
    }    

    // 下からK番目の値(1-indexed)を出力
    T get_Kth(int K){
        adjust_Kth(K);
        return pq_L.top();
    }

    // x を集合に挿入
    void insert(T x){
        T front_L = (pq_L.empty() ? TINF : pq_L.top());

        if(x > front_L){
            pq_R.push(x);
            sum_R += x; 
        }else{
            pq_L.push(x);
            sum_L += x; 
        }
        return;
    }

};

// verified @ https://atcoder.jp/contests/abc127/tasks/abc127_f
int main(){

    ll Q;
    cin >> Q;

    ll B = 0;
    ll cnt = 0;
    DynamicKthPQ<ll> dkpq;

    while(Q--){
        ll t;
        cin >> t;
        if(t == 1){
            ll a, b;
            cin >> a >> b;
            cnt++;
            B += b;
            dkpq.insert(a);
        }else{
            ll res = 0;
            ll v = dkpq.get_Kth((cnt+1)/2);
            ll Lsz = dkpq.pq_L.size();
            ll Rsz = dkpq.pq_R.size();
            ll Lsum = dkpq.sum_L;
            ll Rsum = dkpq.sum_R;
            res += Lsz*v - Lsum;
            res += Rsum - Rsz*v;
            res += B;
            cout << v spa res << endl;
        }
    }

    return 0;
}