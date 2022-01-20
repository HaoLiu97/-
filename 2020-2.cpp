#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define x first
#define y second

typedef pair<int, int> PII;

const int N = 1010;
int a[N][N], a_origin[N][N];
int n, m;
vector<PII> s_row[N], s_col[N];
int row_cnt[N], col_cnt[N];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            if (a[i][j] != 0) {
                if (s_row[i].size() < 2)s_row[i].emplace_back(j, a[i][j]);
                if (s_col[j].size() < 2)s_col[j].emplace_back(i, a[i][j]);
                row_cnt[i]++, col_cnt[j]++;
            }
        }
    }

    memcpy(a_origin, a, sizeof a);

    int T = 2;
    while (T--) {
        for (int i = 1; i <= n; ++i) {
            if (s_row[i].size() >= 2 && row_cnt[i] < m) {
                auto iter1 = s_row[i][0], iter2 = s_row[i][1];
                int d = (iter2.second - iter1.second) / (iter2.first - iter1.first);
                for (int j = 1; j <= m; ++j) {
                    if (a[i][j] == 0) {
                        a[i][j] = iter1.second + d * (j - iter1.first);
                        if (s_row[i].size() < 2)s_row[i].emplace_back(j, a[i][j]);
                        if (s_col[j].size() < 2)s_col[j].emplace_back(i, a[i][j]);
                        row_cnt[i]++;
                        col_cnt[j]++;
                    }
                }
            }
        }

        for (int i = 1; i <= m; ++i) {
            if (s_col[i].size() >= 2 && col_cnt[i] < n) {
                auto iter1 = s_col[i][0], iter2 = s_col[i][1];
                int d = (iter2.second - iter1.second) / (iter2.first - iter1.first);
                for (int j = 1; j <= n; ++j) {
                    if (a[j][i] == 0) {
                        a[j][i] = iter1.second + d * (j - iter1.first);
                        if (s_row[j].size() < 2)s_row[j].emplace_back(i, a[j][i]);
                        if (s_col[i].size() < 2)s_col[i].emplace_back(j, a[j][i]);
                        row_cnt[j]++;
                        col_cnt[i]++;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] != a_origin[i][j]) {
                printf("%d %d %d\n", i, j, a[i][j]);
            }
        }
    }

    return 0;
}
