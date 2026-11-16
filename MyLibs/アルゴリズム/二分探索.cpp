#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// 二分探索テンプレート
//
// 使用頻度：★★★★★
// 主な用途：答えを仮定したときの可否判定に単調性がある問題
// キーワード：二分探索，めぐる式，check，ok，ng
//
// 【基本形】
//   ok : check(ok) == true となることが確実な値
//   ng : check(ng) == false となることが確実な値
//
// ok < ng でも ok > ng でも使用できる．
// 最後まで「okはOK，ngはNG」という関係を維持する．
//
// 整数二分探索：
//   int，long long の両方に同じ関数を使用できる．
//   okとngの差が1になるまで探索する．
//   戻り値は「NGとの境界に最も近いOK」．
//
// 実数二分探索：
//   double用．
//   okとngの距離がepsilon以下になるまで探索する．
//   戻り値はOK側の近似値．
//
// 【重要】
// check(x)には単調性が必要．
// 例1：
// true true true true false false false
//                    ↑
//            最大のOKを求める
// 例2：
// false false false true true true true
//                   ↑
//            最小のOKを求める
// ============================================================

// ============================================================
// 実戦用テンプレート
// ============================================================
#if 0
using ll = long long;

// 整数二分探索（int，long long 共通）
template<class T, class F>
T binary_search_integer(T ok, T ng, F check) {
    while (abs(ok - ng) > 1) {
        T mid = midpoint(ok, ng);

        if (check(mid)) ok = mid;
        else            ng = mid;
    }
    return ok;
}
// 実数二分探索
template<class F>
double binary_search_double(double ok, double ng, double epsilon, F check) {
    while (abs(ok - ng) > epsilon) {
        double mid = midpoint(ok, ng);
        if (check(mid)) ok = mid;
        else            ng = mid;
    }
    return ok;
}

int main() {
    int n;      cin >> n;
    vector A(n, 0LL);
    for (auto& x : A) cin >> x;

    auto check = [&](ll v) {    // 実数版では double v
        // 問題ごとの判定処理を書く．
        // vが実現可能ならtrue
        // vが実現不可能ならfalse
        return true;
    };
    // 整数型
    ll ok = 0;              // 確実にOKな値を設定
    ll ng = 1LL << 60;      // 確実にNGな値を設定
    ll ans = binary_search_integer(ok, ng, check);
    // 実数型
    // double ok = 0.;         // 確実にOKな値を設定
    // double ng = 1e10;       // 確実にNGな値を設定
    // double epsilon = 1e-10; // 許容誤差を設定
    // double ans = binary_search_double(ok, ng, epsilon, check);

    cout << ans << '\n';
    return 0;
}

#endif


// ============================================================
// 学習用実行例
// ============================================================
#if 1
using ll = long long;

// 整数二分探索（int，long long 共通）
template<class T, class F>
T binary_search_integer(T ok, T ng, F check) {
    while (abs(ok - ng) > 1) {
        T mid = midpoint(ok, ng);

        if (check(mid)) ok = mid;
        else            ng = mid;
    }
    return ok;
}
// 実数二分探索
template<class F>
double binary_search_double(double ok, double ng, double epsilon, F check) {
    while (abs(ok - ng) > epsilon) {
        double mid = midpoint(ok, ng);
        if (check(mid)) ok = mid;
        else            ng = mid;
    }
    return ok;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "===== 整数二分探索 =====\n";

    // x^2 <= 50 となる最大の整数を求める
    auto check = [](ll x) {
        return x * x <= 50;
    };

    ll ok = 0;       // check(0) == true
    ll ng = 50;      // check(50) == false

    ll ans = binary_search_integer(ok, ng, check);
    cout << "　探索条件: x^2 <= 50\n";
    cout << "　初期OK: " << ok << '\n';
    cout << "　初期NG: " << ng << '\n';
    cout << "　最大のOK: " << ans << '\n';


    cout << "\n===== 実数二分探索 =====\n";

    // x^2 >= 2 を満たす最小のx ≒ √2 を求める．
    auto check2 = [](double x) {
        return x * x >= 2.0;
    };

    double ok2 = 2.0;       // 確実にOK
    double ng2 = 0.0;       // 確実にNG
    double epsilon = 1e-10;

    double ans2 = binary_search_double(ok2, ng2, epsilon, check2);
    cout << fixed << setprecision(10);
    cout << "　探索条件: x^2 >= 2\n";
    cout << "　√2の近似値: " << ans2 << '\n';

    return 0;
}

#endif