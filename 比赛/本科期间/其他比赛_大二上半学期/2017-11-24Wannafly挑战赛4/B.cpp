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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k,t;
int a[maxn];
LL val[40][2][2];
LL solve(int x){
	if (x&1) x--;
//	if (x==0) return 0;
	int i,j,k;
	LL ret=0;
	REP(i,32)REP(j,2)REP(k,2) val[i][j][k]=0;
	FOR(i,0,n){
		int seg=i&1;
//		printf("cal:%d,add:%d\n",i,a[i]);
		REP(k,32){
			int mark=(a[i]>>k)&1;
			(ret+=(val[k][seg][mark^1]<<k))%=M;
			val[k][seg][mark]++;
		}
		if (i-x>=0){
//			printf("del:%d,%d\n",i-x,a[i-x]);
			REP(k,32){
				int mark=(a[i-x]>>k)&1;
				val[k][seg][mark]--;
			}
		}
//		printf("ret=%d\n",ret);
	}return ret;
}
int main(){
	int L,R;
	scanf("%d%d%d",&n,&L,&R);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,2,n) a[i]^=a[i-1];
//	FOR(i,1,n) printf("%d ",a[i]);puts("");
//	printf("%lld\n",solve(R));
	printf("%lld\n",(solve(R)-solve(L-1)+M)%M);
}
/*
L-1->R;\sum{XOR} 
*/
