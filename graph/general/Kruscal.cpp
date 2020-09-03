template<typename T>
struct edge{
  int u, v, idx; T w;
  edge(int u, int v, T w) : u(u), v(v), w(w) {}
};
template<typename T>
using edges = vector<edge<T>>;

struct UnionFindSize {
    vector<int> par;
    
    UnionFindSize(int n) : par(n, -1) { }
    void init(int n) { par.assign(n, -1); }
    
    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }
    
    bool issame(int x, int y) {
        return root(x) == root(y);
    }
    
    bool merge(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y); // merge technique
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    
    int size(int x) {
        return -par[root(x)];
    }

    void print(){
		cout << "uf: ";
		for(int i=0;i<(int)par.size();i++) cout << root(i) << " ";
		cout << endl;
	}
};

template<typename T>
T Kruscal(edges<T> &E, int N){
  sort(E.begin(), E.end()), [](const edge<T> &x, const edge<T> &y){
    return x.w < y.w;
  };
  UnionFindSize uf(N);
  T res = 0;
  for(auto &e: E){
    if(uf.merge(e.u, e.v)) res += e.w;
  }
  return res;
}