#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
// ============================================================
// std::set / std::multiset まとめ
//
// 使用頻度：★★★★☆
// 主な用途：要素を常にソートして保持，存在判定，重複要素の管理，
//           最大値・最小値，lower_bound，upper_bound
// キーワード：set，multiset，insert，erase，find，contains，count，
//             begin，rbegin，lower_bound，upper_bound
//
// 【基本】
// set<int> S;         // 昇順，重複不可
// multiset<int> MS;   // 昇順，重複可
// 要素は自動的に昇順に並ぶ（Pythonとは異なる）
//
// insert，find，contains，lower_bound，upper_bound：O(log N)
// erase：基本O(log N)
// 最小値 *begin()，最大値 *rbegin()：O(1)
//
// ============================================================
// 【生成・初期化】
//
// set<int> S1;                   // 空のset
// set S2{5, 2, 8, 2, 4};        // {2, 4, 5, 8}．int型を推論
//
// multiset<int> MS1;             // 空のmultiset
// multiset MS2{5, 2, 8, 2, 4};  // {2, 2, 4, 5, 8}
//
// vector A{5, 2, 8, 2, 4};
// set S3(A.begin(), A.end());        // vectorからsetを作成
// multiset MS3(A.begin(), A.end());  // vectorからmultisetを作成
//
// ============================================================
// 【主なメソッド・操作】
// set<int> S;      // multisetもメソッド名は同じ
//
// 〇追加
//   ・S.insert(x);                     // 1つの要素 xを追加
//   ・S.emplace(...);                  // 引数から要素を直接作成
//
// 〇削除
//   ・S.erase(x);           // 値xを削除．multisetの場合は，すべての xを削除
//   ・S.erase(it);          // iteratorが指す要素を削除．multisetでも削除されるのは1つ
//
// 〇検索
//   ・S.contains(x);        // xが存在すればtrue．C++20～
//   ・S.find(x);            // xのiterator．なければS.end()
//   ・S.count(x);           // xの個数．setでは0または1
//
// 〇要素数
//   ・S.size();
//   ・S.empty();
//
// 〇全要素を削除
//   ・S.clear();
//
// 〇最小値・最大値
//   ・*S.begin();           // 最小値．S.empty() = trueだと未定義動作
//   ・*S.rbegin();          // 最大値．S.empty() = trueだと未定義動作
//
// ============================================================
// 【lower_bound / upper_bound】
//
// set，multisetではメンバ関数を使用する．O(log N)
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
// ============================================================
// 【multisetの削除】
//
// multiset<int> MS;
// MS.erase(x);   // xをすべて削除する
//
// xを1個だけ削除する場合：
// auto it = MS.find(x);
// if (it != MS.end()) {
//     MS.erase(it);    // イテレータ指定なら削除は1つ
// }
//
// ============================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << boolalpha;

    cout << "##### set #####\n";
    set S{5, 2, 8, 2, 4};
    cout << "S: ";
    for (int x : S) cout << x << ' ';
    cout << '\n';

    S.insert(3);
    cout << "3を追加: ";
    for (int x : S) cout << x << ' ';
    cout << '\n';

    cout << "5が存在する？: " << S.contains(5) << '\n';
    cout << "最小値: " << *S.begin() << '\n';
    cout << "最大値: " << *S.rbegin() << '\n';

    auto lb = S.lower_bound(5);
    auto ub = S.upper_bound(5);
    cout << "5以上の最小値: " << *lb << '\n';
    cout << "5より大きい最小値: " << *ub << '\n';

    S.erase(2);
    cout << "2を削除: ";
    for (int x : S) cout << x << ' ';
    cout << '\n';


    cout << "\n##### multiset #####\n";
    multiset MS{5, 2, 2, 2, 8, 4};
    cout << "MS: ";
    for (int x : MS) cout << x << ' ';
    cout << '\n';

    cout << "2の個数: " << MS.count(2) << '\n';
    auto it = MS.find(2);
    if (it != MS.end()) MS.erase(it);

    cout << "2を1個削除: ";
    for (int x : MS) cout << x << ' ';
    cout << '\n';

    MS.erase(2);
    cout << "残りの2をすべて削除: ";
    for (int x : MS) cout << x << ' ';
    cout << '\n';

    return 0;
}


// ============================================================
// 補足
// ============================================================
// find()とcontains()．どちらもO(log N)
//
// 存在するかだけ調べる：
//   if (S.contains(x)) ...
//
// iteratorが必要：
//   auto it = S.find(x);
//   if (it != S.end()) ...
//
// ============================================================
// iterator
//
// set，multisetは添字アクセス・ランダムアクセスできない．
//
// コンパイルエラー：
//   S[i]           : 添字アクセス禁止
//   it + 1         : 指定数だけ動かすランダムアクセス禁止
//   it - S.begin() : 同上
//
// 1つ進む／戻ることはできる：
//   ++it;      : 1つ進む
//   --it;      : 1つ戻る
//
// 複数個進める場合：
//   next(it, k);   : k回進む．O(k)
//   prev(it, k);   : k回戻る．O(k)
//
// vectorのiteratorのようなランダムアクセスはできないため，setだけでは
// 「x未満の要素が何個あるか」
// 「k番目に小さい要素は何か」
// をO(log N)では求められない．
//
// ============================================================
// setの要素は変更できない
//
// 値を変更すると並び順が崩れる可能性があるため，
// set，multisetに格納された要素そのものは直接変更することはできない．
//
// auto it = S.find(x);
// *it = y;     <-- NG
//
// 必要なら，
//   S.erase(it);
//   S.insert(y);
// とする．
//
// ============================================================
// 降順のset
//
// 大きい値から順に保持する．
// set<int, greater<>> S;
// multiset<int, greater<>> MS;
//
// ただし通常は昇順のsetを使い，
// 最大値が必要なら*rbegin()とする方が単純なことが多い．
//
// ============================================================
// ranges::lower_boundではなくメンバ関数を使う
//
// set，multisetでは，
//   S.lower_bound(x);
//   S.upper_bound(x);
// を使用する．どちらもO(log N)．
//
// ranges::lower_bound(S, x)も使えるが，O(N)なので使う理由がない．
//
// ============================================================
// 集合演算
//
// 【A自身を演算結果に更新する】
//
// 和集合 A ← A∪B：
// A.insert(B.begin(), B.end());
//
// 積集合 A ← A∩B：
// for (auto it=A.begin(); it!=A.end(); ) {
//     if (!B.contains(*it)) it = A.erase(it);
//     else ++it;
// }
//
// 差集合 A ← A-B：
// for (int x : B) A.erase(x);
//
// 対称差 A ← A△B：
// for (int x : B) {
//     if (A.contains(x)) A.erase(x);
//     else A.insert(x);
// }
//
// 【ranges::set_* で，新しい集合Cを作る場合】
//
// set<int> C;  // 新規作成用
//
// 和集合 C ← A∪B：
// ranges::set_union(A, B, inserter(C, C.end()));
// 積集合 C ← A∩B：
// ranges::set_intersection(A, B, inserter(C, C.end()));
// 差集合 C ← A-B：
// ranges::set_difference(A, B, inserter(C, C.end()));
// 対称差 C ← A△B：
// ranges::set_symmetric_difference(A, B, inserter(C, C.end()));
//
// ranges::set_* は2つのソート済み集合を先頭から処理するため，
// 比較回数はO(|A| + |B|)．
// ============================================================
// 走査しながらerase
//
// for (auto it=S.begin(); it!=S.end(); ) {
//     if (条件) it = S.erase(it);
//     else ++it;
// }
// erase(it)は削除した要素の次を指すイテレータを返す．
// ============================================================
