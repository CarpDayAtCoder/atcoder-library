#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// グリッドBFS まとめ
//
// 使用頻度：★★★★★
// 主な用途：最短距離，最短経路，到達可能判定，複数始点BFS
//
// 【DFSとの使い分け】
// ・各辺の移動コストが同じときの最短距離・最短経路 → BFS
// ・到達できるか，どれか1経路でよい               → DFS
//
// 【重要】
// ・dist[r][c] == -1 を未訪問とする．
// ・queueへ追加する時点でdistを更新する．
// ・front()を参照で受けてからpopしない．
//     auto [r, c] = que.front();
//     que.pop();
// ・状態が(r,c)だけでない場合は，distにも状態を追加する．
//   例：(r,c,dir) → dist[r][c][dir]
//
// 計算量：O(HW)（各マスを高々1回訪問する場合）
//
// ============================================================

// ============================================================
// 【実戦用】最短距離＋最短経路
//
// '#'：壁
// 'S'：始点
// 'G'：ゴール
//
// dist[r][c]：始点からの最短距離
// prev_dir[r][c]：そのマスへ移動するときに使った方向
//
// ゴールまで到達できれば，最短経路をansに保存する．
// ============================================================
#if 0

// 4方向：右，上，左，下
constexpr array DIR4 = {
    pair{0, 1}, pair{-1, 0}, pair{0, -1}, pair{1, 0}
};
constexpr string DIR_CHAR = "RULD";

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> S(h);
    for (auto& s : S) cin >> s;

    int sr = -1, sc = -1;
    int gr = -1, gc = -1;
    for (int r=0; r<h; r++) {
        for (int c=0; c<w; c++) {
            if (S[r][c] == 'S') sr = r, sc = c;
            if (S[r][c] == 'G') gr = r, gc = c;
        }
    }

    vector dist(h, vector(w, -1));          // -1で未到達
    vector prev_dir(h, vector<int>(w, -1)); // その地点に到達したときの移動方向
    queue<pair<int,int>> que;
    dist[sr][sc] = 0;
    que.push({sr, sc});

    while (!que.empty()) {
        auto [r, c] = que.front();  // FIFO．参照
        que.pop();                  // 取り出し
        for (int dir=0; dir<4; dir++) {
            auto [dr, dc] = DIR4[dir];
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || h <= nr || nc < 0 || w <= nc) continue;
            if (S[nr][nc] == '#') continue;     // 問題ごとの移動不可条件
            if (dist[nr][nc] != -1) continue;   // 訪問済み

            dist[nr][nc] = dist[r][c] + 1;
            prev_dir[nr][nc] = dir;
            que.push({nr, nc});
        }
    }
    if (dist[gr][gc] == -1) {   // ゴールが見つからないとき
        cout << "No\n";
        return 0;
    }

    // ゴール → 始点へ逆向きに最短経路を復元
    string ans;
    int r = gr, c = gc;
    while (r != sr || c != sc) {
        int dir = prev_dir[r][c];
        ans.push_back(DIR_CHAR[dir]);
        auto [dr, dc] = DIR4[dir];
        r -= dr;
        c -= dc;
    }
    ranges::reverse(ans);
    cout << "Yes\n";
    cout << dist[gr][gc] << '\n';
    cout << ans << '\n';
    return 0;
}

#endif


// ============================================================
// 【学習用】始点から各マスへの最短距離
// ============================================================
#if 1

// 4方向：右，上，左，下
constexpr array DIR4 = {
    pair{0, 1}, pair{-1, 0}, pair{0, -1}, pair{1, 0}
};

// 8方向：右，右上，上，左上，左，左下，下，右下
constexpr array DIR8 = {
    pair{0, 1}, pair{-1, 1}, pair{-1, 0}, pair{-1, -1},
    pair{0, -1}, pair{1, -1}, pair{1, 0}, pair{1, 1}
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<string> S{
        ".....",
        ".###.",
        "...#.",
        ".#...",
        "....."
    };

    int h = ssize(S), w = ssize(S[0]);
    int sr = 0, sc = 0;

    vector dist(h, vector(w, -1));
    queue<pair<int,int>> que;

    dist[sr][sc] = 0;
    que.push({sr, sc});

    while (!que.empty()) {
        auto [r, c] = que.front();      // コピーしてからpop
        que.pop();

        for (auto [dr, dc] : DIR4) {
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || h <= nr || nc < 0 || w <= nc) continue;
            if (S[nr][nc] == '#') continue;
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[r][c] + 1;
            que.push({nr, nc});
        }
    }

    cout << "===== グリッド =====\n";
    for (auto& s : S) cout << s << '\n';

    cout << "\n===== 始点からの最短距離 =====\n";
    for (int r=0; r<h; r++) {
        for (int c=0; c<w; c++) {
            if (S[r][c] == '#') cout << " ##";
            else                cout << setw(3) << dist[r][c];
        }
        cout << '\n';
    }
    return 0;
}

#endif


// ============================================================
// 補足
// ============================================================
// 【queueへ追加するタイミングで訪問済みにする】
//
// dist[nr][nc] = dist[r][c] + 1;
// que.push({nr, nc});
//
// queueから取り出した時点でdistを更新すると，
// 同じマスが複数回queueへ入る場合がある．
//
// ============================================================
// 【front()とpop()】
//
// NG：front()を参照で受けてからpopすると参照が無効になる．
//
// auto& [r, c] = que.front();
// que.pop();
//
// OK：コピーしてからpopする．
//
// auto [r, c] = que.front();
// que.pop();
//
// ============================================================
// 【最短経路の復元】
//
// 各マスについて「どの方向から来たか」を保存する．
//
// prev_dir[nr][nc] = dir;
//
// ゴールから
//
// auto [dr, dc] = DIR4[dir];
// r -= dr;
// c -= dc;
//
// と逆向きにたどる．
//
// BFSでは最初に到達したときの経路が最短経路になる．
//
// ============================================================
// 【複数始点BFS】
//
// 複数の始点をすべて距離0として最初にqueueへ入れる．
//
// for (...) {
//     dist[r][c] = 0;
//     que.push({r, c});
// }
//
// その後のBFSは通常と同じ．
//
// 各マスのdistは「最も近い始点からの距離」になる．
//
// ============================================================
// 【状態が位置だけでない場合】
//
// 例えば，
//   (r, c, dir)
// が1状態なら，distも3次元にする．
//
// vector<vector<array<int, 4>>> dist;
//
// dist[r][c][dir]
//
// 同じマスでもdirが異なれば別状態として探索する．
//
// 未訪問を-1とする場合は，各要素を{-1,-1,-1,-1}で初期化する．
//
// ============================================================
// 【到達可能判定】
//
// BFS終了後，
//
// dist[gr][gc] != -1
//
// ならゴールへ到達可能．
//
// 最短距離が不要でも，BFSで到達可能判定をして問題ない．
//
// ============================================================
// 【到達可能なマス数】
//
// BFS終了後，dist[r][c] != -1 のマスを数えればよい．
//
// int cnt = 0;
// for (int r=0; r<h; r++) {
//     for (int c=0; c<w; c++) {
//         if (dist[r][c] != -1) cnt++;
//     }
// }
//
// ============================================================
// 【8近傍】
//
// constexpr array DIR8 = {
//     pair{0, 1}, pair{-1, 1}, pair{-1, 0}, pair{-1, -1},
//     pair{0, -1}, pair{1, -1}, pair{1, 0}, pair{1, 1}
// };
//
// DIR4をDIR8へ変更すればよい．
//
// ============================================================