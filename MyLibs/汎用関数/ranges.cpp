#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// C++ ranges まとめ
//
// 使用頻度：★★★★★
//
// 【ソート・並び替え】
//   ranges::sort(A);                       // 昇順
//   ranges::sort(A, greater<>());          // 降順
//   ranges::reverse(A);                    // 逆順
//   ranges::sort(T, {}, [](const auto& t) {
//       return get<2>(t);                  // tupleの3番目で昇順
//   });
//   ranges::sort(T, greater<>(), [](const auto& t) {
//       return get<2>(t);                  // tupleの3番目で降順
//   });
//   ranges::sort(P, [](const auto& a, const auto& b) {
//       if (a.second != b.second) return a.second < b.second;
//       return a.first < b.first;          // pairをsecond, firstの順に昇順
//   });
//
// 【カウント】
//   auto cnt = ranges::count(A, x);         // xの個数
//   auto cnt = ranges::count_if(A, f);      // 条件fを満たす個数
//
// 【探索】
//   auto it = ranges::find(A, x);           // xへのイテレータ．なければA.end()
//   auto it = ranges::find_if(A, f);        // 条件fを満たす最初．なければA.end()
//
// 【最大・最小】
//   auto mx = ranges::max(A);               // 最大値
//   auto mn = ranges::min(A);               // 最小値
//   auto it = ranges::max_element(A);       // 最大値へのイテレータ
//   auto it = ranges::min_element(A);       // 最小値へのイテレータ
//
// 【二分探索】※検索対象について昇順であること
//   auto lb = ranges::lower_bound(A, x);    // x以上の最初の要素を指すイテレータ
//   int cnt1 = lb - A.begin();              // x未満の要素数
//   auto ub = ranges::upper_bound(A, x);    // xより大きい最初の要素を指すイテレータ
//   int cnt2 = ub - A.begin();              // x以下の要素数
//   bool f = ranges::binary_search(A, x);   // xが存在するか
//
// 【その他】
//   ranges::fill(A, x);                     // 全要素をxにする
//
// ============================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << boolalpha;

    // ========================================================
    // 1次元vector
    // ========================================================
    vector A{5, 2, 8, 2, 4};

    // 【ソート】
    cout << "===== sort()，reverse() =====\n";

    ranges::sort(A);
    cout << "昇順: ";
    for (int x : A) cout << x << ' ';
    cout << '\n';

    ranges::sort(A, greater<>());
    cout << "降順: ";
    for (int x : A) cout << x << ' ';
    cout << '\n';

    ranges::reverse(A);
    cout << "逆順: ";
    for (int x : A) cout << x << ' ';
    cout << '\n';


    // 【カウント】
    cout << "\n===== count()，count_if() =====\n";
    cout << "2の個数: " << ranges::count(A, 2) << '\n';
    int even_count = ranges::count_if(A, [](int x) {
        return x % 2 == 0;
    });
    cout << "偶数の個数: " << even_count << '\n';


    // 【最大・最小】
    cout << "\n===== max()，min() =====\n";
    cout << "最大値: " << ranges::max(A) << '\n';
    cout << "最小値: " << ranges::min(A) << '\n';


    // 【探索】
    cout << "\n===== find() =====\n";
    auto it = ranges::find(A, 8);
    if (it != A.end()) {
        cout << "8が見つかった\n";
        cout << "添字: " << it - A.begin() << '\n';
    }


    // 【二分探索】
    cout << "\n===== lower_bound()，upper_bound() =====\n";
    ranges::sort(A);       // {2, 2, 4, 5, 8}
    auto lb = ranges::lower_bound(A, 2);    // 2以上の最初の要素を指す
    cout << "2以上の最初の値: " << *lb << '\n';               // 2
    cout << "2未満の個数: " << lb - A.begin() << '\n';       // 0
    auto ub = ranges::upper_bound(A, 2);    // 2より大きい最初の要素を指す
    cout << "2より大きい最初の値: " << *ub << '\n';          // 4
    cout << "2以下の個数: " << ub - A.begin() << '\n';       // 2
    cout << "5は存在する？: "
        << ranges::binary_search(A, 5) << '\n';


    // 【条件判定】
    cout << "\n===== all_of()，any_of()，none_of() =====\n";
    cout << "全要素が正？: "
         << ranges::all_of(A, [](int x) { return x > 0; }) << '\n';
    cout << "偶数が1つ以上ある？: "
         << ranges::any_of(A, [](int x) { return x % 2 == 0; }) << '\n';
    cout << "負数が1つもない？: "
         << ranges::none_of(A, [](int x) { return x < 0; }) << '\n';

    // ========================================================
    // pair
    // ========================================================
    cout << "\n===== pair：projection =====\n";

    vector<pair<int,int>> P{
        {1, 80},
        {2, 50},
        {3, 90},
        {4, 70}
    };      // {番号，点数}

    // second（点数）で昇順
    ranges::sort(P, {}, &pair<int,int>::second);

    cout << "点数順: ";
    for (auto [id, score] : P) {
        cout << "(" << id << ", " << score << ") ";
    }
    cout << '\n';

    // second（点数）について二分探索
    auto it2 = ranges::lower_bound(
        P, 75, {}, &pair<int,int>::second
    );

    if (it2 != P.end()) {
        cout << "点数75以上で最初の人: "
             << "番号" << it2->first
             << "，点数" << it2->second << '\n';
    }


    // ========================================================
    // tuple
    // ========================================================
    cout << "\n===== tuple：projection =====\n";

    vector<tuple<int,int,int>> T{
        {3, 10, 7},
        {5, 20, -2},
        {1, 30, 4},
        {8, 40, 10}
    };

    // 3番目で昇順
    ranges::sort(T, {}, [](const auto& t) {
        return get<2>(t);
    });

    cout << "3番目で昇順:\n";
    for (auto [a, b, d] : T) {
        cout << a << ' ' << b << ' ' << d << '\n';
    }

    // 3番目で降順
    ranges::sort(T, greater<>(), [](const auto& t) {
        return get<2>(t);
    });

    cout << "3番目で降順:\n";
    for (auto [a, b, d] : T) {
        cout << a << ' ' << b << ' ' << d << '\n';
    }

    return 0;
}


// ============================================================
// 補足
// ============================================================
// 【lower_bound / upper_bound】
//
// auto lb = ranges::lower_bound(A, x);
//   → x以上の最初の要素を指すiterator
//   → lb - A.begin() は x未満の要素数
//
// auto ub = ranges::upper_bound(A, x);
//   → xより大きい最初の要素を指すiterator
//   → ub - A.begin() は x以下の要素数
//
// Aがvector<ll>なら戻り値の型は
// vector<ll>::iterator
//
// 先に宣言して使い回す場合：
// vector<ll>::iterator ub;
// ub = ranges::upper_bound(A, x);
//
// 一般には
// decltype(A.begin()) ub;
// とも書ける．
//
// 【注意】
// 条件を満たす要素がなければend()を返す．
// この場合 *ub は不可．
// ub - A.begin() は問題なく使用できる．
//
// ============================================================
// 【比較関数】
//
// cmp(a, b) がtrueなら，aをbより前に並べる．
//
// 例：文字列a，bについて，a+b > b+aとなる順
//   auto cmp = [](const string& a, const string& b) {
//       return a + b > b + a;
//   };
//   ranges::sort(A, cmp);
//
// 1回しか使わない場合は直接書いてもよい．
//   ranges::sort(A, [](const auto& a, const auto& b) {
//       return a.second > b.second;
//   });
//
// ※ <=，>= は基本的に使わない．
//    同じ要素同士についてcmp(a, a) == falseとなる必要がある．
//
// ============================================================
// 【projection（射影）】
//
// 各要素全体ではなく，一部分を比較対象にする．
//
// 例）pairのsecondに対する各種処理
//   vector<pair<int,int>> P;
//   ranges::sort(P, {}, &pair<int,int>::second);           // secondで昇順
//   ranges::sort(P, greater<>(), &pair<int,int>::second);  // secondで降順
//   // secondが最大のpairそのもの
//   auto p = ranges::max(P, {}, &pair<int,int>::second);
//   // secondが最大のpairへのイテレータ
//   auto it = ranges::max_element(
//       P, {}, &pair<int,int>::second
//   );
//
// ------------------------------------------------------------
// 複数項目をprojectionにする
//
// ranges::sort(P, {}, [](const auto& p) {
//     return pair{p.second, p.first};      // second → first の順で昇順
// });
// ranges::sort(T, {}, [](const auto& t) {
//     return tuple{                        // 3番目 → 1番目 → 2番目 の順で昇順
//         get<2>(t), get<0>(t), get<1>(t)
//     };
// });
//
// ============================================================
// 【projection付き二分探索】
//
// projection後の値について昇順になっている必要がある．
//
// vector<pair<int,int>> P;
// auto it = ranges::lower_bound(
//     P, x, {}, &pair<int,int>::second     // secondについてx以上となる最初
// );
// auto it = ranges::upper_bound(
//     P, x, {}, &pair<int,int>::second     // secondについてxより大きい最初
// );
//
// ============================================================
// 【条件判定】
//   ranges::all_of(A, f);       // 全要素が条件fを満たすならtrue
//   ranges::any_of(A, f);       // 1つ以上の要素が条件fを満たすならtrue
//   ranges::none_of(A, f);      // 条件fを満たす要素が1つもなければtrue
//
// ============================================================
// 【従来型との対応】
//
// ranges::sort(A);                 sort(A.begin(), A.end());
// ranges::sort(A, greater<>());    sort(A.begin(), A.end(), greater<>());
// ranges::reverse(A);              reverse(A.begin(), A.end());
// ranges::count(A, x);             count(A.begin(), A.end(), x);
// ranges::find(A, x);              find(A.begin(), A.end(), x);
// ranges::max_element(A);          max_element(A.begin(), A.end());
// ranges::min_element(A);          min_element(A.begin(), A.end());
// ranges::lower_bound(A, x);       lower_bound(A.begin(), A.end(), x);
// ranges::upper_bound(A, x);       upper_bound(A.begin(), A.end(), x);
//
// ============================================================
// 【合計】
//
// ranges::sum(A) は存在しない．
// long long sum = accumulate(A.begin(), A.end(), 0LL);
//
// ============================================================