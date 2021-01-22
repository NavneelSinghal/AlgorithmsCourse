#include <bits/stdc++.h>
using namespace std;

const int N = 13;

int valid[N][N];

vector<vector<int>> I = {{}, {1}, {2}, {3}, {4}, {5}, {1, 3}, {1, 4}, {1, 5}, {2, 4}, {2, 5}, {3, 5}, {1, 3, 5}};

bool intersect(vector<int> a, vector<int> b) {
    for (auto x : a) for (auto y : b) if (x == y) return true;
    return false;
}

void precompute() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (intersect(I[i], I[j])) {
                valid[i][j] = 0;
            } else {
                valid[i][j] = 1;
            }
        }
    }
}

int max_sum(vector<vector<int>> &a) {
    precompute();
    int n = a.size();
    vector<vector<int>> dp(n + 1, vector<int>(N));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (!valid[j][k]) continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][k]);
            }
            for (auto l : I[j]) {
                dp[i][j] += a[i - 1][l - 1];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        ans = max(ans, dp[n][i]);
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < N; ++j) {
            if (dp[i][j] == 1e9) {
                cout << "$\\infty$";
            } else {
                cout << dp[i][j];
            }
            cout << vector<string>{" & ", "\\\\"}[j == N - 1];
        }
        cout << endl;
    }
    return ans;
}

int ceil2(int x) {
    return (x + 1) / 2;
}

int floor2(int x) {
    return x / 2;
}

int median_clustering(vector<int> &a, int k) {

    int n = a.size();
    vector<int> pre(n + 1);

    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i - 1];
    }

    auto cost = [&] (int i, int j) {
        return pre[j] - pre[ceil2(i + j - 1)] - pre[floor2(i + j - 1)] + pre[i - 1];
    };

    const int INF = 1e9;
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
    for (int i = 1; i <= n; ++i) dp[i][1] = cost(1, i);
    for (int j = 1; j <= k; ++j) dp[0][j] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= k; ++j) {
            for (int ii = 1; ii <= i; ++ii) {
                dp[i][j] = min(dp[i][j], dp[ii - 1][j - 1] + cost(ii, i));
            }
        }
    }

    cout << "\\hline\n";
    cout << "$i \\downarrow, j \\rightarrow$ & ";
    for (int j = 0; j <= k; ++j) cout << j << vector<string>{" & ", " \\\\\n"}[j == k];
    cout << "\\hline\n";
    for (int i = 0; i <= n; ++i) {
        cout << i << " & ";
        for (int j = 0; j <= k; ++j) {
            if (dp[i][j] == 1e9) {
                cout << "$\\infty$";
            } else {
                cout << dp[i][j];
            }
            cout << vector<string>{" & ", " \\\\\n"}[j == k];
        }
        cout << "\\hline\n";
    }
    return dp[n][k];
}

int min_diff(vector<int> &a) {
    int n = a.size();
    int s = 0;
    for (auto x : s) s += x;
    vector<vector<int>> dp(n + 1, s + 1);
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) dp[i][0] = 1;
    for (int j = 1; j <= s; ++j) dp[0][j] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= s; ++j) {
            if (j >= a[i - 1]) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - a[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
}

int main() {
    //vector<vector<int>> a = {{-1, 2, 3, -4, 5}, {2, -5, 3, 5, 6}};
    //cout << max_sum(a) << endl;
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    median_clustering(a, k);
}
