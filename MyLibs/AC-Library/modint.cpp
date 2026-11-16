#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// AC-Library modint（mint）テンプレート
//
// 使用頻度：★★★★★
// 主な用途：MODを取りながら行う加減乗除，累乗，逆元
// キーワード：val，mod，pow，inv，set_mod
//
// 【固定MOD】
// using mint = modint998244353;
// using mint = modint1000000007;
//
// 【可変MOD】
// using mint = modint;
// mint::set_mod(MOD);                 // mintを使う前に設定
//
// mint a = x;
//   整数xをmint型として保存する．自動的にMODを取る．
//
// a.val();
//   mintが保持している0以上MOD未満の整数値を返す．
//
// mint::mod();
//   現在使用しているMODを返す．
//
// a + b，a - b，a * b，a / b;
//   MOD上で加減乗除を行う．
//
// a += b，a -= b，a *= b，a /= b;
//   複合代入演算子も使用できる．
//
// a.pow(k);
//   aのk乗をMOD上で計算する．kは0以上の整数．
//
// a.inv();
//   aの乗法逆元を返す．
//
// mint::raw(x);
//   MODを取らず，xをそのままmintへ格納する高速化用機能．
//   0 <= x < MOD が必須なので，通常は使用しなくてよい．
//
// 【割り算の注意】
// a / b は，bの逆元を利用して計算される．
// bとMODが互いに素で，逆元が存在する必要がある．
// 998244353や1000000007では，bがMODの倍数でなければよい．
//
// 使用するmainを #if 1，使用しないmainを #if 0 にする．
// ============================================================


// ============================================================
// 実戦用テンプレート
// ============================================================
#if 0
#include <atcoder/modint>
using namespace atcoder;

using mint = modint998244353;         // MOD = 998244353
// using mint = modint1000000007;     // MOD = 1000000007
// using mint = modint;               // 可変MODの場合
//    mint::set_mod(MOD);             // 可変MODの場合，プログラム中で mintを使う前にMODを設定

int main() {
    int n;  cin >> n;
    mint ans = 0;                              // 答えをmint型で管理

    for (int i = 0; i < n; i++) {
        long long x;    cin >> x;
        ans += x;                              // 自動的にMODを取る
    }
    cout << ans.val() << '\n';                 // 通常の整数値として出力
    return 0;
}

#endif


// ============================================================
// 学習用実行例
// 固定MOD = 998244353 を使用する．
// ============================================================

#if 1
#include <atcoder/modint>
using namespace atcoder;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    using mint = modint998244353;

    cout << "===== 使用しているMOD =====\n";
    cout << "　MOD: " << mint::mod() << '\n';


    cout << "\n===== mint型の作成とval() =====\n";
    mint a = 1'000'000'000;                    // MODより大きい値
    mint b = 3;
    cout << "　1,000,000,000をMODで割った余り: "
         << a.val() << '\n';
    cout << "　bの値: "
         << b.val() << '\n';

    cout << "\n===== 加減乗除 =====\n";
    mint sum = a + b;
    mint difference = a - b;
    mint product = a * b;
    mint quotient = a / b;  // 通常の割り算ではなく，MOD上での割り算
    cout << "　a + b: " << sum.val() << '\n';
    cout << "　a - b: " << difference.val() << '\n';
    cout << "　a * b: " << product.val() << '\n';
    cout << "　a / b: " << quotient.val() << '\n';

    cout << "\n===== 複合代入演算子 =====\n";
    mint x = 10;
    cout << "　最初のx: " << x.val() << '\n';
    x += 5;
    cout << "　x += 5 の結果: " << x.val() << '\n';
    x *= 3;
    cout << "　x *= 3 の結果: " << x.val() << '\n';
    x -= 7;
    cout << "　x -= 7 の結果: " << x.val() << '\n';
    x /= 2;
    cout << "　x /= 2 の結果: " << x.val() << '\n';

    cout << "\n===== pow()による累乗 =====\n";
    mint power = mint(2).pow(10);
    cout << "　2の10乗をMODで割った余り: "
         << power.val() << '\n';

    cout << "\n===== inv()による逆元 =====\n";
    mint inverse = mint(3).inv();
    cout << "　3の逆元: "
         << inverse.val() << '\n';
    cout << "　3 × 3の逆元: "
         << (mint(3) * inverse).val() << '\n';

    cout << "\n===== 負の値も気にせず使える =====\n";
    mint negative = -1;
    cout << "　-1をMOD上で表した値: "
         << negative.val() << '\n';

    return 0;
}

#endif