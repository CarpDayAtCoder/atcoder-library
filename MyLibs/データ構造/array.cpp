#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// std::array まとめ
//
// 使用頻度：★★★★☆
// 主な用途：要素数がコンパイル時に決まっている固定長配列
// キーワード：array，固定長，fill，size，CTAD，多次元配列
//
// 【基本】
// array<型, 要素数>
// 要素数はコンパイル時に決まる定数でなければならない．
// 例：array<int, 5> A;
//
// vectorと異なり，作成後に要素数を変更することはできない．
// 一方で，C配列と違ってsize()，fill()などのメソッドを使用できる．
//
// ============================================================
// 【1次元arrayの生成・初期化】
//
// array<int, 5> A1;            // ローカル変数では未初期化
// array<int, 5> A2{};          // 全要素0
// array A3{1, 2, 3, 4, 5};     // 各要素を指定
// array<int, 5> A4;
// A4.fill(-1);                 // 全要素-1
//
// ============================================================
// 【多次元arrayの生成・初期化】
//
// 例：2次元（3行4列）
// array<array<int, 4>, 3> B1;       // ローカル変数では未初期化
// array<array<int, 4>, 3> B2{};     // 全要素0
// array<array<int, 4>, 3> B3;
// for (auto& row : B3) {
//     row.fill(-1);                // 全要素-1
// }
//
// 例：3次元（2 × 3 × 4）
// array<array<array<int, 4>, 3>, 2> C1;    // 未初期化
// array<array<array<int, 4>, 3>, 2> C2{};  // 全要素0
// array<array<array<int, 4>, 3>, 2> C3;
// for (auto& plane : C3) {
//     for (auto& row : plane) {
//         row.fill(-1);                    // 全要素-1
//     }
// }
//
// ============================================================
// 【vector × array】
//
// 行数は実行時に決まり，各行の要素数だけ固定したい場合に便利．
// vector<array<long long, 3>> dp(n);       // n × 3，全要素0
//
// vectorの要素は値初期化されるため，array内部のlong longも0LLで初期化される．
//
// ============================================================
// 【主なメソッド・操作】
//  例：array<int, 5> A{10, 20, 30, 40, 50};
//
//  〇要素アクセス
//   ・A[i]          // i番目の要素．範囲チェックなし
//   ・A.at(i)       // i番目の要素．範囲外なら例外
//   ・A.front()     // 先頭要素
//   ・A.back()      // 最後の要素
//
//  〇要素数
//   ・A.size()      // 要素数
//   ・A.empty()     // 空ならtrue
//
//  〇【全要素を同じ値にする】
//   ・A.fill(x);
//
//  〇イテレータ
//   ・A.begin()
//   ・A.end()
//   ・A.rbegin()
//   ・A.rend()
//
// ============================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "##### 1次元array #####\n";

    array<int, 5> A{};      // 0で初期化
    cout << "A: ";
    for (int x : A) cout << x << ' ';
    cout << '\n';

    A.fill(-1);             // -1で埋める
    cout << "fill(-1): ";
    for (int x : A) cout << x << ' ';
    cout << '\n';

    cout << "size(): " << A.size() << '\n'; // 要素数


    cout << "\n===== 要素アクセス =====\n";
    array B{10, 20, 30, 40, 50};    // 型と要素数の自動推論（CTAD）でarray<int, 5
    cout << "B: ";
    for (int x : B) cout << x << ' ';
    cout << '\n';

    cout << "先頭: " << B.front() << '\n';
    cout << "最後: " << B.back() << '\n';


    cout << "\n===== ranges =====\n";
    ranges::reverse(B);             // 逆順
    cout << "reverse: ";
    for (int x : B) cout << x << ' ';
    cout << '\n';

    ranges::sort(B);                // ソート
    cout << "sort: ";
    for (int x : B) cout << x << ' ';
    cout << '\n';


    cout << "\n##### 2次元array #####\n";
    array<array<int, 4>, 3> C{};
    for (auto& row : C) row.fill(-1);   // -1で埋める
    for (auto& row : C) {
        for (int x : row) cout << setw(3) << x;
        cout << '\n';
    }


    cout << "\n##### vector × array #####\n";
    int n = 3;
    vector<array<int, 2>> D(n);
    D[0] = {10, 20};
    D[1] = {30, 40};
    D[2] = {50, 60};
    for (auto [x, y] : D) {
        cout << x << ' ' << y << '\n';
    }

    return 0;
}

// ============================================================
// 補足
// ============================================================
// 型と要素数の自動推論（CTAD）
//
// array A3{1, 2, 3, 4, 5}; 
// はCTADによって，型と要素数が推論され，
// array<int, 5> となる．
//
// constexpr array DIR4 = {
//     pair{0, 1}, pair{-1, 0}, pair{0, -1}, pair{1, 0}
// };
// のような固定データにも便利．
//
// ============================================================
// rangesとの組合せ
//
// arrayもvectorと同じようにrangesを使用できる．
//
// ranges::sort(A);                 // 昇順
// ranges::sort(A, greater<>());    // 降順
// ranges::reverse(A);              // 逆順
// ranges::max(A);                  // 最大値
// ranges::min(A);                  // 最小値
// ranges::find(A, x);              // xを探索
// ranges::count(A, x);             // xの個数
//
// ============================================================
// 【配列全体のコピー・代入】
//  arrayはC配列と異なり，配列全体をそのままコピー・代入できる．
//
//  array<int, 3> A{1, 2, 3};
//  array<int, 3> B = A;     // コピー
//
// ============================================================
// C配列，vectorとの使い分け
//
// 【std::array】
//   array<int, 5> A;
//   ・要素数はコンパイル時に固定
//   ・size()，fill()などを使用できる
//   ・配列全体のコピー，代入が可能
//   ・rangesとの相性がよい
//
// 【C配列】
//   int A[5];
//   ・要素数は固定
//   ・記述が短い
//   ・size()，fill()などのメンバ関数はない
//   ・関数へ渡すときにポインタへ変換される場合がある
//
// 【vector】
//   vector<int> A(n);
//   ・要素数を実行時に決められる
//   ・resize()，push_back()などで要素数を変更できる
//
// 使い分けの目安：
//   要素数が実行時に決まる
//       → vector
//   固定長で，単純な配列として使いたい
//       → C配列でもよい
//   固定長で，fill()，size()，コピーなどを使いたい
//       → array
//
// ============================================================
