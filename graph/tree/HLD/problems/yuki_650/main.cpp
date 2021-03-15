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

template< class T >
struct Matrix {
  vector< vector< T > > A;

  Matrix() {}

  Matrix(int n, int m) : A(n, vector< T >(m, 0)) {}

  Matrix(int n) : A(n, vector< T >(n, 0)) {};

  int height() const {
    return (int)(A.size());
  }

  int width() const {
    return (int)(A[0].size());
  }

  inline const vector< T > &operator[](int k) const {
    return (A.at(k));
  }

  inline vector< T > &operator[](int k) {
    return (A.at(k));
  }

  static Matrix I(int n) {
    Matrix mat(n);
    for(int i = 0; i < n; i++) mat[i][i] = 1;
    return (mat);
  }

  Matrix &operator+=(const Matrix &B) {
    size_t n = height(), m = width();
    assert(n == B.height() && m == B.width());
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        (*this)[i][j] += B[i][j];
    return (*this);
  }

  Matrix &operator-=(const Matrix &B) {
    size_t n = height(), m = width();
    assert(n == B.height() && m == B.width());
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        (*this)[i][j] -= B[i][j];
    return (*this);
  }

  Matrix &operator*=(const Matrix &B) {
    int n = height(), m = B.width(), p = width();
    assert(p == B.height());
    vector< vector< T > > C(n, vector< T >(m, 0));
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        for(int k = 0; k < p; k++)
          C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
    A.swap(C);
    return (*this);
  }

  Matrix &operator^=(long long k) {
    Matrix B = Matrix::I(height());
    while(k > 0) {
      if(k & 1) B *= *this;
      *this *= *this;
      k >>= 1LL;
    }
    A.swap(B.A);
    return (*this);
  }

  Matrix operator+(const Matrix &B) const {
    return (Matrix(*this) += B);
  }

  Matrix operator-(const Matrix &B) const {
    return (Matrix(*this) -= B);
  }

  Matrix operator*(const Matrix &B) const {
    return (Matrix(*this) *= B);
  }

  Matrix operator^(const long long k) const {
    return (Matrix(*this) ^= k);
  }

  friend ostream &operator<<(ostream &os, Matrix &p) {
    size_t n = p.height(), m = p.width();
    for(int i = 0; i < n; i++) {
      os << "[";
      for(int j = 0; j < m; j++) {
        os << p[i][j] << (j + 1 == m ? "]\n" : ",");
      }
    }
    return (os);
  }


  T determinant() {
    Matrix B(*this);
    assert(width() == height());
    T ret = 1;
    for(int i = 0; i < width(); i++) {
      int idx = -1;
      for(int j = i; j < width(); j++) {
        if(B[j][i] != 0) idx = j;
      }
      if(idx == -1) return (0);
      if(i != idx) {
        ret *= -1;
        swap(B[i], B[idx]);
      }
      ret *= B[i][i];
      T vv = B[i][i];
      for(int j = 0; j < width(); j++) {
        B[i][j] /= vv;
      }
      for(int j = i + 1; j < width(); j++) {
        T a = B[j][i];
        for(int k = 0; k < width(); k++) {
          B[j][k] -= B[i][k] * a;
        }
      }
    }
    return (ret);
  }
};

template<class Operator> class Tree {
	using TypeDist = typename Operator::TypeDist;
	size_t num;
	size_t ord;
	enum METHODS{
		MAKE_DEPTH,
		MAKE_CHILD,
		MAKE_PARENT,
		MAKE_SIZE,
		MAKE_SUBTREE,
		MAKE_ANCESTOR,
		MAKE_EOULERTOUR,
		MAKE_HEAVY_LIGHT_DECOMPOSITION,
		METHODS_SIZE,
	};
	array<int,METHODS_SIZE> executed_flag;
public:
	vector<vector<pair<size_t,TypeDist>>> edge;
	vector<size_t> depth;
	vector<size_t> order; // ord[i]: i番目に「その頂点からのdfsが終了した」頂点の番号．葉の方がdfsが早く完了するため，ord[0], ord[1]などには葉が，ord[num-1] には根が入る．葉から根の方に有向辺を引いたときのトポロジカル順序と思ってもOK．
	vector<size_t> reorder; // ord を逆にしたもの．根から葉の方に有向辺を引いたときのトポロジカル順序と思ってもOK．
	vector<TypeDist> dist;
	vector<pair<size_t,TypeDist>> parent;
	vector<vector<pair<size_t,TypeDist>>> child;
	vector<array<pair<size_t,TypeDist>,Operator::bit>> ancestor;
	vector<size_t> size;
	vector<vector<size_t>> subtree;
	vector<size_t> head;
	vector<size_t> hldorder;
	vector<size_t> eulertour;
	vector<pair<size_t,size_t>> eulertour_range;
	Tree(const int num):num(num),edge(num),depth(num,-1),order(num),dist(num),executed_flag(){}
	//O(1) anytime
	void make_edge(const int& from, const int& to, const TypeDist w = 1) {
		edge[from].push_back({to,w});
	}
	//O(N) anytime
	void make_depth(const int root) {
		executed_flag[MAKE_DEPTH]++;
		depth[root] = 0;
		dist[root] = Operator::unit_dist;
		ord = 0;
		dfs(root,-1);
		order[ord++] = root;
		reverse_copy(order.begin(),order.end(),back_inserter(reorder));
	}
	//O(N) anytime for forest
	void make_depth(void) {
		executed_flag[MAKE_DEPTH]++;
		ord = 0;
		for(size_t root = 0; root < num; ++root) {
			if(depth[root] != -1) continue;
			depth[root] = 0;
			dist[root] = Operator::unit_dist;
			dfs(root,-1);
			order[ord++] = root;
		}
		reverse_copy(order.begin(),order.end(),back_inserter(reorder));
	}
	//for make_depth
	void dfs(int curr, int prev){
		for(auto& e:edge[curr]){
			int next = e.first;
			if(next==prev) continue;
			depth[next] = depth[curr] + 1;
			dist[next]  = Operator::func_dist(dist[curr],e.second);
			dfs(next,curr);
			order[ord++] = next;
		}
	}
	//for make_eulertour
	void dfs(int from){
		eulertour.push_back(from);
		for(auto& e:child[from]){
			int to = e.first;            
			dfs(to);        
			eulertour.push_back(from);
		}
	}
	//O(N) after make_depth
	void make_parent(const int root = 0) {
		if(executed_flag[MAKE_PARENT]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		parent.resize(num,make_pair(num,Operator::unit_dist));
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[i]) if (depth[i] > depth[e.first]) parent[i] = e;
	}
	//O(N) after make_depth
	void make_child(const int root = 0) {
		if(executed_flag[MAKE_CHILD]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		child.resize(num);
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[i]) if (depth[i] < depth[e.first]) child[i].push_back(e);
	}
	//O(NlogN) after make_parent
	void make_ancestor(const int root = 0) {
		if(executed_flag[MAKE_ANCESTOR]++) return;
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		ancestor.resize(num);
		for (size_t i = 0; i < num; ++i) ancestor[i][0] = (parent[i].first!=num?parent[i]:make_pair(i,Operator::unit_lca));
		for (size_t j = 1; j < Operator::bit; ++j) {
			for (size_t i = 0; i < num; ++i) {
				size_t k = ancestor[i][j - 1].first;
				ancestor[i][j] = Operator::func_lca(ancestor[k][j - 1],ancestor[i][j - 1]);
			}
		}
	}
	//O(logN) after make_ancestor
	//return {lca,lca_dist} l and r must be connected
	pair<size_t,TypeDist> lca(size_t l, size_t r) {
		assert(executed_flag[MAKE_ANCESTOR]);
		if (depth[l] < depth[r]) swap(l, r);
		int diff = depth[l] - depth[r];
		auto ancl = make_pair(l,Operator::unit_lca);
		auto ancr = make_pair(r,Operator::unit_lca);
		for (int j = 0; j < Operator::bit; ++j) {
			if (diff & (1 << j)) {
				ancl = Operator::func_lca(ancestor[ancl.first][j],ancl);
			}
		}
		if(ancl.first==ancr.first) return ancl;
		for (int j = Operator::bit - 1; 0 <= j; --j) {
			if(ancestor[ancl.first][j].first!=ancestor[ancr.first][j].first) {
				ancl = Operator::func_lca(ancestor[ancl.first][j],ancl);
				ancr = Operator::func_lca(ancestor[ancr.first][j],ancr);
			}
		}
		ancl = Operator::func_lca(ancestor[ancl.first][0],ancl);
		ancr = Operator::func_lca(ancestor[ancr.first][0],ancr);
		return Operator::func_lca(ancl,ancr);
	}
	//O(N) anytime
	//pair<diameter,vertex_set>
	pair<TypeDist,vector<int>> diameter(void){
		make_depth(0);
		int root = max_element(dist.begin(), dist.end()) - dist.begin();
		make_depth(root);
		int leaf = max_element(dist.begin(), dist.end()) - dist.begin();
		make_parent();
		TypeDist d = dist[leaf];
		vector<int> v;
		while (leaf != root) {
			v.push_back(leaf);
			leaf = parent[leaf].first;
		}
		v.push_back(root);
		return make_pair(d,v);
	}
	//O(N^2) after make_depth
	void make_subtree(const int root = 0) {
		if(executed_flag[MAKE_SUBTREE]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		subtree.resize(num);
		for (size_t i = 0; i < num; ++i) subtree[i].push_back(i);
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[order[i]]) if (depth[order[i]] < depth[e.first]) for(auto k: subtree[e.first]) subtree[order[i]].push_back(k);
	}
	//O(N) after make_child
	void make_size(const int root = 0) {
		if(executed_flag[MAKE_SIZE]++) return;
		if(!executed_flag[MAKE_CHILD]) make_child(root);
		size.resize(num,1);
		for (size_t i:order) for (auto e : child[i]) size[i] += size[e.first];
	}
	//(N) after make_depth and make_child
	template<class TypeReroot> vector<TypeReroot> rerooting(vector<TypeReroot> rerootdp,vector<TypeReroot> rerootparent) {
		assert(executed_flag[MAKE_CHILD]);
		for(size_t pa:order) for(auto& e:child[pa]) rerootdp[pa] = Operator::func_reroot(rerootdp[pa],rerootdp[e.first]);
		for(size_t pa:reorder) {
			if(depth[pa]) rerootdp[pa] = Operator::func_reroot(rerootdp[pa],rerootparent[pa]);
			size_t m = child[pa].size();
			for(int j = 0; j < m && depth[pa]; ++j){
				size_t ch = child[pa][j].first;
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],rerootparent[pa]);
			}
			if(m <= 1) continue;
			vector<TypeReroot> l(m),r(m);
			for(int j = 0; j < m; ++j) {
				size_t ch = child[pa][j].first;
				l[j] = rerootdp[ch];
				r[j] = rerootdp[ch];
			}
			for(int j = 1; j+1 < m; ++j) l[j] = Operator::func_reroot_merge(l[j],l[j-1]);
			for(int j = m-2; 0 <=j; --j) r[j] = Operator::func_reroot_merge(r[j],r[j+1]);
			size_t chl = child[pa].front().first;
			size_t chr = child[pa].back().first;
			rerootparent[chl] = Operator::func_reroot(rerootparent[chl],r[1]);
			rerootparent[chr] = Operator::func_reroot(rerootparent[chr],l[m-2]);
			for(int j = 1; j+1 < m; ++j) {
				size_t ch = child[pa][j].first;
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],l[j-1]);
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],r[j+1]);
			}
		}
		return rerootdp;
	}
	//O(N) after make_depth,make_parent,make_child
	void make_heavy_light_decomposition(const int root = 0){
		if(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]++) return;
		if(!executed_flag[MAKE_SIZE]) make_size(root);
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		head.resize(num); // head[i]: 頂点 i から heavy edge を遡っていった時に最も根に近い頂点
		hldorder.resize(num); // hldorder[i]: hld 順序に並べた場合の 頂点 i が何番目にあるか．hld 順序では，heavy-path が必ず区間になっている & 部分木が必ず区間になっている
		iota(head.begin(),head.end(),0);

        // head を埋める
		for(size_t& pa:reorder) {
			pair<size_t,size_t> maxi = {0,num}; // maxi: (部分木サイズ，頂点)のタプルで，部分木サイズが最大のもの
			for(auto& e:child[pa]) maxi = max(maxi,{size[e.first],e.first});
			if(maxi.first) head[maxi.second] = head[pa]; //　pa から heavy edge が子の方向に生えているなら，heavy edge の先の頂点の head を pa の head と同じにする
		}

        // hldorder を埋める
		stack<size_t> st_head,st_sub;
		size_t cnt = 0;
		for(size_t& root:reorder){ // forest の場合への対応（根が複数ある）
			if(depth[root]) continue; 
			st_head.push(root); // ここから dfs 開始． heavy path を優先して進むような dfs
			while(st_head.size()){
				size_t h = st_head.top();
				st_head.pop();
				st_sub.push(h);
				while (st_sub.size()){
					size_t pa = st_sub.top();
					st_sub.pop();
					hldorder[pa] = cnt++;
					for(auto& e:child[pa]) {
						if(head[e.first]==head[pa]) st_sub.push(e.first);
						else st_head.push(e.first);
					}
				}				
			}
		}
	}
	//after hld type 0: vertex, 1: edge
	vector<pair<size_t,size_t>> path(size_t u,size_t v,int type = 0) {
        // 辺クエリの場合は親方向への辺を処理することにしておく
		assert(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]);
		vector<pair<size_t,size_t>> path;
		while(1){
			if(hldorder[u]>hldorder[v]) swap(u,v);
			if(head[u]!=head[v]) {
				path.push_back({hldorder[head[v]],hldorder[v]});
				v=parent[head[v]].first;
			}
			else {
				path.push_back({hldorder[u],hldorder[v]});
				break;
			}
		}
		reverse(path.begin(),path.end());
		if(type) path.front().first++; // 辺クエリの場合，LCAだけ省略
		return path;
	}
	size_t hld_lca(size_t u,size_t v){
		assert(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]);
		while(1){
			if(hldorder[u]>hldorder[v]) swap(u,v);
			if(head[u]==head[v]) return u;
			v=parent[head[v]].first;
		}
	}
	//O(N) after make_child and make_parent
	void make_eulertour(const int root = 0){
		if(executed_flag[MAKE_EOULERTOUR]++) return;
		if(!executed_flag[MAKE_CHILD]) make_child(root);
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		dfs(reorder.front());
		eulertour_range.resize(num);
		for(int i = 0; i < eulertour.size(); ++i) eulertour_range[eulertour[i]].second = i;
		for(int i = eulertour.size()-1; 0 <= i; --i) eulertour_range[eulertour[i]].first = i;
	}
};
//depth,dist
//https://atcoder.jp/contests/abc126/tasks/abc126_d
//child
//https://atcoder.jp/contests/abc133/tasks/abc133_e
//lca
//https://atcoder.jp/contests/abc014/tasks/abc014_4
//weighted lca
//https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h
//https://atcoder.jp/contests/cf16-tournament-round1-open/tasks/asaporo_c
//diameter
//https://atcoder.jp/contests/agc033/tasks/agc033_c
//subtree
//https://atcoder.jp/contests/code-thanks-festival-2018/tasks/code_thanks_festival_2018_f
//rerooting
//https://yukicoder.me/problems/no/922
//size
//https://yukicoder.me/problems/no/872
//eulerTour
//https://yukicoder.me/problems/no/900
//hld
//https://yukicoder.me/problems/no/399
//https://yukicoder.me/problems/no/650
template<class T> struct TreeOperator{
	using TypeDist = T;
	inline static constexpr size_t bit = 20;
	inline static constexpr TypeDist unit_dist = 0;
	inline static constexpr TypeDist unit_lca = 0;
	inline static constexpr TypeDist func_dist(const TypeDist& parent,const TypeDist& w){return parent+w;}
	inline static constexpr pair<size_t,TypeDist> func_lca(const pair<size_t,TypeDist>& l,const pair<size_t,TypeDist>& r){return make_pair(l.first,l.second+r.second);}
	template<class TypeReroot> inline static constexpr TypeReroot func_reroot(const TypeReroot& l,const TypeReroot& r) {
		return {l.first+r.first+r.second,l.second+r.second};
	}
	template<class TypeReroot> inline static constexpr TypeReroot func_reroot_merge(const TypeReroot& l,const TypeReroot& r) {
		return {l.first+r.first,l.second+r.second};
	}
};

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
using vm = vector<mint>;
using vvm = vector<vm>;

ostream& operator << (ostream& os, const mint v){
os << v.value(); return os;
}

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

using S = Matrix<mint>;

S op(S x, S y){
    return x * y; // ?
}

S e(){
    Matrix<mint> m;
    return m.I(2);
}

int main(){

    ll N;
    cin >> N;

    V<pll> E;

    Tree<TreeOperator<ll>> tree(N);
    REP(i, N-1){
        ll a, b;
        cin >> a >> b;
        tree.make_edge(a, b);
        tree.make_edge(b, a);
        E.emplace_back(a, b);
    }

    tree.make_heavy_light_decomposition();

    auto eid2pos = [&](ll idx){
        ll u = E[idx].first;
        ll v = E[idx].second;
        ll pos = -1;
        if(tree.depth[u]>tree.depth[v]) pos = u;
        else pos = v;
        return tree.hldorder[pos];
    };

    Matrix<mint> m;
    V<S> v(N, m.I(2));

    segtree<S, op, e> seg(v);

    ll Q;
    cin >> Q;
    REP(q, Q){
        char c;
        cin >> c;
        if(c == 'g'){
            ll u, v;
            cin >> u >> v;
            auto paths = tree.path(u, v, 1);
            S res = m.I(2);
            for(auto p: paths){
                res = res * seg.prod(p.first, p.second+1);
            }
            cout << res[0][0] spa res[0][1] spa res[1][0] spa res[1][1] << "\n"; 
        }else{
            ll vdx, a, b, c, d;
            cin >> vdx >> a >> b >> c >> d;
            ll idx = eid2pos(vdx);
            S mat(2, 2);
            mat[0][0] = a;
            mat[0][1] = b;
            mat[1][0] = c;
            mat[1][1] = d;
            seg.set(idx, mat);
        }
    }


    return 0;
}