#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
// ============================================================
// std::map まとめ
//
// 使用頻度：★★★★★
// 主な用途：keyとvalueの対応付け，頻度集計，key順での管理・探索
// キーワード：map，key，value，[]，insert，erase，find，contains，
//             count，lower_bound，upper_bound
//
// 【基本】
// map<int, int> M;      // {key, value}をkeyの昇順で保持
//
// 検索，追加，削除，lower_bound，upper_bound：O(log N)
//
// ============================================================
// 【生成・初期化】
//
// map<int, int> M1;     // 空のmap
//
// map M2{
//     pair{1, 10}, pair{3, 30}, pair{2, 20}
// };                    // {{1,10}, {2,20}, {3,30}}．型を推論
//
// vector<pair<int, int>> A{{1, 10}, {2, 20}, {3, 30}};
// map M3(A.begin(), A.end());
//
// ============================================================
// 【主なメソッド・操作】
// map<int, int> M;
//
// 〇追加・valueの変更
//   ・M[key] = value;       // keyがなければ追加，あればvalueを変更
//   ・M[key]++;             // 頻度集計などで頻出
//   ・M.insert({key, value});
//
// ※ M[key]はkeyが存在しない場合，
//    valueをデフォルト値で作成してkeyを追加する．
//
// 〇取得
//   ・M[key];               // keyに対応するvalue
//
// 〇検索
//   ・M.contains(key);      // keyが存在すればtrue．C++20～
//   ・M.find(key);          // keyのiterator．なければM.end()
//   ・M.count(key);         // 0または1
//
// 〇削除
//   ・M.erase(key);         // keyの要素を削除
//   ・M.erase(it);          // iteratorが指す要素を削除
//
// 〇要素数
//   ・M.size();
//   ・M.empty();
//
// 〇全要素を削除
//   ・M.clear();
//
// ============================================================
// 【range-for】
//
// key，valueを構造化束縛で取得できる．
//
// 読み取りだけ：
// for (const auto& [key, value] : M) {
//     ...
// }
//
// valueを変更：
// for (auto& [key, value] : M) {
//     value++;
// }
//
// ※ keyは並び順を決めるため変更できない．
//
// ============================================================
// 【lower_bound / upper_bound】
//
// keyについて検索する．メンバ関数を使用する．O(log N)
//
// auto lb = M.lower_bound(x);   // keyがx以上の最初
// auto ub = M.upper_bound(x);   // keyがxより大きい最初
//
// 〇xより小さい最大のkey
// auto it = M.lower_bound(x);
// if (it != M.begin()) {
//     --it;
//     cout << it->first << ' ' << it->second;
// }
//
// 〇x以下の最大のkey
// auto it = M.upper_bound(x);
// if (it != M.begin()) {
//     --it;
//     cout << it->first << ' ' << it->second;
// }
//
// ============================================================


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << boolalpha;

    map<int, int> M;
    cout << "##### 追加・変更 #####\n";
    M[3] = 30;
    M[1] = 10;
    M[5] = 50;
    M[2] = 20;
    cout << "M: ";
    for (auto [key, value] : M) {
        cout << "(" << key << ", " << value << ") ";
    }
    cout << '\n';
    M[3] = 300;
    cout << "M[3]を300に変更: " << M[3] << '\n';

    cout << "\n##### 検索 #####\n";
    cout << "key=2が存在する？: " << M.contains(2) << '\n';
    auto it = M.find(5);
    if (it != M.end()) {
        cout << "key=5: " << it->second << '\n';
    }

    cout << "\n##### lower_bound / upper_bound #####\n";
    auto lb = M.lower_bound(3);
    auto ub = M.upper_bound(3);
    cout << "keyが3以上の最初: "
         << lb->first << ", " << lb->second << '\n';
    cout << "keyが3より大きい最初: "
         << ub->first << ", " << ub->second << '\n';

    cout << "\n##### 頻度集計（success中の各文字） #####\n";
    string S = "success";
    map<char, int> cnt;
    for (char c : S) cnt[c]++;
    for (auto [x, count] : cnt) {
        cout << x << ": " << count << '\n';
    }

    return 0;
}


// ============================================================
// 補足
// ============================================================
// mapはkeyについてソートされる
//
// map<int, int> M;
// M[5] = 100;
// M[2] = 300;
// M[8] = 200;
//
// range-forではkeyの昇順に取り出される．
//   2 → 5 → 8
// valueの大小は並び順に関係しない．
//
// ============================================================
// M[key]による自動追加
//
// M[key]は，keyが存在しない場合に新しい要素を作成する．
//
// map<int, int> M;
// int x = M[10];
//
// key=10が存在しなくてもエラーにはならず，
//   {10, 0}
// が追加され，x = 0となる．
// stringなら空文字列，vectorなら空vectorなど，
// value型のデフォルト値で作成される．
//
// 存在確認だけをしたい場合は
//   M.contains(key)
//   M.find(key)
// を使う．
//
// ============================================================
// find()とcontains()．どちらもO(log N)
//
// 存在するかだけ調べる：
//   if (M.contains(key)) ...
//
// iteratorが必要：
//   auto it = M.find(key);
//   if (it != M.end()) {
//       cout << it->first;     // key
//       cout << it->second;    // value
//   }
//
// ============================================================
// insert()
//
// M.insert({key, value});
//
// keyがすでに存在する場合，valueは上書きされない．
//
// map<int, int> M;
// M[1] = 10;
// M.insert({1, 100});
//
// M[1]は10のまま．
//
// 単純に追加または上書きしたい場合は
//   M[key] = value;
// が分かりやすい．
//
// ============================================================
// keyは変更できないがvalueは変更できる
//
// auto it = M.find(key);
// NG：
//   it->first = new_key;      // keyは変更不可
// OK：
//   it->second = new_value;   // valueは変更可能
//
// keyを変更したい場合はeraseしてから再度追加する．
//
// ============================================================
// iterator
//
// mapもsetと同様にランダムアクセスできない．
//
// コンパイルエラー：
//   it + 1
//   it - M.begin()
//
// 1つ進む／戻る：
//   ++it;
//   --it;
//
// 複数個進める：
//   next(it, k);      // O(k)
//   prev(it, k);      // O(k)
//
// ============================================================
// 最小key・最大key
//
// Mが空でない場合：
//
// auto [min_key, min_value] = *M.begin();
// auto [max_key, max_value] = *M.rbegin();
//
// または
//   M.begin()->first
//   M.rbegin()->first
//
// ※ 空の場合にbegin()，rbegin()をデリファレンスすると未定義動作．
//
// ============================================================
// at()
//
// M.at(key)でもvalueを取得できる．
//
// M[key]との違い：
//   M[key]    → keyがなければ新しく追加
//   M.at(key) → keyがなければout_of_range例外
//
// 競プロではM[key]，contains()，find()を使うことが多い．
//
// ============================================================
// 降順のmap
//
// keyの大きい順に保持することも可能．
// map<int, int, greater<>> M;
//
// 通常は昇順のmapを使い，最大keyが必要なら
// M.rbegin()を使う方が単純なことが多い．
//
// ============================================================
// ranges::lower_boundではなくメンバ関数を使う
//
// mapでは，
//   M.lower_bound(x);
//   M.upper_bound(x);
// を使用する．どちらもO(log N)．
//
// ranges::lower_boundを使う必要はない．
//
// ============================================================
// 走査しながらerase
//
// for (auto it=M.begin(); it!=M.end(); ) {
//     if (条件) it = M.erase(it);
//     else ++it;
// }
// erase(it)は削除した要素の次を指すイテレータを返す．
// ============================================================
