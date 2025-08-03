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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const LL INF=0x3f3f3f3fll;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
int a[maxn];
int pre[maxn],suf[maxn];
bool have[maxn];
int tot,TOT;
vector<int> check,del;
void solve(){
	scanf("%d",&n);
	int i,j;
	FOR(i,1,n) scanf("%d",&a[i]);
	a[0]=-INF;a[n+1]=INF;
	FOR(i,1,n) pre[i]=i-1,suf[i]=i+1,check.push_back(i),have[i]=1;
	while (1){
		bool mark=1;
		for (int i:check) if (a[i]<a[pre[i]]||a[suf[i]]<a[i]&&have[i]) del.push_back(i),have[i]=0;
		check.clear();
		if (del.empty()) break;
		for (int i:del){
			suf[pre[i]]=suf[i],pre[suf[i]]=pre[i];
			if (have[pre[i]]) check.push_back(pre[i]);
			if (have[suf[i]]) check.push_back(suf[i]);
		}
		del.clear();
	}
	tot=0;
	FOR(i,1,n) tot+=have[i];
	printf("%d\n",tot);
	FOR(i,1,n) if (have[i]) printf("%d ",a[i]);
	puts("");
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
