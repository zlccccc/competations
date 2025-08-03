#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UI;
const LL maxn=5e5+7;
const LL M=998244353;
const LL INF=0x3f3f3f3fll;
const ULL INFF=0x3f3f3f3f3f3f3f3full;
const double eps=0.000001;
inline void read(ULL &x){
    x=0;char p=getchar();
    while(!(p<='9'&&p>='0'))p=getchar();
    while(p<='9'&&p>='0')x*=10,x+=p-48,p=getchar();
}
//http://acm.hdu.edu.cn/showproblem.php?pid=6057 
//很容易卡T...3^18也许能过 //这个比2^nlog^2(n=19)的慢了快5倍 
int T;
int n;
ULL A[1<<19|7],B[1<<19|7],C[1<<22|7];
ULL *X,*Y,*Z;
ULL ans,mul;
int S[27];//stack
int top,len;
int main()
{
	int i;
	scanf("%d",&n);len=1<<n;
	REP(i,len) read(A[i]);
	REP(i,len) read(B[i]);
	X=A;Y=B;Z=C;
	S[++top]=0;
	while (top){
//		if (S[top]==0) printf("  %d %d %d %d %d\n",X-A,Y-B,Z-C,len,top);
		if (S[top]==0){
			if (len==2&&!S[top]) {
				Z[1]=X[0]*Y[1];
				Z[0]=2*X[1]*Y[1]+X[0]*Y[0];
				top--;
			}else{
				Z+=len;len>>=1;S[top]++;
				top++;
			}
		}else if (S[top]==1){
//			printf("1:%d %d %d %d %d\n",X-A,Y-B,Z-C,len,top);
			Y+=len;Z+=len;S[top]++;
			top++;
		}else if (S[top]==2){
//			printf("2:%d %d %d %d %d\n",X-A,Y-B,Z-C,len,top);
			X+=len;Z+=len;S[top]++;
			top++;
		}else if (S[top]==3){
//			printf("3:%d %d %d %d %d\n",X-A,Y-B,Z-C,len,top);
			X-=len;Y-=len;Z-=len+len;
			REP(i,len){
				Z[i-len]=Z[i+len];
				(Z[i-len-len]=Z[i+len+len]*2+Z[i])>INFF&&(Z[i-len-len]%=M);
			}
			len<<=1;
			Z-=len;S[top--]=0;
		}
	}
	mul=1;
	REP(i,(1<<n)){
//		printf("%d ",C[i]);
		C[i]%=M; 
		ans+=1ll*mul*C[i]%M;
		while (ans>M) ans-=M;
		mul=1526ll*mul%M;
	}
	printf("%d\n",ans);
	return 0;
}
/*
2
1 2 3 4
5 6 7 8
*/
