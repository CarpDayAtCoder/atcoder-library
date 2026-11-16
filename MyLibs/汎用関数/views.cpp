#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// C++ views まとめ
//
// 使用頻度：★★★★☆
// 主な用途：コンテナをコピーせず，要素の見え方や取り出し方を変える
// キーワード：iota，enumerate，zip，filter，transform，reverse，
//             take，drop，pairwise，slide，chunk，stride
//
// C++20以降で使用可能．
// enumerate，zip，pairwise，slide，chunk，strideなどはC++23．
//
// viewsは基本的に新しいコンテナを作らず，元の範囲を別の形で見る．
// 多くのviewは遅延評価され，必要になった要素だけ処理される．
// 元の要素への参照を持つviewでは，要素を書き換えると元のコンテナも変わる．
//
// ============================================================
// 主な機能
//
// 【連番生成】
//   views::iota(a, b)
//       a以上b未満の連番を生成する．Pythonのrange(a, b)に近い．
//       例：for (int i : views::iota(0, n))
//
// 【添字と要素】
//   views::enumerate(A)
//       {添字，要素}を順に取り出す．Pythonのenumerate(A)に近い．
//       例：for (auto [i, e] : views::enumerate(A))
//       eは元要素への参照になり得るため，eを書き換えるとAも変わる．
//
// 【複数の範囲を同時に走査】
//   views::zip(A, B)
//       A，Bの対応する要素を組にして取り出す．Pythonのzip(A, B)に近い．
//       例：for (auto [a, b] : views::zip(A, B))
//       長さが異なる場合は，短い方の終端で終了する．
//
// 【条件で絞る】
//   A | views::filter(f)
//       条件fを満たす要素だけを見る．
//
// 【要素を変換して見る】
//   A | views::transform(f)
//       各要素にfを適用した結果を見る．元のA自体は変更しない．
//
// 【逆順に見る】
//   A | views::reverse
//       Aを変更せず，逆順に見る．
//       ranges::reverse(A)はA自体を逆順にするので役割が異なる．
//
// 【先頭部分を取る／飛ばす】
//   A | views::take(k)
//       先頭k要素を見る．PythonのA[:k]に近い．
//
//   A | views::drop(k)
//       先頭k要素を飛ばして見る．PythonのA[k:]に近い．
//
// 【隣接する2要素】
//   A | views::pairwise
//       隣り合う2要素を順に取り出す．
//       例：for (auto [a, b] : A | views::pairwise)
//
// ============================================================
// viewの連結
//
// viewは | でつなげられる．
// 例：偶数だけ取り出し，その二乗を見る．
//   auto B = A
//          | views::filter([](int x) { return x % 2 == 0; })
//          | views::transform([](int x) { return x * x; });
//
// Bはvectorではなくview．必要になった要素から順に評価される．
//
// ============================================================
// viewをvectorなどに変換
//
// C++23ではranges::toを使える．
//   auto B = A
//          | views::filter([](int x) { return x % 2 == 0; })
//          | ranges::to<vector>();
//
// Bは実体を持つvectorになる．viewの結果を保存したい場合に使用する．
//
// ============================================================
// 補足：その他のview
//
// 【一定間隔で取り出す】
//   A | views::stride(k)
//       先頭からk個おきに見る．PythonのA[::k]に近い．
//       kは正の値を指定する．
//
// 【連続する長さkの区間】
//   A | views::slide(k)
//       長さkの連続区間を1つずつずらしながら見る．
//       例：{1,2,3,4,5}，k=3
//           → {1,2,3}，{2,3,4}，{3,4,5}
//       kは正の値を指定する．
//
// 【k個ずつ分割】
//   A | views::chunk(k)
//       先頭からk個ずつのまとまりに分けて見る．
//       例：{1,2,3,4,5}，k=2
//           → {1,2}，{3,4}，{5}
//       kは正の値を指定する．
//
// 【pair，tupleの一部分だけを見る】
//   P | views::keys
//       各要素のget<0>だけを見る．
//
//   P | views::values
//       各要素のget<1>だけを見る．
//
// 【直積】
//   views::cartesian_product(A, B)
//       AとBの全組合せを取り出す．
//
// ============================================================
// 注意
//
// ・viewは元のコンテナを参照していることが多い．
//   元のコンテナの寿命が切れた後にviewを使わない．
//
// ・viewを作っただけでは，通常はvectorなどの新しいコンテナは作られない．
//   結果を保存したい場合はranges::to<vector>()などを使用する．
//
// ・添字アクセスや前後の要素へのアクセスが中心なら，
//   通常のfor (int i = 0; i < ssize(A); i++)の方が分かりやすい場合も多い．
//
// ============================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector A{1, 2, 3, 4, 5, 6};

    // 【iota】
    cout << "===== iota =====\n";
    cout << "　0以上5未満: ";
    for (int i : views::iota(0, 5)) {
        cout << i << ' ';
    }
    cout << '\n';

    // 【enumerate】
    cout << "\n===== enumerate =====\n";
    for (auto [i, e] : views::enumerate(A)) {
        cout << "　A[" << i << "] = " << e << '\n';
    }

    // 【zip】
    cout << "\n===== zip =====\n";
    vector B{10, 20, 30, 40, 50, 60};
    for (auto [a, b] : views::zip(A, B)) {
        cout << "　" << a << " + " << b << " = " << a + b << '\n';
    }

    // 【filter】
    cout << "\n===== filter =====\n";
    cout << "　偶数: ";
    for (int x : A | views::filter([](int x) { return x % 2 == 0; })) {
        cout << x << ' ';
    }
    cout << '\n';

    // 【transform】
    cout << "\n===== transform =====\n";
    cout << "　二乗: ";
    for (int x : A | views::transform([](int x) { return x * x; })) {
        cout << x << ' ';
    }
    cout << '\n';

    // 【reverse】
    cout << "\n===== reverse =====\n";
    cout << "　逆順: ";
    for (int x : A | views::reverse) {
        cout << x << ' ';
    }
    cout << '\n';

    // 【take，drop】
    cout << "\n===== take，drop =====\n";
    cout << "　先頭3要素: ";
    for (int x : A | views::take(3)) {
        cout << x << ' ';
    }
    cout << '\n';

    cout << "　先頭3要素を除く: ";
    for (int x : A | views::drop(3)) {
        cout << x << ' ';
    }
    cout << '\n';

    // 【pairwise】
    cout << "\n===== pairwise =====\n";
    cout << "　隣接差分: ";
    for (auto [a, b] : A | views::pairwise) {
        cout << b - a << ' ';
    }
    cout << '\n';

    // 【viewの連結】
    cout << "\n===== filter | transform =====\n";
    auto C = A
           | views::filter([](int x) { return x % 2 == 0; })
           | views::transform([](int x) { return x * x; });

    cout << "　偶数の二乗: ";
    for (int x : C) {
        cout << x << ' ';
    }
    cout << '\n';

    // 【ranges::to】
    auto D = A
           | views::filter([](int x) { return x % 2 == 1; })
           | ranges::to<vector>();

    cout << "　奇数をvectorに変換: ";
    for (int x : D) {
        cout << x << ' ';
    }
    cout << '\n';

    // 【stride】
    cout << "\n===== stride =====\n";
    cout << "　2個おき: ";
    for (int x : A | views::stride(2)) {
        cout << x << ' ';
    }
    cout << '\n';

    // 【slide】
    cout << "\n===== slide （大きさ3）=====\n";
    for (auto window : A | views::slide(3)) {
        cout << "　";
        for (int x : window) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    // 【chunk】
    cout << "\n===== chunk （2要素ずつ）=====\n";
    for (auto group : A | views::chunk(2)) {
        cout << "　";
        for (int x : group) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}