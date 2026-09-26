#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <tuple>
#include <queue>
#include <set>
using namespace std;

#define ff first
#define ss second
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

void solve() {
	int n, al;
	cin >> n >> al;
	--al;
	const int maxc = 1000000;
	vector<int> clr(maxc, 0);
	vector<char> good(maxc, true);
	good[al] = false;
	for (int i = 0; i < n; ++i) {
		int c; cin >> c; --c;
		if (clr[c] < clr[al]) {
			good[c] = false;
		}
		clr[c] += 1;
	}
	for (int i = 0; i < maxc; ++i) {
		if (clr[i] >= clr[al] && good[i]) {
			cout << i + 1 << endl;
			return;
		}
	}
	cout << -1 << endl;
}

int main() {
#ifdef _DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	//int t; cin >> t; for (int i = 0; i < t; ++i)
	solve();
	return 0;
}
