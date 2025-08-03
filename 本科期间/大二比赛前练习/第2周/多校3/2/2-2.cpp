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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

inline void read(int &x){
    x=0;char p=getchar();
    while(!(p<='9'&&p>='0'))p=getchar();
    while(p<='9'&&p>='0')x*=10,x+=p-48,p=getchar();
}
inline void UPD(int &x,int y){x+=y;if (x>M) x-=M;}
void fwt(int *A,int len,int inv) {
	int i,j,k;
	int div=powMM(2ll,M-2);
	for(i=2;i<=len;i<<=1){
		for(j=0;j<len;j+=i){
			for(k=j;k<j+i/2;k++){
				if (inv==1){
					LL a=A[k],b=A[k+i/2];
					A[k]=(a+b)%M;
					A[k+i/2]=(a-b+M)%M;
				}else{
					LL a=A[k],b=A[k+i/2];
					A[k]=(a+b)*div%M;
					A[k+i/2]=(a-b+M)%M*div%M;
				}
			}
		}
	}
}
int T;
int n;
int cnt[1<<19|7];
int A[1<<19|7],B[1<<19|7];
int a[20][1<<19|7],b[20][1<<19|7],c[20][1<<20|7];
int d[27];
int ans,mul;
int main()
{
	int i,j,k;
	scanf("%d",&n);
	REP(i,(1<<n)) read(A[i]);
	REP(i,(1<<n)) read(B[i]);
	REP(i,(1<<n)) cnt[i]=cnt[i>>1]+(i&1);
	REP(i,(1<<n)) a[cnt[i]][i]=A[i]*(1ll<<cnt[i])%M,b[cnt[i]][i]=B[i];
	REP(i,n+1) fwt(a[i],1<<n,1),fwt(b[i],1<<n,1);
//	REP(i,(1<<n)) printf("%d:%d\n",i,cnt[i]);
	REP(i,(1<<n)){
		REP(j,n+1) d[j]=0;
		REP(j,n+1) REP(k,j+1) d[j-k]=(d[j-k]+1ll*b[j][i]*a[k][i])%M;
		REP(j,n+1) c[j][i]=d[j];
	}
	REP(i,n+1) fwt(c[i],1<<n,0);
	mul=1;
//	REP(i,(1<<n)) printf("%d ",c[cnt[i]][i]);puts("");
	REP(i,(1<<n)) ans=(ans+1ll*mul*c[cnt[i]][i])%M,mul=1526ll*mul%M;
	printf("%d\n",ans);
	return 0;
}
/*
2
1 2 3 4
5 6 7 8
*/
