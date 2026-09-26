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

int i,j,k,n,t;
int a[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
LL cnt[maxn];
LL now[1<<19|7],pre[1<<19|7];
int main(){
//	REP(i,19) printf("%d ",a[i]);puts("");
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&t),cnt[t]++;
	now[0]=1;
	FOR(i,2,70){
		int t=0,x=i;
		rREP(j,19){
			while (x%(a[j]*a[j])==0) x/=a[j]*a[j];
			if (x%a[j]==0) t|=1<<j;
		}if (!cnt[i]) continue;
		REP(j,(1<<19)) pre[j]=now[j],now[j]=0;
		LL noww=powMM(2ll,cnt[i]-1);
		REP(j,(1<<19)){
			(now[j^t]+=pre[j]*noww)%=M;
			(now[j]+=pre[j]*noww)%=M;
		}
	}
	now[0]=now[0]*powMM(2ll,cnt[1])%M;
	printf("%I64d",(now[0]+M-1)%M);
}
/*
*/
