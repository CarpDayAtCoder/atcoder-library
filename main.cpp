#include <bits/stdc++.h>

#ifdef LOCAL
#include <local_debug.hpp>
#else
#define db(...) ((void)0)
#endif

using namespace std;
using ll = long long;                   // 最大 約9.2×10^18．intは最大 約2.1×10^9
constexpr int INF = 1 << 30;            // 2^30 ≒ 1.07×10^9
constexpr ll LINF = 1LL << 60;          // 2^60 ≒ 1.15×10^18．1'000'000...のようにも書ける
constexpr char nl = '\n';
#define rep(i, a, b) for (int i=(a); i<(b); i++)
#define rrep(i, a, b) for (int i=(a); i>(b); i--)
void yes() { cout << "Yes\n"; }
void no()  { cout << "No\n"; }
void yn(bool f) { cout << (f ? "Yes\n" : "No\n"); }
template <class T>
void pr(const T& x) { cout << x << '\n'; }

int main() {
    ll n;          cin >> n;
    ll n, m;       cin >> n >> m;
    ll h, w;       cin >> h >> w;

    vector<ll> A(n);   for (ll& x : A) cin >> x;
    vector A(n, vector<ll>(m));
    for (auto& row : A)
        for (ll& x : row) cin >> x;

    vector<pair<ll, ll>> AB(n);
    for (auto& [a, b] : AB) cin >> a >> b;
    vector<tuple<ll, ll, ll>> ABC(n);
    for (auto& [a, b, c] : ABC) cin >> a >> b >> c;

    string S;       cin >> S;
    vector<string> S(n);    for (string& s : S) cin >> s;
    vector<string> G(h);    for (string& s : G) cin >> s;   // 文字グリッド
    vector<pair<string, string>> ST(n);
    for (auto& [s, t] : ST) cin >> s >> t;

    yn(/* 条件 */);
    for (auto& x : ans) pr(x);                // 各行に1つ出力
    for (auto& x : ans) cout << x << ' ';
    cout << nl;                               // 1行に空白区切りで出力

    return 0;
}