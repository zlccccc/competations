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
#define rep(I,pos,N) for (I=pos;I<N;I++)
#define rrep(I,pos,N) for (I=N-1;I>=pos;I--)
#define FOR(I,pos,N) for (I=pos;I<=N;I++)
#define rFOR(I,pos,N) for (I=N;I>=pos;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

#define x x_x
#define y y_y
LL n,m;
LL x,y,q,ans;
LL mx,now;
LL mx1,mx2,mx3,mx4;
LL i,j,k;
int main(){
	scanf("%I64d%I64d",&n,&m);
	scanf("%I64d",&q);
	mx1=mx2=mx3=mx4=-INFF;
	REP(i,q){
		scanf("%I64d%I64d",&x,&y);
		mx1=max(mx1,x+y);
		mx2=max(mx2,x-y);
		mx3=max(mx3,-x+y);
		mx4=max(mx4,-x-y);
	}
	scanf("%I64d",&q);
	mx=INFF;
	FOR(i,1,q){
		scanf("%I64d%I64d",&x,&y);
		now=max(max(mx1-x-y,mx2-x+y),max(mx3+x-y,mx4+x+y));
		if (now<mx){
			mx=now;
			ans=i;
		}
	}
	printf("%I64d\n",mx);
	printf("%I64d",ans);
}
/*
*/
