#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

LL sval[maxn],snode[maxn];
vector<LL> ans;
int main() {
	int q;
	scanf("%d",&q);
	while (q--){
		int op;LL X;
		scanf("%d%I64d",&op,&X);
		if (op==1){
			LL K;int dep=-1;
			scanf("%I64d",&K);
			while (X) X>>=1,dep++;
			sval[dep]+=K;
			sval[dep]=(sval[dep]%(1ll<<dep)+(1ll<<dep))%(1ll<<dep);
			// dbg(sval[dep]);dbgln(dep);
		}else if (op==2){
			LL K;int dep=-1;
			scanf("%I64d",&K);
			while (X) X>>=1,dep++;
			snode[dep]+=K;
			snode[dep]=(snode[dep]%(1ll<<dep)+(1ll<<dep))%(1ll<<dep);
			// dbg(snode[dep]);dbgln(dep);
		}else{
			int dep=-1;
			for (LL x=X;x;x>>=1) dep++;
			ans.clear();
			while (dep!=-1){
				ans.push_back(X);
				X+=snode[dep]+sval[dep];
				X=(1ll<<dep)+(X%(1ll<<dep)+(1ll<<dep))%(1ll<<dep);
				// dbg(dep);dbg(X);
				X/=2;dep--;
				X-=sval[dep];
				X=(1ll<<dep)+(X%(1ll<<dep)+(1ll<<dep))%(1ll<<dep);
				// dbgln(X);
			}for (auto now:ans) printf("%I64d ",now);puts("");
		}
	}
}
/*
5
3 14
1 5 -3
3 14
1 3 1
3 14
*/
