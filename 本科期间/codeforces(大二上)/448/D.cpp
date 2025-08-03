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

int cnt[255],all[255];
LL fac[maxn],inv[maxn];
LL calc(char *c,int len){
	memcpy(cnt,all,sizeof(all));
	LL ret=0;int i,j;
//	FOR(i,'a','z') printf("%d ",cnt[i]);puts("");
	REP(i,len){
		LL now=0;
		rep(j,'a',c[i]){
			now+=cnt[j];
		}FOR(j,'a','z') (now*=inv[cnt[j]])%=M;
		(ret+=now*fac[len-i-1])%=M;
//		printf("%d %d\n",now,ret);
		if (!cnt[c[i]]) break;
		cnt[c[i]]--;
	}return ret;
}
int n;
char a[maxn],b[maxn];
int main(){
	scanf("%s%s",a,b);
	int i;
	n=strlen(a);
	REP(i,n) all[a[i]]++;
	fac[0]=1;
	FOR(i,1,n) fac[i]=fac[i-1]*i%M;
	inv[0]=inv[1]=1;
	FOR(i,2,n) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,2,n) inv[i]=inv[i]*inv[i-1]%M;
//	printf("%I64d\n",calc(b,n));
	printf("%I64d\n",(calc(b,n)-calc(a,n)-1+M)%M);
}
/*
*/
