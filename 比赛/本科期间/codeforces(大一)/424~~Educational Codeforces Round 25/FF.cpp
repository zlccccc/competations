#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

int cal(int t) {
  int ret = 0;
  while (t > 0) {
    t /= 10;
    ret++;
  }
  return ret;
}

int main(int argc, char *argv[]) {
  string s;
  cin >> s;
  int n = s.size();
  vector<int> dp(n + 1, inf);
  dp[0] = 0;
  for (int i = 1; i <= n; i++) {
    vector<int> fail(i + 1, -1);
    int p = -1;
    for (int j = 0; j < i; j++) {
      while (p != -1 && s[i - 1 - j] != s[i - 1 - p]) p = fail[p];
      fail[j + 1] = ++p;
      dp[i] = min(dp[i], dp[i - j - 1] + j + 2);
      if ((j + 1) % (j + 1 - fail[j + 1]) == 0) {
        int t = (j + 1) / (j + 1 - fail[j + 1]);
        int l = j + 1 - fail[j + 1];
        dp[i] = min(dp[i], dp[i - j - 1] + l + cal(t));
      }
    }
  }
  cout << dp[n] << endl;
  return 0;
}
