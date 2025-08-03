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
const LL INF=0x7f3f3f3fll;
const ULL INFF=0x3f3f3f3f3f3f3f3f;
const double eps=0.000001;
inline void read(ULL &x){
    x=0;char p=getchar();
    while(!(p<='9'&&p>='0'))p=getchar();
    while(p<='9'&&p>='0')x*=10,x+=p-48,p=getchar();
}
//http://acm.hdu.edu.cn/showproblem.php?pid=6057 
//�����׿�T...3^18Ҳ���ܹ� //�����2^nlog^2(n=19)�����˿�5�� 
int T;
int n;
ULL A[1<<19|7],B[1<<19|7];
ULL C[1<<22|7];
ULL ans,mul;
inline void solve(ULL *A,ULL *B,ULL *C,int len){
	int i;
	if (len==2) {C[1]=A[0]*B[1];C[0]=2*A[1]*B[1]+A[0]*B[0];return;}//����Ҫ�� 
//	if (len==1) {C[0]=1ll*A[0]*B[0]%M;return;}
	ULL *D=C+len;
	len>>=1;
	solve(A,B,D,len);//����A��B������Ҫ���,������������������ 
	solve(A,B+len,D+len,len);
	solve(A+len,B+len,D+len+len,len);
	REP(i,len){
		C[i+len]=D[i+len];
		(C[i]=D[i+len+len]*2+D[i])>INFF&&(C[i]%=M);
	}
}
int main()
{
	int i;
	scanf("%d",&n);
	REP(i,(1<<n)) read(A[i]);
	REP(i,(1<<n)) read(B[i]);
	solve(A,B,C,1<<n);
	mul=1;
	REP(i,(1<<n)) {
//		printf("%d ",C[i]);
		C[i]%=M;
		ans+=C[i]*mul;
		if(ans>INFF) ans%=M;
		mul=1526*mul%M;
	}ans%=M;
	printf("%llu\n",ans);
	return 0;
}
/*
*/
