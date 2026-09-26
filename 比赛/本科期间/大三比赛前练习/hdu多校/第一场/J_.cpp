#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b)	for (int i(a); i <= (b); ++i)
#define dec(i, a, b)	for (int i(a); i >= (b); --i)
#define MP		make_pair
#define fi		first
#define se		second


typedef long long LL;

const int N = 1e6 + 10;
const LL mod = 1e9 + 7;

int L, R;
int T, n, l[2][N], r[2][N], l_back[N], r_back[N];
bool l_br[2][N], r_br[2][N];
char s[N];
LL   ans;
bitset <N> a;

void solve(){

	scanf("%d", &n);
	scanf("%s", s + 1);
	L = n, R = 0;
	rep(i, 1, n){
		a[i] = s[i] - '0';
		if(a[i]) L = min(L, i), R = i;
	}

	if (!R){
		puts("0");
		return;
	}

	dec(i, n + 1, 1){
		if (i > R){ r[0][i] = r[1][i] = 0; continue;}
		r[0][i] = (i < R) + r[!a[i + 1]][i + 1];
		if (a[i + 1] && r[0][i + 1] == 0) r[1][i] = 2;
		else r[1][i] = 3 + r[a[i + 1]][i + 1];
	}

	rep(i, 0, n){
		if (i < L) {l[0][i] = l[1][i] = 0; continue;}
		l[0][i] = (i > L) + l[!a[i - 1]][i - 1];
		if (a[i - 1] && l[0][i - 1] == 0) l[1][i] = 2;
		else l[1][i] = 3 + l[a[i - 1]][i - 1];
	}

	dec(i, n + 1, 1){
		if (i >= R) {r_back[i] = 0, r_br[0][i] = 0, r_br[1][i] = 1; continue;}
		r_back[i] = r_back[i] = 1 + r_back[i + 1] + (r_br[!a[i + 1]][i + 1] ? 3 : 1);
		r_br[0][i] = r_br[!a[i + 1]][i + 1] ? 0 : 1;
		r_br[1][i] = r_br[!a[i + 1]][i + 1] ? 1 : 0;
	}
	
	rep(i, 0, n){
		if (i <= L) {l_back[i] = 0, l_br[0][i] = 0, l_br[1][i] = 1; continue; }
		l_back[i] = 1 + l_back[i - 1] + (l_br[!a[i - 1]][i - 1] ? 3 : 1);
		l_br[0][i] = l_br[!a[i - 1]][i - 1] ? 0 : 1;
		l_br[1][i] = l_br[!a[i - 1]][i - 1] ? 1 : 0;
	}

	rep(i, 1, n) printf("%d ",l_back[i]);puts("");
	ans = 0;
	rep(i, 1, n){
		int x = min(l_back[i] + r[l_br[a[i]][i]][i], r_back[i] + l[r_br[a[i]][i]][i]);
		ans   = (ans + 1ll * i * x % mod) % mod;
		printf("%d ",x);
	}

	printf("%lld\n", ans);
}

int main(){

	scanf("%d", &T);
	while (T--) solve();
	return 0;

}

