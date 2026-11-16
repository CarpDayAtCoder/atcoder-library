#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// std::vector まとめ
//
// 使用頻度：★★★★★
// 主な用途：要素数を実行時に決められる可変長配列
// キーワード：vector，push_back，pop_back，resize，assign，erase，reserve
//
// 【基本】
// vector<型> A;
//
// 要素数を実行時に決めることができる．
// push_back()，resize()などによって，作成後に要素数を変更できる．
//
// ============================================================
// 【1次元vectorの生成・初期化】
//
// vector<int> A1;                  // 空，size = 0
// vector<int> A2(n);               // n要素，全要素0
// vector<int> A3(n, -1);           // n要素，全要素-1
// vector<int> A4{1, 2, 3, 4, 5};   // 各要素を指定
//
// 型を自動推論する場合：
// vector A5(n, 0);                 // vector<int>
// vector A6(n, 0LL);               // vector<long long>
// vector A7{1, 2, 3, 4, 5};        // vector<int>
//
// ※ vector A(n); だけでは要素の型を推論できない．
//
// ============================================================
// 【多次元vectorの生成・初期化】
//
// 例：2次元（h行w列）
// vector<vector<int>> A1(h, vector<int>(w));       // 全要素0
// vector<vector<int>> A2(h, vector<int>(w, -1));   // 全要素-1
//
// 型の自動推論を使うと短く書ける：
// vector A3(h, vector(w, 0));      // vector<vector<int>>
// vector A4(h, vector(w, 0LL));    // vector<vector<long long>>
// vector A5(h, vector(w, '.'));    // vector<vector<char>>
//
// 例：3次元（a × b × c）
// vector A6(a, vector(b, vector(c, 0)));
//
// ============================================================
// 【主なメソッド・操作】
//  例：vector<int> A{10, 20, 30};
//
//  〇要素アクセス
//   ・A[i]              // i番目の要素
//   ・A.front()         // 先頭要素
//   ・A.back()          // 最後の要素
//
//  〇要素数
//   ・A.size()          // 要素数
//   ・A.empty()         // 空ならtrue
//
//  〇末尾への追加・削除
//   ・A.push_back(x);      // 末尾にxを追加
//   ・A.emplace_back(...); // 末尾に要素を直接作成．pairやtuple向け
//   ・A.insert(A.end(), B.begin(), B.end())    // Aの後ろにBを連結
//   ・A.pop_back();        // 最後の要素を削除
//
//  ※ front()，back()，pop_back()は空のvectorには使用しない．
//
//  〇要素数の変更
//   ・A.resize(n);      // 要素数をnに変更
//   ・A.resize(n, x);   // 増えた要素をxで初期化
//
//  〇全要素を置き換える
//   ・A.assign(n, x);   // n要素すべてxにする
//
//  〇全要素を削除
//   ・A.clear();        // size = 0
//
//  〇挿入・削除
//   ・A.insert(A.begin() + i, x);       // i番目にxを挿入
//   ・A.erase(A.begin() + i);           // i番目を削除
//   ・A.erase(A.begin() + l, A.begin() + r);   // [l, r)を削除
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

    cout << "##### 1次元vector #####\n";

    vector A(5, 0);     // 要素数5．0で初期化
    cout << "A: ";
    for (int x : A) cout << x << ' ';
    cout << '\n';

    A.push_back(10);    // 10を末尾に追加
    cout << "push_back(10): ";
    for (int x : A) cout << x << ' ';
    cout << '\n';

    A.pop_back();       // 末尾を削除
    cout << "pop_back(): ";
    for (int x : A) cout << x << ' ';
    cout << '\n';

    cout << "size(): " << A.size() << '\n';


    cout << "\n===== resize() =====\n";
    vector B{1, 2, 3};      // 要素数 3
    B.resize(5, -1);        // 要素数 5に変更．追加分は -1で埋める
    cout << "resize(5, -1): ";
    for (int x : B) cout << x << ' ';
    cout << '\n';

    B.resize(2);            // 要素数 2に変更
    cout << "resize(2): ";
    for (int x : B) cout << x << ' ';
    cout << '\n';


    cout << "\n===== insert()，erase() =====\n";
    vector C{10, 20, 30, 40};
    C.insert(C.begin() + 2, 25);    // C[2]の位置に 25 を挿入
    cout << "25を添字2へ挿入: ";
    for (int x : C) cout << x << ' ';
    cout << '\n';

    C.erase(C.begin() + 1);         // C[1]を削除
    cout << "添字1を削除: ";
    for (int x : C) cout << x << ' ';
    cout << '\n';


    cout << "\n##### 2次元vector #####\n";
    int h = 3, w = 4;
    vector D(h, vector(w, -1));     // 2次元（3 x 4）を -1で埋める．
    for (auto& row : D) {
        for (int x : row) cout << setw(3) << x;
        cout << '\n';
    }

    return 0;
}

// ============================================================
// 補足
// ============================================================
// 型の自動推論
//
// 以下の例では，初期値の型からvectorの要素型が推論される．
// vector A(n, 0);        // vector<int>
// vector A(n, 0LL);      // vector<long long>
// vector A(n, 0.0);      // vector<double>
//
// vector A(n);           // NG
// この場合は要素型を推論する材料がないため，
// vector<int> A(n); 
// のように型を指定する必要がある．
//
// ============================================================
// reserve()とresize()
//
// A.reserve(n);
//   capacityをあらかじめ確保する．
//   sizeは変化しない．
//
// A.resize(n);
//   vector自体の要素数をnに変更する．
//
// 例：
//   vector<int> A;
//   A.reserve(100);      // size() == 0
//   A.push_back(10);     // size() == 1
//
// reserve()はpush_back()を大量に行う場合に，
// メモリの再確保を減らせることがある．
//
// ============================================================
// size()とcapacity()
//
// size()
//   現在実際に存在する要素数．
// capacity()
//   現在再確保せずに保持できる要素数．
// 通常の競技プログラミングでは，capacity()を直接使う機会は少ない．
//
// ============================================================
// resize()で要素数を増やす場合
//
// intなどの場合，追加された要素は0で初期化される．
// vector<int> A{1, 2, 3};
// A.resize(5);　　　// → {1, 2, 3, 0, 0}
//
// 第2引数は「新しく追加された要素」の初期値．
// A.resize(5, -1);
// → {1, 2, 3, -1, -1}
//
// ============================================================
// assign()
//
// resize()と違い，元の要素は残さず，全体を置き換える．
// vector<int> A{1, 2, 3};
// A.assign(5, -1);     // → {-1, -1, -1, -1, -1}
//
// ============================================================
// push_back()とemplace_back()
//
// vector<pair<int, int>> P;
// P.push_back({1, 10});
// P.emplace_back(1, 10);
//
// どちらもpair{1, 10}を末尾へ追加できる．
// 競プロではpush_back({a, b})でも十分短く，分かりやすい．
//
// ============================================================
// 要素の削除
//
// erase()は位置を指定して削除する．
// vector<int> A{1, 2, 3, 2, 4};
// A.erase(A.begin() + 1);      // → {1, 3, 2, 4}
//
// 値を指定してすべて削除する場合，C++20以降では
// erase(A, 2);     // → {1, 3, 4}
// と書くこともできる．
//
// ============================================================
// rangesとの組合せ
//
// vectorはrangesを使う代表的なコンテナ．
// ranges::sort(A);                 // 昇順
// ranges::sort(A, greater<>());    // 降順
// ranges::reverse(A);              // 逆順
// ranges::max(A);                  // 最大値
// ranges::min(A);                  // 最小値
// ranges::find(A, x);              // xを探索
// ranges::count(A, x);             // xの個数
//
// ============================================================
// vectorとarray，C配列の使い分け
//
// 【vector】
//   vector<int> A(n);
//   ・要素数を実行時に決められる
//   ・resize()，push_back()などで要素数を変更できる
//
// 【std::array】
//   array<int, 5> A;
//   ・要素数はコンパイル時に固定
//   ・fill()，size()などを使用できる
//
// 【C配列】
//   int A[5];
//   ・要素数は固定
//   ・記述が短い
//
// 使い分けの目安：
//   要素数が実行時に決まる
//       → vector
//   固定長で，fill()，size()などを使いたい
//       → array
//   固定長で単純な配列として使いたい
//       → C配列でもよい
//
// ============================================================
// at()による範囲チェック
//
// A.at(i)は，i番目の要素へアクセスする．
// A[i]と異なり，範囲外ならout_of_range例外を投げる．
//
// vector<int> A{10, 20, 30};
// A[1];      // 20．範囲チェックなし
// A.at(1);   // 20．範囲チェックあり
// A.at(5);   // 範囲外なので例外
//
// 競プロでは通常A[i]を使うことが多い．
//
// ============================================================