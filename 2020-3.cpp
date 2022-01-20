#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, M = 8010, C = 810;

int h[N], e[M], ne[M], w[M], idx;
int v[N];
int n, m, q;
int dp[N][C];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dfs(int start, int u, int cur_cost, int value) {
    if (cur_cost > 800) return;
    if(u < start) { // 到达已经处理过的点
        for(int c = 0; cur_cost + c <= 800; ++c) {
            dp[start][cur_cost + c] = max(dp[start][cur_cost + c], value + dp[u][c] - v[u]);
        }
        return;
    }

    dp[start][cur_cost] = max(dp[start][cur_cost], value);

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        dfs(start, j, cur_cost + w[i], value + v[j]);
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &m, &q);
    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &v[i]);
    }

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    for (int i = 1; i <= n; ++i) {
        dfs(i, i, 0, v[i]);
        for (int j = 1; j <= 800; ++j) {
            dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        }
    }

    for (int i = 0; i < q; ++i) {
        int u, c;
        scanf("%d%d", &u, &c);
        printf("%d\n", dp[u][c]);
    }

    return 0;
}
