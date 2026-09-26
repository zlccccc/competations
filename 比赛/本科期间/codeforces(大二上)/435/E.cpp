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

LL a[maxn],b[maxn];
LL seg[maxn];
LL all[maxn];
LL alla,allb;
LL i;
LL n,m,k;
LL l,r,val,add;
LL cnt,now;
int main(){
	scanf("%I64d%I64d%I64d",&n,&m,&k);
	FOR(i,1,n) scanf("%I64d",&a[i]);
	FOR(i,1,m) scanf("%I64d",&b[i]);
	seg[0]=-1;
	FOR(i,1,m) seg[i]=seg[i-1]*-1;
	FOR(i,1,n) alla+=seg[i]*a[i];
	FOR(i,1,n) allb+=seg[i]*b[i];
	all[cnt++]=alla-allb;
	FOR(i,n+1,m){
		allb=allb-seg[i-n]*b[i-n]+seg[i]*b[i];
		all[cnt++]=alla+seg[i-n]*allb;
	}
	sort(all,all+cnt);
//REP(i,cnt) printf("%d ",all[i]);
	val=0;
	LL pos=lower_bound(all,all+cnt,add)-all;
	LL ans=INFF;
	if (pos!=cnt) ans=min(ans,abs(all[pos]+add));
	if (pos!=0) ans=min(ans,abs(all[pos-1]+add));
	printf("%I64d\n",ans);
	
	add=0;
	FOR(i,1,k){
		scanf("%I64d%I64d%I64d",&l,&r,&val);
		if ((r-l)%2==1) add+=0;
		else if (l&1) add+=val;
		else add-=val;
//		printf("add=%d ",add);
		LL k=lower_bound(all,all+cnt,-add)-all;
		LL ans=INFF;
		if (k!=cnt) ans=min(ans,abs(all[k]+add));
		if (k!=0) ans=min(ans,abs(all[k-1]+add));
		printf("%I64d\n",ans);
	}
}
/*
*/
