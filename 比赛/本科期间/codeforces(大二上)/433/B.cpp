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
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	LL d,f,t,c;
}a[maxn];
bool cmp(node a,node b){
	return a.d<b.d;
}
int n,m,k;
int i;
LL pre[maxn],suf[maxn];
LL now[maxn],all,ans;
int cnt;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	REP(i,m) scanf("%I64d%I64d%I64d%I64d",&a[i].d,&a[i].f,&a[i].t,&a[i].c);
	sort(a,a+m,cmp);
	memset(now,0x3f,sizeof(now));
	memset(pre,0x3f,sizeof(pre));
//	puts("");
//	REP(i,m) printf("%I64d %I64d %I64d %I64d\n",a[i].d,a[i].f,a[i].t,a[i].c);
	all=0;cnt=0;
	REP(i,m){
		if (!a[i].f) continue;
		if (now[a[i].f]==INFF) cnt++,all+=a[i].c;
		else all=all-(now[a[i].f]-min(now[a[i].f],a[i].c));
		now[a[i].f]=min(now[a[i].f],a[i].c);
		if (cnt==n) pre[a[i].d]=min(pre[a[i].d],all);
	}
	FOR(i,1,1000000) pre[i]=min(pre[i],pre[i-1]);
	memset(now,0x3f,sizeof(now));
	memset(suf,0x3f,sizeof(suf));
	all=0;cnt=0;
	rREP(i,m){
		if (!a[i].t) continue;
		if (now[a[i].t]==INFF) cnt++,all+=a[i].c;
		else all=all-(now[a[i].t]-min(now[a[i].t],a[i].c));
		now[a[i].t]=min(now[a[i].t],a[i].c);
//		printf("%d %d %d\n",cnt,all,a[i].t);
		if (cnt==n) suf[a[i].d]=min(suf[a[i].d],all);
	}
	rFOR(i,0,1000000) suf[i]=min(suf[i],suf[i+1]);
	ans=INFF;
	FOR(i,0,1000000) if (i+k+1<=1000000) ans=min(ans,pre[i]+suf[i+k+1]);
//	FOR(i,1,20) printf("%20lld",pre[i]);puts("");
//	FOR(i,1,20) printf("%20lld",suf[i]);puts("");
	if (ans==INFF) puts("-1");
	else printf("%I64d",ans);
}
/*
*/
