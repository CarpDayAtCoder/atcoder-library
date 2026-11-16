#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// lower_bound / upper_bound まとめ
//
// 使用頻度：★★★★★
// 主な用途：ソート済みvectorから境界位置，最大・最小，個数を求める
// キーワード：lower_bound，upper_bound，二分探索，境界，個数
//
// ※ Aは検索対象について昇順に並んでいる必要がある．
// ※ vectorに対するlower_bound，upper_bound：O(log N)
//
//        [      x未満      ][   xと等しい   ][     xより大きい     ]
//                          ↑               ↑
//                      lower_bound     upper_bound
//
// lower_bound(A, x) → x以上となる最初の位置
// upper_bound(A, x) → xより大きくなる最初の位置
//
// ============================================================
// 【最大値・最小値を探す】
//
// 〇x以上の最小値
// auto it = ranges::lower_bound(A, x);
// if (it != A.end()) {
//     cout << *it;
// }
//
// 〇xより大きい最小値
// auto it = ranges::upper_bound(A, x);
// if (it != A.end()) {
//     cout << *it;
// }
//
// 〇xより小さい最大値
// auto it = ranges::lower_bound(A, x);
// if (it != A.begin()) {
//     cout << *(--it);
// }
//
// 〇x以下の最大値
// auto it = ranges::upper_bound(A, x);
// if (it != A.begin()) {
//     cout << *(--it);
// }
//
// そのまま*itを使う場合はend()を確認する．
// 1つ戻る場合はbegin()を確認してから--itする．
//
// ============================================================
// 【個数を求める】
//
// auto lb = ranges::lower_bound(A, x);
// auto ub = ranges::upper_bound(A, x);
//
// 〇xより小さい個数
// lb - A.begin();
//
// 〇x以下の個数
// ub - A.begin();
//
// 〇xと等しい個数
// ub - lb;
//
// 〇x以上の個数
// A.end() - lb;
//
// 〇xより大きい個数
// A.end() - ub;
//
// ============================================================
// 【位置・添字を求める】
//
// auto it = ranges::lower_bound(A, x);
// int idx = it - A.begin();
//
// it == A.end()の場合，idx == A.size()となる．
// upper_boundでも同様．
//
// ============================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector A{1, 3, 3, 3, 5, 8};
    int x = 3;

    cout << "A: ";
    for (int a : A) cout << a << ' ';
    cout << '\n';
    cout << "x = " << x << '\n';


    auto lb = ranges::lower_bound(A, x);
    auto ub = ranges::upper_bound(A, x);

    cout << "\n===== lower_bound / upper_bound =====\n";
    cout << "lower_boundの位置: " << lb - A.begin() << '\n';
    cout << "upper_boundの位置: " << ub - A.begin() << '\n';

    cout << "\n===== 最大値・最小値 =====\n";
    auto it1 = ranges::lower_bound(A, x);
    if (it1 != A.end())
        cout << "x以上の最小値: " << *it1 << '\n';
    auto it2 = ranges::upper_bound(A, x);
    if (it2 != A.end())
        cout << "xより大きい最小値: " << *it2 << '\n';
    auto it3 = ranges::lower_bound(A, x);
    if (it3 != A.begin())
        cout << "xより小さい最大値: " << *(--it3) << '\n';
    auto it4 = ranges::upper_bound(A, x);
    if (it4 != A.begin())
        cout << "x以下の最大値: " << *(--it4) << '\n';

    cout << "\n===== 個数 =====\n";
    cout << "xより小さい: " << lb - A.begin() << '\n';
    cout << "x以下: " << ub - A.begin() << '\n';
    cout << "xと等しい: " << ub - lb << '\n';
    cout << "x以上: " << A.end() - lb << '\n';
    cout << "xより大きい: " << A.end() - ub << '\n';

    return 0;
}


// ============================================================
// 補足
// ============================================================
// lower_bound / upper_boundの境界の見方
//
//        [      x未満      ][   xと等しい   ][     xより大きい     ]
//                           ↑               ↑
//                       lower_bound     upper_bound
// したがって，
// begin ～ lower_bound         → x未満
// begin ～ upper_bound         → x以下
// lower_bound ～ upper_bound   → xと等しい
// lower_bound ～ end           → x以上
// upper_bound ～ end           → xより大きい
//
// 範囲はすべて半開区間 [first, last) と考える．
//
// ============================================================
// lower_boundとupper_boundの返り値
//
// vectorに対するranges::lower_bound，ranges::upper_boundはイテレータを返す．
//
// auto it = ranges::lower_bound(A, x);
// 値：
//   *it   【注意】it == A.end()の場合は*itを使用しない
// 添字：
//   it - A.begin()
//
// ============================================================
// begin()とend()
//
// n個の要素を持つvectorでは，境界位置を
//   0, 1, 2, ..., n
// と考えることができる．
//
// A.begin()      → 位置0
// A.begin() + i  → 位置i
// A.end()        → 位置n
//
// これによって，
//   it - A.begin()
// で境界位置を整数として取得できる．
//
// ============================================================
// set / multiset
//
// set，multiset Sでは，ranges::lower_bound(S, x)ではなく，
// メンバ関数 S.lower_bound(x) を使用する．
//
// set<int> S;
// auto lb = S.lower_bound(x);   // x以上の最小値
// auto ub = S.upper_bound(x);   // xより大きい最小値
//
// 〇xより小さい最大値
// auto it = S.lower_bound(x);
// if (it != S.begin()) {
//     cout << *(--it);
// }
//
// 〇x以下の最大値
// auto it = S.upper_bound(x);
// if (it != S.begin()) {
//     cout << *(--it);
// }
//
// lower_bound，upper_bound：O(log N)
//
// 【注意】setでは
//      it - S.begin()
//    のようなiterator同士の引き算はできない．
//
// ============================================================
// map
//
// mapでもkeyについてメンバ関数を使用する．
//
// map<int, int> M;
// auto lb = M.lower_bound(x);   // keyがx以上の最初
// auto ub = M.upper_bound(x);   // keyがxより大きい最初
//
// if (lb != M.end()) {
//     cout << lb->first << ' ' << lb->second;
// }
//
// lower_bound，upper_bound：O(log N)
//
// setと同様に，iterator同士の引き算はできない．
//
// ============================================================
// projection
//
// pairなどの一部分を基準に二分探索する場合はprojectionを使える．
//
// secondについて昇順に並んでいる場合：
// vector<pair<int, int>> P;
// auto it = ranges::lower_bound(
//     P, x, {}, &pair<int, int>::second
// );
//
// auto it = ranges::upper_bound(
//     P, x, {}, &pair<int, int>::second
// );
//
// projection後の値について昇順に並んでいる必要がある．
//
// ============================================================
// equal_range
//
// lower_boundとupper_boundを同時に取得することもできる．
//
// auto [lb, ub] = ranges::equal_range(A, x);
//
// xと等しい個数：
// ub - lb;
//
// lower_boundとupper_boundを両方必要とする場合に使える．
//
// ============================================================