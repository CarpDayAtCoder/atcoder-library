#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
using ll = long long;

// ============================================================
// __int128 まとめ
//
// 使用頻度：★★☆☆☆
// 主な用途：long longを超える整数計算
//
// GCC拡張．AtCoderのC++環境で使用可能．
//
// using lll = __int128_t;       // 符号付き128bit整数
//
// 最大値：約1.7×10^38
// long longの最大値：約9.2×10^18
//
// 【重要】
// __int128はcoutで直接出力できないため，operator<<を定義する．
// また，計算途中でlong longがoverflowしないように，
// 掛け算の前に__int128へ変換する．
//
// ll a, b;
// lll x = (lll)a * b;       // OK
// lll x = a * b;            // NGの可能性あり
//                           // a*bをlong longで計算してから代入される
//
// ============================================================
// 実行例
// ============================================================
#if 1

using lll = __int128_t;
using ulll = __uint128_t;
ostream& operator<<(ostream& os, lll x) {   // __int128の出力
    if (x == 0) return os << '0';
    bool minus = (x < 0);
    // unsignedへ変換して絶対値を作る．__int128の最小値でも安全に処理できる．
    ulll u;
    if (minus)  u = 0 - (ulll)x;
    else        u = (ulll)x;
    string s;
    while (u > 0) {
        s += '0' + u % 10;
        u /= 10;
    }
    if (minus) os << '-';
    reverse(s.begin(), s.end());
    return os << s;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    ll a = 1'000'000'000'000'000'000LL;   // 10^18
    lll x = (lll)a * a;                    // 10^36
    cout << x << '\n';

    return 0;
}

#endif


// ============================================================
// 補足
// ============================================================
// 【型変換してから計算する】
//
// 次は危険：
// ll a, b;
// lll x = a * b;
//
// a*bはlong long同士なので，__int128へ代入する前にoverflowする可能性がある．
// どちらか一方を先に__int128へ変換する：
// lll x = (lll)a * b;
//
// ============================================================
// 【入力について】
//
// long longに収まる値なら，
// ll a;    cin >> a;
// lll x = a;
// でよい．
//
// long longを超える値そのものを入力する場合は，
// stringとして受け取り，1桁ずつ__int128へ変換する必要がある．
//
// ============================================================