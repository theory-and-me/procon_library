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

// https://mugen1337.hatenablog.com/entry/2020/10/14/134022

// 閉区間の範囲を管理
template<typename T>
struct RangeSet{
    set<pair<T,T>> st;
    T TINF;
 
    RangeSet(){
        TINF=numeric_limits<T>::max()/2;
        st.emplace(TINF,TINF);
        st.emplace(-TINF,-TINF);
    }
    // [l,r] covered?
    bool covered(T l,T r){
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        return ite->first<=l and r<=ite->second;
    }
    bool covered(T x){
        return covered(x,x);
    }
    // [l, r]がカバーされているなら，その区間を返す. されていないなら[-TINF,-TINF]を返す
    pair<T,T> covered_by(T l,T r){
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if(ite->first<=l and r<=ite->second) return *ite;
        return make_pair(-TINF,-TINF);
    }
    pair<T,T> covered_by(T x){
        return covered_by(x,x);
    }
    // insert[l,r], 増加量を返す
    T insert(T l,T r){
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if(ite->first<=l and r<=ite->second) return T(0);
        T sum_erased=T(0);
        if(ite->first<=l and l<=ite->second+1){
            l=ite->first;
            sum_erased+=ite->second-ite->first+1;
            ite=st.erase(ite);
        }else ite=next(ite);
        while(r>ite->second){
            sum_erased+=ite->second-ite->first+1;
            ite=st.erase(ite);
        }
        if(ite->first-1<=r and r<=ite->second){
            sum_erased+=ite->second-ite->first+1;
            r=ite->second;
            st.erase(ite);
        }
        st.emplace(l,r);
        return r-l+1-sum_erased;
    }
    T insert(T x){
        return insert(x,x);
    }
    // erase [l,r], 減少量を返す
    T erase(T l,T r){
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if(ite->first<=l and r<=ite->second){
            // 完全に1つの区間に包含されている
            if(ite->first<l)  st.emplace(ite->first,l-1);
            if(r<ite->second) st.emplace(r+1,ite->second);
            st.erase(ite);
            return r-l+1;
        }
 
        T ret=T(0);
        if(ite->first<=l and l<=ite->second){
            ret+=ite->second-l+1;// 消えた
            if(ite->first<l) st.emplace(ite->first,l-1);
            ite=st.erase(ite);// 次へ
        }else ite=next(ite);
        while(ite->second<=r){
            ret+=ite->second-ite->first+1;
            ite=st.erase(ite);
        }
        // 右端が区間の間にあるか
        if(ite->first<=r and r<=ite->second){
            ret+=r-ite->first+1;
            if(r<ite->second) st.emplace(r+1,ite->second);
            st.erase(ite);
        }
        return ret;
    }
    T erase(T x){
        return erase(x,x);
    }
    // number of range
    int size(){
        return (int)st.size()-2;
    }
    // mex [x,~)
    int mex(T x=0){
        auto ite=prev(st.lower_bound({x+1,x+1}));
        if(ite->first<=x and x<=ite->second) return ite->second+1;
        else return x;
    }
    void output(){
        cout<<"RangeSet : ";
        for(auto &p:st){
            if(p.first==-TINF or p.second==TINF) continue;
            cout<<"["<<p.first<<", "<<p.second<<"] ";
        }
        cout<<"\n";
    }
};


//  verified @ https://codeforces.com/contest/915/problem/E
int main(){

    ll n, q;
    cin >> n >> q;

    RangeSet<ll> rs;
    ll res = n;
    rs.insert(0, n-1);

    REP(i, q){
        ll k, l, r;
        cin >> l >> r >> k;
        l--, r--;
        if(k == 1){
            res -= rs.erase(l, r);
            cout << res << "\n";
        }else{
            res += rs.insert(l, r);
            cout << res << "\n";
        }
    }

    return 0;
}