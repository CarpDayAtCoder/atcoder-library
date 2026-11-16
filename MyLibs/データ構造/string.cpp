#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// std::string まとめ
//
// 使用頻度：★★★★★
// 主な用途：文字列の保存，追加，削除，検索，部分文字列の取得
// キーワード：string，size，substr，find，push_back，stoi，to_string
//
// 【基本】
// string S;
//
// stringは文字charを並べた可変長の文字列．
// 添字は0-indexで，S[i]によって各文字へアクセスできる．
//
// ============================================================
// 【生成・初期化】
//
// string S1;                  // 空文字列 ""
// string S2 = "abc";          // "abc"
// string S3{"abc"};           // "abc"
// string S4(5, 'a');          // "aaaaa"
// string S5 = S2;             // コピー
//
// ============================================================
// 【主なメソッド・操作】
//  例：string S = "abcde";
//
//  〇要素アクセス
//   ・S[i]              // i番目の文字
//   ・S.front()         // 先頭の文字
//   ・S.back()          // 最後の文字
//
//  〇長さ
//   ・S.size()          // 文字数
//   ・S.length()        // size()と同じ
//   ・S.empty()         // 空文字列ならtrue
//
// 〇末尾への追加
//  ・S += 'x';              // 文字を1つ追加．push_back('x')でも同じ
//  ・S += "xyz";            // 文字列を追加．append("xyz")でも同じ
//  ・S.append(k, 'x');      // 同じ文字をk個追加
//
// 〇末尾から削除
//  ・S.pop_back();          // 最後の1文字を削除
//  ・S.resize(S.size()-k);  // 末尾のk文字を削除
//
//  〇文字列を空にする
//   ・S.clear();
//
//  〇部分文字列
//   ・S.substr(pos, len)     // posからlen文字
//   ・S.substr(pos)          // posから最後まで
//
//  〇検索
//   ・S.find("abc")          // 最初に現れる位置
//   ・S.find('a')            // 文字も検索可能
//   ・S.rfind("abc")         // 最後に現れる位置
//   ・見つからない場合は string::npos
//
//  〇挿入・削除・置換
//   ・S.insert(pos, "abc")       // posに文字列を挿入
//   ・S.erase(pos, len)          // posからlen文字削除
//   ・S.replace(pos, len, "abc") // posからlen文字を置換
//
// ※ front()，back()，pop_back()は空文字列には使用しない．
// ============================================================
// 【数値との変換】
//
// string → 数値
//   int x = stoi(S);
//   long long x = stoll(S);
//   double x = stod(S);
//
// 数値 → string
//   string S = to_string(x);
//
// ============================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "##### string #####\n";

    string S = "abcde";
    cout << "S: " << S << '\n';
    cout << "文字数: " << S.size() << '\n';
    cout << "先頭: " << S.front() << '\n';
    cout << "最後: " << S.back() << '\n';


    cout << "\n===== 文字の追加・削除 =====\n";
    S += 'f';
    cout << "S += 'f': " << S << '\n';
    S += "gh";
    cout << "S += \"gh\": " << S << '\n';
    S.pop_back();
    cout << "pop_back(): " << S << '\n';


    cout << "\n===== substr() =====\n";
    string T = "abcdefgh";
    cout << "T: " << T << '\n';
    cout << "T.substr(2, 3): " << T.substr(2, 3) << '\n';  // "cde"
    cout << "T.substr(5): " << T.substr(5) << '\n';        // "fgh"


    cout << "\n===== find() =====\n";
    string U = "abcabc";
    cout << "U: " << U << '\n';
    auto pos = U.find("bc");
    if (pos != string::npos) {
        cout << "\"bc\"が最初に現れる位置: " << pos << '\n';
    }


    cout << "\n===== 数値との変換 =====\n";
    string num = "12345";
    int x = stoi(num);
    cout << "stoi(\"12345\"): " << x << '\n';
    string V = to_string(6789);
    cout << "to_string(6789): " << V << '\n';


    cout << "\n===== ranges =====\n";
    string W = "dbca";
    ranges::sort(W);
    cout << "sort: " << W << '\n';
    ranges::reverse(W);
    cout << "reverse: " << W << '\n';

    return 0;
}

// ============================================================
// 補足
// ============================================================
// charとstring
//
// 'a'   ：char，1文字
// "a"   ：文字列リテラル．stringの初期化や追加などに使用できる
//
// ============================================================
// 大文字・小文字の変換，文字種判定
//
// C++ではstring全体に対するlower()，upper()はない．
// tolower()，toupper()を各文字に適用する．
//
// 〇1文字の変換
// char c = 'A';
// c = tolower(c);       // 'a'
// c = 'a';
// c = toupper(c);       // 'A'
//
// 〇string全体を小文字に変換
// ranges::transform(S, S.begin(), [](unsigned char c) {
//     return tolower(c);
// });
//
// 〇string全体を大文字に変換
// ranges::transform(S, S.begin(), [](unsigned char c) {
//     return toupper(c);
// });
//
// 〇文字種の判定
// islower(c)    // 小文字ならtrue
// isupper(c)    // 大文字ならtrue
// isalpha(c)    // 英字ならtrue
// isdigit(c)    // 数字ならtrue
// isalnum(c)    // 英数字ならtrue
// isspace(c)    // 空白文字ならtrue
//
// ============================================================
// find()とstring::npos
//
// string::nposは「見つからなかった」ことを表す特殊な値．
// 使用例：
//   auto pos = S.find("abc");
//   if (pos != string::npos) {
//       // 見つかった
//   }
//
// ============================================================
// find_first_of()，find_first_not_of()など
//
// 指定した文字集合に含まれる／含まれない文字の位置を探す．
//
// string S = "000123400";
// S.find_first_of("123");       // 3．'1','2','3'のいずれかが最初に現れる位置
// S.find_first_not_of('0');     // 3．'0'以外が最初に現れる位置
// S.find_last_of('0');          // 8．'0'が最後に現れる位置
// S.find_last_not_of('0');      // 6．'0'以外が最後に現れる位置
//
// 見つからない場合はstring::nposを返す．
//
// 例：先頭の連続する'0'を除く
// auto pos = S.find_first_not_of('0');
// if (pos == string::npos)     S = "0";    // 全文字が'0'
// else                         S = S.substr(pos);
//
// ※ find("abc")は文字列"abc"そのものを探す．
//    find_first_of("abc")は'a','b','c'のいずれか1文字を探す．
//
// ============================================================
// substr(pos, len)
//
// string S = "abcdefgh";
// S.substr(2, 3)   // "cde"
// S.substr(2)      // "cdefgh"
//
// 第2引数は終了位置ではなく「文字数」であることに注意．
//
// ============================================================
// starts_with()，ends_with()，contains()
//
// C++20：
//   S.starts_with("abc")    // "abc"で始まるか
//   S.ends_with("xyz")      // "xyz"で終わるか
// C++23：
//   S.contains("abc")       // "abc"を含むか
//
// ============================================================
// rangesとの組合せ
//
// stringも文字のrangeとして扱える．
// ranges::sort(S);                 // 文字を昇順ソート
// ranges::sort(S, greater<>());    // 降順ソート
// ranges::reverse(S);              // 逆順
// ranges::count(S, 'a');           // 'a'の個数
// ranges::find(S, 'a');            // 'a'を検索
//
// ============================================================
// reserve()とresize()
//
// string S;
//
// S.reserve(n);
//   容量capacityをあらかじめ確保する．文字数sizeは0のまま．
//   文字列を何度も追加するとき，再確保を減らせる場合がある．
//
// S.resize(n);
//   文字列自体の長さをnに変更する．
//   文字列を長くする場合，追加された文字は'\0'で初期化される．
//
// string S(n, '?');
//   最初から長さnで，全要素'?'の文字列を作成する．
//
// 例：
//   string S;
//   S.reserve(100);       // size()は0
//   S += "abc";           // 普通に追加できる
//
// ============================================================
// at()による範囲チェック
//
// S.at(i)は，i番目の文字へアクセスする．
// S[i]と異なり，範囲外ならout_of_range例外を投げる．
//
// string S = "abc";
// S[1];      // 'b'．範囲チェックなし
// S.at(1);   // 'b'．範囲チェックあり
// S.at(5);   // 範囲外なので例外
//
// 競プロでは通常S[i]を使うことが多い．
//
// ============================================================
// 【文字列の入力】
//
// 空白を含まない文字列：
//   cin >> S;
//
// 空白を含む1行：
//   getline(cin, S);
//
// cin >> の直後にgetline()する場合：
//   getline(cin >> ws, S);
//
// ============================================================
