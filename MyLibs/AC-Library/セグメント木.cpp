#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
using ll = long long;

// ============================================================
// AC-Library SegTree（セグメント木）まとめ
//
// 使用頻度：★★★★☆
// 主な用途：一点更新，区間の最大値・最小値・合計などの取得
// キーワード：set，get，prod，all_prod
//
// ------------------------------------------------------------
// 基本操作
//
// segtree<S, op, e> st(n);
//   長さnのセグメント木を作成する．全要素は単位元e()で初期化される．
// segtree<S, op, e> st(A);
//   vector<S> Aの内容でセグメント木を初期化する．
//
// st.set(p, x);       // A[p]をxへ変更．O(log N)
// st.get(p);          // A[p]を取得．O(1)
// st.prod(l, r);      // A[l:r)の演算結果．O(log N)
// st.all_prod();      // A全体の演算結果．O(1)
//
// ------------------------------------------------------------
// 【パターン1】区間最大値（最小値）
// 【パターン2】区間合計
// 【パターン3】複数情報を持つセグ木：括弧列
// ============================================================

// ============================================================
// 【パターン1】区間最大値（最小値）
// ============================================================
#if 1

#include <atcoder/segtree>
using namespace atcoder;
constexpr ll LINF = 1LL << 60;
// ※ ±LINFを単位元にする場合，実際の値がその範囲内であることを確認する．

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<ll> A{5, 2, 8, 4, 6};

    // 区間最大値
    constexpr auto op = [](ll a, ll b) { return max(a, b); }; // 2項間演算
    constexpr auto e = []() { return -LINF; };                // 単位元

    // 区間最小値の場合
    // constexpr auto op = [](ll a, ll b) { return min(a, b); };
    // constexpr auto e = []() { return LINF; };

    segtree<ll, op, e> st(A);                                 // Aの初期値で作成

    cout << "A = {5, 2, 8, 4, 6}\n";

    cout << "\n===== prod()による区間最大値 =====\n";
    cout << "A[1:4)の最大値: " << st.prod(1, 4) << '\n';

    cout << "\n===== set()による一点更新 =====\n";
    st.set(2, 10);                           // A[2]を10へ変更
    cout << "A[2]を10へ変更\n";
    cout << "A[1:4)の最大値: " << st.prod(1, 4) << '\n';

    cout << "\n===== get()による一点取得 =====\n";
    cout << "A[2]の値: " << st.get(2) << '\n';

    cout << "\n===== all_prod()による配列全体の最大値 =====\n";
    cout << "A全体の最大値: " << st.all_prod() << '\n';

    return 0;
}

#endif


// ============================================================
// 【パターン2】区間合計
// ============================================================
#if 0

#include <atcoder/segtree>
using namespace atcoder;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<ll> A{5, 2, 8, 4, 6};

    // 区間合計
    constexpr auto op = [](ll a, ll b) { return a + b; }; // 2項間演算
    constexpr auto e = []() { return 0LL; };              // 単位元
    segtree<ll, op, e> st(A);                             // Aの初期値で作成

    cout << "A = {5, 2, 8, 4, 6}\n";

    cout << "\n===== prod()による区間合計 =====\n";
    cout << "A[1:4)の合計: " << st.prod(1, 4) << '\n';

    cout << "\n===== set()による一点更新 =====\n";
    st.set(2, 10);                           // A[2]を10へ変更
    cout << "A[2]を10へ変更\n";
    cout << "A[1:4)の合計: " << st.prod(1, 4) << '\n';

    cout << "\n===== get()による一点取得 =====\n";
    cout << "A[2]の値: " << st.get(2) << '\n';

    cout << "\n===== all_prod()による配列全体の合計 =====\n";
    cout << "A全体の合計: " << st.all_prod() << '\n';

    return 0;
}

#endif


// ============================================================
// 【パターン3】複数情報を持つセグ木：括弧列
//
// '('を+1，')'を-1とする．
// 各ノードには次の2つの情報を持たせる．
//   first ：区間全体の合計
//   second：区間先頭を0とした累積和の最小値
//
// 正しい括弧列の条件：
//   ・区間全体の合計 == 0
//   ・累積和の最小値 >= 0
// ============================================================
#if 0

#include <atcoder/segtree>
using namespace atcoder;
constexpr ll LINF = 1LL << 60;

using S = pair<ll, ll>;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    string str = "(()())";

    vector<S> A;
    for (char c : str) {
        if (c == '(') A.push_back({1, 1});
        else          A.push_back({-1, -1});
    }

    // first：区間合計
    // second：区間先頭を0とした累積和の最小値
    constexpr auto op = [](S a, S b) {
        return S{
            a.first + b.first,
            min(a.second, a.first + b.second)
        };
    };

    constexpr auto e = []() {
        return S{0LL, LINF};
    };

    segtree<S, op, e> st(A);

    cout << "S = \"(()())\"\n";

    cout << "\n===== prod()による括弧列の判定 =====\n";
    auto x = st.prod(0, 6);
    cout << "S[0:6)は正しい括弧列: "
         << (x.first == 0 && x.second >= 0 ? "Yes" : "No") << '\n';

    cout << "\n===== set()による一点更新 =====\n";
    st.set(1, S{-1, -1});                  // S[1]を'('から')'へ変更
    cout << "S[1]を'('から')'へ変更\n";

    x = st.prod(0, 6);
    cout << "S[0:6)は正しい括弧列: "
         << (x.first == 0 && x.second >= 0 ? "Yes" : "No") << '\n';

    return 0;
}

#endif


// ============================================================
// 補足
// ============================================================
// セグメント木と遅延セグメント木の使い分け
//
// ・一点更新だけでよい　-> セグメント木（segtree）
// ・区間更新が必要     ->  遅延セグメント木（lazy_segtree）
//
// ============================================================
// S, op, e
//
// S: 1つのノードが持つ値の型
//    llだけでなく，pairやstructを使って複数の情報を持たせてもよい．
//
// op: 2区間の結果を結合する演算．
//     2つの引数a，bに対して演算を行った結果を返す．
//     【重要】結合則
//       op(op(a, b), c) == op(a, op(b, c))
//     を満たす必要がある．
//
// e: 演算の単位元を返す関数．e()で単位元を得る．
//    任意のxについて，次式を満たす値．
//       op(x, e) == op(e, x) == x
//    空区間に対する演算結果にもeが使われる．
//
// ------------------------------------------------------------
// その他のopとe
//
// 【積】
// constexpr auto op = [](ll a, ll b) { return a * b; };
// constexpr auto e = []() { return 1LL; };
// ※ オーバーフローに注意する．
//
// 【最大公約数】
// constexpr auto op = [](ll a, ll b) { return gcd(a, b); };
// constexpr auto e = []() { return 0LL; };
//
// 【最小公倍数】
// constexpr auto op = [](ll a, ll b) { return lcm(a, b); };
// constexpr auto e = []() { return 1LL; };
//
// 【ビットOR】
// constexpr auto op = [](ll a, ll b) { return a | b; };
// constexpr auto e = []() { return 0LL; };
//
// 【ビットAND】
// constexpr auto op = [](ll a, ll b) { return a & b; };
// constexpr auto e = []() { return ~0LL; };
//
// 【ビットXOR】
// constexpr auto op = [](ll a, ll b) { return a ^ b; };
// constexpr auto e = []() { return 0LL; };
//
// ============================================================
// 複数情報を持つセグメント木
//
// 区間の答えを求めるために複数の情報が必要な場合，
// pairやstructを使って1つのノードに複数の情報を持たせる．
//
// 例：括弧列
//   first ：区間全体の合計
//   second：区間先頭を0とした累積和の最小値
//
//   左区間aと右区間bを結合すると，
//     合計 = a.first + b.first
//     最小値 = min(a.second, a.first + b.second)
//
// ※ 上の例では空prefixを累積和の最小値の候補に含めない．
//    空prefixも含める定義なら，
//      '(' -> {1, 0}
//      ')' -> {-1, -1}
//      e() -> {0, 0}
//    とする方法もある．
//
// ============================================================
// st.max_right(l, f);
//
// 区間[l, r)で，f(st.prod(l, r))がtrueとなる最大のrを探す．O(log N)．
// 条件fには次が必要．
//   ・f(e()) == true
//   ・同じ引数に対して常に同じ結果を返す
//   ・区間を広げるにつれてtrue → falseとなる単調な条件
//
// 例：区間最大値セグ木の場合
// B = {5, 2, 3, 4, 5}
// auto f = [](ll x) {
//     return x < 4;
// };
//
// int r = st.max_right(1, f);      // 区間[1, r)で最大値が4未満となる最大のr
//    B[1:3) = {2, 3}    → 最大値3なのでtrue
//    B[1:4) = {2, 3, 4} → 最大値4なのでfalse
//    よって r = 3
//
// ============================================================
// st.min_left(r, f);
//
// 区間[l, r)で，f(st.prod(l, r))がtrueとなる最小のlを探す．O(log N)．
// 条件fはmax_rightと同様．
//
// 例：区間最大値セグ木の場合
// B = {5, 2, 3, 4, 5}
// auto f = [](ll x) {
//     return x < 4;
// };
//
// int l = st.min_left(3, f);      // 区間[l, 3)で最大値が4未満となる最小のl
//    B[1:3) = {2, 3}    → 最大値3なのでtrue
//    B[0:3) = {5, 2, 3} → 最大値5なのでfalse
//    よって l = 1
//
// ============================================================