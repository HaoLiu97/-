#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1000010;

int n, k;
vector<int> vn;
int f[10], mul[10];

int dfs(int u) {
    if(u == vn.size() - 1) {
        return vn[u] >= k;
    }

    int cur = vn[u];
    int ret = 0;

    if(cur < k) {
        ret += cur*f[vn.size()-u-1] + dfs(u+1);
    }

    int t = 0;
    for(int i = u + 1; i < vn.size(); ++i) {
        t = t*10 + vn[i];
    }

    if(cur == k) {
        ret += cur*f[vn.size()-u-1] + dfs(u+1) + t + 1;
    }

    if(cur > k) {
        ret += cur*f[vn.size()-u-1] + dfs(u+1) + mul[vn.size()-u-1];
    }

    return ret;
}

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    int nn = n;
    while(nn != 0) {
        vn.push_back(nn%10);
        nn /= 10;
    }

    reverse(vn.begin(), vn.end());

    int cur = 1;
    mul[0] = 1;
    for(int i = 1; i <= 9; ++i) {
        f[i] = f[i-1]*10 + cur;
        mul[i] = mul[i-1] * 10;
        cur *= 10;
    }

    cout<<dfs(0)<<endl;

    return 0;
}
