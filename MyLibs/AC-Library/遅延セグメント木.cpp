#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
using ll = long long;

// ============================================================
// AC-Library LazySegTree（遅延セグメント木）まとめ
//
// 使用頻度：★★★☆☆
// 主な用途：区間更新＋区間の最大値・最小値・合計などの取得
// キーワード：apply，set，get，prod，all_prod
//
// ------------------------------------------------------------
// 基本操作
//
// lazy_segtree<S, op, e, F, mapping, composition, id> st(A);
//
// st.apply(l, r, f);  // A[l:r)すべてに更新fを適用．O(log N)
// st.apply(p, f);     // A[p]に更新fを適用．O(log N)
// st.set(p, x);       // A[p]をxへ変更．O(log N)
// st.get(p);          // A[p]を取得．O(log N)
// st.prod(l, r);      // A[l:r)の演算結果．O(log N)
// st.all_prod();      // A全体の演算結果．O(1)
//
// ------------------------------------------------------------
// S           ：各ノードが持つ区間情報の型（セグ木と同じ）
// op(a, b)    ：2区間の区間情報を結合する演算（セグ木と同じ）
// e()         ：opの単位元（セグ木と同じ）
// F           ：各ノードが持つ更新情報の型
// mapping(f,x)：区間情報xに更新情報fを適用した後の区間情報を作成
// composition(g,f)：fの後にgを適用した更新操作 g(f(x))
// id()        ：恒等写像．何もしない更新操作
//
// ------------------------------------------------------------
// 【基本パターン】
// 1．区間代入 ＋ 区間最大値（最小値）
// 2．区間加算 ＋ 区間最大値（最小値）
// 3．区間加算 ＋ 区間合計
// 4．区間代入 ＋ 区間合計
// 【応用パターン】
// 5．区間アフィン変換 ＋ 区間合計（mod）
// 6．区間ビット反転 ＋ 区間転倒数
//
// ============================================================

// ============================================================
// 【パターン1】区間代入 ＋ 区間最大値（最小値）
//    apply(l, r, x)：A[l:r)をすべてxにする
//    prod(l, r)    ：A[l:r)の最大値
//    最小値にする場合はopとeの2行を変更する．
//    https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_F
//    https://atcoder.jp/contests/typical90/tasks/typical90_ac
// ============================================================
#if 1

#include <atcoder/lazysegtree>
using namespace atcoder;

constexpr ll LINF = 1LL << 60;
constexpr ll ID = LINF; // 「更新なし」．実際の代入値として使わない値

using S = ll; // ノード：区間最大値
using F = ll; // lazy：代入する値

constexpr auto op = [](S a, S b)
{ return max(a, b); };
constexpr auto e = []()
{ return -LINF; };

// 最小値の場合
// constexpr auto op = [](S a, S b) { return min(a, b); };
// constexpr auto e = []() { return LINF; };

// f==IDなら何もしない．それ以外なら値をfで上書き
constexpr auto mapping = [](F f, S x)
{
    return f == ID ? x : f;
};

// 新しい代入gがあれば，古い代入fを上書き
constexpr auto composition = [](F g, F f)
{
    return g == ID ? f : g;
};

constexpr auto id = []()
{ return ID; };

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<ll> A{5, 2, 8, 4, 6};
    lazy_segtree<S, op, e, F, mapping, composition, id> st(A);

    cout << "A = {5, 2, 8, 4, 6}\n";

    cout << "\n===== 区間代入 =====\n";
    st.apply(1, 4, 3); // A[1:4)を3に
    cout << "A[1:4)を3に代入\n";

    cout << "\n===== prod()による区間最大値 =====\n";
    cout << "A[0:4)の最大値: " << st.prod(0, 4) << '\n';

    cout << "\n===== get()による一点取得 =====\n";
    cout << "A[2]の値: " << st.get(2) << '\n';

    cout << "\n===== all_prod() =====\n";
    cout << "A全体の最大値: " << st.all_prod() << '\n';

    return 0;
}

#endif

// ============================================================
// 【パターン2】区間加算 ＋ 区間最大値（最小値）
//    apply(l, r, x)：A[l:r)すべてにxを加算
//    prod(l, r)    ：A[l:r)の最大値
//    最小値にする場合はopとeの2行を変更する．
//    https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H
// ============================================================
#if 0

#include <atcoder/lazysegtree>
using namespace atcoder;

constexpr ll LINF = 1LL << 60;

using S = ll;               // ノード：区間最大値
using F = ll;               // lazy：加算する値

constexpr auto op = [](S a, S b) { return max(a, b); };
constexpr auto e = []() { return -LINF; };

// 最小値の場合
// constexpr auto op = [](S a, S b) { return min(a, b); };
// constexpr auto e = []() { return LINF; };

// 区間内の全要素にfを加えるので，最大値もf増える
constexpr auto mapping = [](F f, S x) {
    return x + f;
};

// 加算更新は足し合わせる
constexpr auto composition = [](F g, F f) {
    return g + f;
};

constexpr auto id = []() { return 0LL; };

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<ll> A{5, 2, 8, 4, 6};
    lazy_segtree<S, op, e, F, mapping, composition, id> st(A);

    cout << "A = {5, 2, 8, 4, 6}\n";

    cout << "\n===== 区間加算 =====\n";
    st.apply(1, 4, 3);          // A[1:4)に3加算
    cout << "A[1:4)に3加算\n";

    cout << "\n===== prod()による区間最大値 =====\n";
    cout << "A[0:4)の最大値: " << st.prod(0, 4) << '\n';

    cout << "\n===== get()による一点取得 =====\n";
    cout << "A[2]の値: " << st.get(2) << '\n';

    cout << "\n===== all_prod() =====\n";
    cout << "A全体の最大値: " << st.all_prod() << '\n';

    return 0;
}

#endif

// ============================================================
// 【パターン3】区間加算 ＋ 区間合計
//    apply(l, r, x)：A[l:r)すべてにxを加算
//    prod(l, r).sum：A[l:r)の合計
//
//    Sには「合計」だけでなく「要素数」も持たせる．
//    区間全体にfを加えると，区間合計は f×要素数 増えるため．
//    https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G
// ============================================================
#if 0

#include <atcoder/lazysegtree>
using namespace atcoder;

struct S {
    ll sum;
    int size;
};

using F = ll;       // lazy：各要素に加算する値

constexpr auto op = [](S a, S b) {
    return S{a.sum + b.sum, a.size + b.size};
};

constexpr auto e = []() {
    return S{0, 0};
};

// 各要素にf加算 → 区間合計はf×要素数増える
constexpr auto mapping = [](F f, S x) {
    return S{x.sum + f * x.size, x.size};
};

constexpr auto composition = [](F g, F f) {
    return g + f;
};

constexpr auto id = []() {
    return 0LL;
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<ll> A{5, 2, 8, 4, 6};

    vector<S> init;
    for (ll x : A) init.push_back({x, 1});

    lazy_segtree<S, op, e, F, mapping, composition, id> st(init);

    cout << "A = {5, 2, 8, 4, 6}\n";

    cout << "\n===== 区間加算 =====\n";
    st.apply(1, 4, 3);          // A[1:4)に3加算
    cout << "A[1:4)に3加算\n";

    cout << "\n===== prod()による区間合計 =====\n";
    cout << "A[1:4)の合計: " << st.prod(1, 4).sum << '\n';

    cout << "\n===== get()による一点取得 =====\n";
    cout << "A[2]の値: " << st.get(2).sum << '\n';

    cout << "\n===== all_prod() =====\n";
    cout << "A全体の合計: " << st.all_prod().sum << '\n';

    return 0;
}

#endif

// ============================================================
// 【パターン4】区間代入 ＋ 区間合計
//    apply(l, r, x)：A[l:r)をすべてxにする
//    prod(l, r).sum：A[l:r)の合計
//
//    Sには「合計」と「要素数」を持たせる．
//    区間全体をfにすると，区間合計は f×要素数 になる．
//    https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_I
// ============================================================
#if 0

#include <atcoder/lazysegtree>
using namespace atcoder;

constexpr ll LINF = 1LL << 60;
constexpr ll ID = LINF;     // 「更新なし」．実際の代入値として使わない値

struct S {
    ll sum;
    int size;
};

using F = ll;       // lazy：代入する値

constexpr auto op = [](S a, S b) {
    return S{a.sum + b.sum, a.size + b.size};
};

constexpr auto e = []() {
    return S{0, 0};
};

constexpr auto mapping = [](F f, S x) {
    if (f == ID) return x;
    return S{f * x.size, x.size};
};

// 新しい代入gがあれば，古い代入fを上書き
constexpr auto composition = [](F g, F f) {
    return g == ID ? f : g;
};

constexpr auto id = []() {
    return ID;
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<ll> A{5, 2, 8, 4, 6};

    vector<S> init;
    for (ll x : A) init.push_back({x, 1});

    lazy_segtree<S, op, e, F, mapping, composition, id> st(init);

    cout << "A = {5, 2, 8, 4, 6}\n";

    cout << "\n===== 区間代入 =====\n";
    st.apply(1, 4, 3);          // A[1:4)を3に
    cout << "A[1:4)を3に代入\n";

    cout << "\n===== prod()による区間合計 =====\n";
    cout << "A[1:4)の合計: " << st.prod(1, 4).sum << '\n';

    cout << "\n===== get()による一点取得 =====\n";
    cout << "A[2]の値: " << st.get(2).sum << '\n';

    cout << "\n===== all_prod() =====\n";
    cout << "A全体の合計: " << st.all_prod().sum << '\n';

    return 0;
}

#endif

// ============================================================
// 【パターン5】区間アフィン変換 ＋ 区間合計（mod）
//    更新：x → b*x + c
//    apply(l, r, F{b,c})
//    prod(l, r).sum：A[l:r)の合計
//    https://atcoder.jp/contests/practice2/tasks/practice2_k
// ============================================================
#if 0

#include <atcoder/lazysegtree>
#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;

struct S {
    mint sum;
    int size;
};

struct F {
    mint b;
    mint c;
};

constexpr auto op = [](S a, S b) {
    return S{a.sum + b.sum, a.size + b.size};
};

constexpr auto e = []() {
    return S{0, 0};
};

// 区間内の各xを b*x+c にする
constexpr auto mapping = [](F f, S x) {
    return S{f.b * x.sum + f.c * x.size, x.size};
};

// fの後にgを適用
// g(f(x)) = g.b * (f.b*x + f.c) + g.c
constexpr auto composition = [](F g, F f) {
    return F{
        g.b * f.b,
        g.b * f.c + g.c
    };
};

constexpr auto id = []() {
    return F{1, 0};
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<ll> A{5, 2, 8, 4, 6};

    vector<S> init;
    for (ll x : A) init.push_back({x, 1});

    lazy_segtree<S, op, e, F, mapping, composition, id> st(init);

    cout << "A = {5, 2, 8, 4, 6}\n";

    cout << "\n===== 区間アフィン変換 =====\n";
    st.apply(1, 4, F{2, 1});      // x → 2x+1
    cout << "A[1:4)を x -> 2x+1 で更新\n";

    cout << "\n===== prod()による区間合計 =====\n";
    cout << "A[1:4)の合計: " << st.prod(1, 4).sum.val() << '\n';

    cout << "\n===== all_prod() =====\n";
    cout << "A全体の合計: " << st.all_prod().sum.val() << '\n';

    return 0;
}

#endif

// ============================================================
// 【パターン6】区間ビット反転 ＋ 区間転倒数
//    更新：0 <-> 1
//    apply(l, r, true)
//    prod(l, r).inv：A[l:r)の転倒数
//    転倒数：i<j かつ A[i]=1，A[j]=0 となる組の個数
//    https://atcoder.jp/contests/practice2/tasks/practice2_l
// ============================================================
#if 0

#include <atcoder/lazysegtree>
using namespace atcoder;

struct S {
    ll zero;      // 0の個数
    ll one;       // 1の個数
    ll inv;       // 転倒数
};

using F = bool;   // true：反転，false：何もしない

constexpr auto op = [](S a, S b) {
    return S{
        a.zero + b.zero,
        a.one + b.one,
        a.inv + b.inv + a.one * b.zero
    };
};

constexpr auto e = []() {
    return S{0, 0, 0};
};

constexpr auto mapping = [](F f, S x) {
    if (!f) return x;

    // 反転すると0と1の個数が入れ替わる．
    // 全0-1ペア数 zero*one のうち，
    // 元の転倒数でなかったものが新しい転倒数になる．
    return S{
        x.one,
        x.zero,
        x.zero * x.one - x.inv
    };
};

// 2回反転すると元に戻る
constexpr auto composition = [](F g, F f) {
    return g ^ f;
};

constexpr auto id = []() {
    return false;
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<int> A{0, 1, 1, 0, 1};

    vector<S> init;
    for (int x : A) {
        if (x == 0) init.push_back({1, 0, 0});
        else        init.push_back({0, 1, 0});
    }

    lazy_segtree<S, op, e, F, mapping, composition, id> st(init);

    cout << "A = {0, 1, 1, 0, 1}\n";
    cout << "A全体の転倒数: " << st.all_prod().inv << '\n';

    cout << "\n===== 区間ビット反転 =====\n";
    st.apply(1, 4, true);          // A[1:4)を反転
    cout << "A[1:4)を反転\n";

    cout << "A全体の転倒数: " << st.all_prod().inv << '\n';

    return 0;
}

#endif

// ============================================================
// 補足
// ============================================================
// セグメント木と遅延セグメント木
//
// ・一点更新だけでよい → segtree
// ・区間をまとめて更新したい → lazy_segtree
//
// ============================================================
// lazy_segtree<S, op, e, F, mapping, composition, id> st(A);
// で設定する情報
//
// 【準備】各ノードは2種類の情報を持つ．
//   ・ x
//     そのノードが表す区間情報．
//     最大値なら区間最大値，合計なら区間合計など．
//   ・ f
//     子ノードへまだ伝搬していない更新情報．葉ノードはfを持たない．
//
// S：区間情報xの型．（セグ木と同じ）
//    最大値／最小値ならllだけでよい．
//    合計の場合は，区間の要素数も必要．
//
// op(a, b)
//    左右2区間a, bのデータを結合する演算．（セグ木と同じ）
//
// e()：opの単位元を返す関数．（セグ木と同じ）
//
// F：更新情報fの型．
//
// mapping(f, x)
//   更新情報fを区間情報xに反映する写像を定義する．
//   更新クエリを受けたときや，親ノードから更新情報を受けたときに使う
//
// composition(g, f)
//   更新gが来たとき，保存していた更新情報fとの合成を定義する．
//
// id()
//  mappingやcompositionで使うfに対応する恒等写像．
//  「伝搬すべき更新情報は何もない」を表すF型の値を返す．
//
//   子ノードへ降りる必要が生じたら，親のfを子へ伝搬する．
//   その際，子では
//      x = mapping(親のf, x)
//      f = composition(親のf, f)
//   とし，親のfはid()に戻す．
//
// ============================================================
// mapping(f, x)
//
// ノードの区間情報xに更新情報fを適用した区間情報を返す．
// 例：区間加算＋区間最大値
//   mapping(f, x) = x + f
// 例：区間加算＋区間合計
//   mapping(f, x) = x.sum + f * x.size
//
// ============================================================
// composition(g, f)
//
// 【重要】先にf，その後gを適用した操作を返す．
//    composition(g, f)(x) = g(f(x))
//
// 加算なら順番を意識しなくても結果は同じだが，
// 代入やアフィン変換では順番が重要．
//
// 例：代入
//   古い更新「3を代入」の後に「5を代入」
//   → 最終的には「5を代入」
//
// 例：アフィン変換
//   f(x) = b1*x + c1
//   g(x) = b2*x + c2
//   g(f(x))
//     = b2*b1*x + (b2*c1+c2)
//
// ============================================================
// id
//
// id()：恒等写像．何もしない更新操作．
//
// 加算       → 0
// アフィン変換 → (1, 0)
// ビット反転 → false
//
// 代入には自然な「何もしない値」がないため，
// 実際には代入されない値をIDとして用意して，
// mappingやcompositionで，IDの場合だけ特別対応する．
// 上の例ではLINFを使用している．
//
// ============================================================
// 区間合計では要素数が必要
//
// 例えば区間[l,r)の全要素にfを加えると，
//   区間合計 += f * (r-l)
// となる．
//
// 遅延セグ木ではmappingが担当区間[l,r)を直接知らないので，
// Sにsizeを持たせておく．
//   struct S {
//       ll sum;
//       int size;
//   };
//
// ============================================================
// setとapply
//
// st.set(p, x);
//   A[p]そのものをS型のxに変更する．
// st.apply(p, f);
//   A[p]にF型の更新fを適用する．
// st.apply(l, r, f);
//   A[l:r)すべてに更新fを適用する．
//
// ============================================================
// max_right / min_left
//
// lazy_segtreeでもsegtreeと同様に使用できる．
//
// st.max_right(l, f);
// st.min_left(r, f);
//
// 条件fには次が必要．
//   ・f(e()) == true
//   ・同じ引数に対して常に同じ結果を返す
//   ・境界探索ではtrue → falseとなる単調な条件
//
// ============================================================