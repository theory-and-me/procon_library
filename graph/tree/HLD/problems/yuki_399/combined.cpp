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
#include <iostream>
#include <vector>
namespace atcoder {

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
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

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
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
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
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

using S = pll;
using F = ll;

S op(S x, S y){
    return {x.first+y.first, x.second+y.second};
}

S e(){
    return {0, 0};
}

S mapping(F a, S x){
    return {x.first + a * x.second, x.second};
}

F composition(F a, F b){
    return a+b;
}

F id(){
    return 0;
}


int main(){

    ll N;
    cin >> N;
    Tree<TreeOperator<ll>> tree(N);
    REP(i, N-1){
        ll u, v;
        cin >> u >> v;
        u--, v--;
        tree.make_edge(u, v);
        tree.make_edge(v, u);
    }
    tree.make_heavy_light_decomposition();

    V<pll> v(N, {1, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

    ll Q;
    cin >> Q;
    ll res = 0;
    REP(q, Q){
        ll A, B;
        cin >> A >> B;
        A--, B--;
        auto paths = tree.path(A, B);
        for(auto p: paths){
            ll tmp = seg.prod(p.first, p.second+1).first; // 頂点クエリの場合はアップデートするだけならhldorderにアクセスする必要はない．頂点vの値が欲しい時はseg.get(hldorder[v])で取得
            res += tmp;
            seg.apply(p.first, p.second+1, 1);   
        }
    }

    cout << res << endl;

    return 0;
}
