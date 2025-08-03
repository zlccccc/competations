#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define drep(i, a, b) for (int i = a; i >= b; i--)
#define xx first
#define yy second
#define mp make_pair
#define pb push_back
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
//*******************************************************

const int maxn = 1005;
pii data[maxn];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		rep(i, 1, n) {
			scanf("%d%d", &data[i].xx, &data[i].yy);
		}
		sort(data + 1, data + 1 + n);

		n /= 2;

		int lim = 1e8;
		if (data[n].xx!=data[n+1].xx) {
			printf("%d %d ", data[n].xx, lim + data[n].yy + data[n + 1].yy);
			printf("%d %d\n", data[n+1].xx, -lim);
		} else {
			printf("%d %d ", data[n].xx-1, lim + data[n].yy + data[n + 1].yy);
			printf("%d %d\n", data[n+1].xx + 1, -lim);
		}
	}
}