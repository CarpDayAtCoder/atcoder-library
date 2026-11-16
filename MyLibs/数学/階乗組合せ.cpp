// ============================================================
// 階乗・組合せ
//
// 使用頻度：★★★★☆
// 主な用途：mod上での階乗，逆階乗，組合せ nCr の高速計算
// キーワード：階乗，逆階乗，組合せ，nCr，modint，逆元
//
// 階乗factと逆階乗inv_factをO(N)で前計算する．
// 前計算後はcomb(n, r)をO(1)で計算できる．
//
// 前処理：O(N + log MOD)
// comb：O(1)
// メモリ：O(N)
//
// ※ fact[N]の逆元を利用するため，N < MODで使用する．
// ※ modintの割り算は逆元計算を行うため，ループ内で何度も使わない．
//
// ============================================================

#if 0
// ============================================================
// 実戦用
// ============================================================

#include <bits/stdc++.h>
using namespace std;

#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;   // MOD = 998244353

vector<mint> fact, inv_fact;

// 0! ～ N!，およびその逆数を前計算
void init_comb(int N) {
    fact.assign(N + 1, 1);
    inv_fact.assign(N + 1, 1);

    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i;
    }

    inv_fact[N] = fact[N].inv();

    for (int i = N; i >= 1; i--) {
        inv_fact[i - 1] = inv_fact[i] * i;
    }
}

// nCr
mint comb(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n - r];
}

int main() {
    int N;
    cin >> N;

    init_comb(N);

    int n, r;
    cin >> n >> r;
    cout << comb(n, r).val() << '\n';

    return 0;
}

#endif

#if 1
// ============================================================
// 学習用
// ============================================================

#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;   // MOD = 998244353

vector<mint> fact, inv_fact;

// ============================================================
// 階乗・逆階乗の前計算
//
// fact[i]     = i!
// inv_fact[i] = 1 / i!
//
// まず，
//   fact[i] = fact[i - 1] * i
// により階乗を前から計算する．
//
// 逆階乗は，最大のN!についてだけ逆元を求める．
//   inv_fact[N] = 1 / N!
//
// i! = i * (i - 1)! より，
//   1 / (i - 1)! = i / i!
// したがって，
//   inv_fact[i - 1] = inv_fact[i] * i
// として後ろから計算できる．
//
// この方法なら，重い逆元計算は1回だけでよい．
// ============================================================

void init_comb(int N) {
    fact.assign(N + 1, 1);              // 全て1を割当
    inv_fact.assign(N + 1, 1);

    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i;      // 階乗の計算
    }

    inv_fact[N] = fact[N].inv();        // 1/N! の計算

    for (int i = N; i >= 1; i--) {
        inv_fact[i - 1] = inv_fact[i] * i;  // 逆階乗の計算
    }
}

// ============================================================
// 組合せ nCr
//
//            n!
// nCr = -------------
//        r! (n-r)!
//
// 逆階乗を使うことで，割り算をせず，
//   fact[n] * inv_fact[r] * inv_fact[n-r]
// としてO(1)で計算できる．
//
// r < 0，r > nの場合は組合せが存在しないので0を返す．
// ============================================================

mint comb(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n - r];
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int N = 10;
    init_comb(N);

    cout << "===== 階乗 =====\n";
    for (int i = 0; i <= 5; i++) {
        cout << "　" << i << "! = " << fact[i].val() << '\n';
    }

    cout << "\n===== 組合せ =====\n";
    cout << "　5C2 = " << comb(5, 2).val() << '\n';
    cout << "　8C3 = " << comb(8, 3).val() << '\n';
    cout << "　10C5 = " << comb(10, 5).val() << '\n';

    cout << "\n===== 範囲外 =====\n";
    cout << "　5C6 = " << comb(5, 6).val() << '\n';

    return 0;
}

#endif

// ============================================================
// 補足
//
// 【なぜ毎回割り算しないのか】
//
// modintにおける
//   a / b
// は通常の整数除算ではなく，bの逆元を求めて掛けている．
//
// そのため，多数のcombを求める場合に，
//   fact[n] / fact[r] / fact[n-r]
// と毎回書くよりも，inv_factを前計算して，
//   fact[n] * inv_fact[r] * inv_fact[n-r]
// とする方が高速．
//
// ------------------------------------------------------------
// 【順列 nPr】
//
// factとinv_factがあれば，順列もO(1)で計算できる．
//   nPr = n! / (n-r)!
//
// mint perm(int n, int r) {
//     if (r < 0 || r > n) return 0;
//     return fact[n] * inv_fact[n - r];
// }
//
// ------------------------------------------------------------
// 【階乗そのもの】
//
// init_comb(N)の後は，
//   fact[n]       // n!
//   inv_fact[n]   // 1 / n!
// として直接利用できる．
//
// ------------------------------------------------------------
// 【注意】
//
// この方法ではfact[N]の逆元を求めるため，
//   N < MOD
// の範囲で使用する．
//
// modint998244353の場合，通常のAtCoder問題で
// Nが10^5～10^7程度なら問題ないことが多いが，制約は必ず確認する．
// ============================================================