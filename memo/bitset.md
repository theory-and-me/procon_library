# bitset 高速化について
* bitset<N> は長さNの01配列だと思って良い　集合としても捉えられる
* bitset は and, or, xorなどの計算が速い(64倍)
* 例えば, bit値を持つdpが高速に計算できる．Median Sum など．https://atcoder.jp/contests/agc020/tasks/agc020_c

