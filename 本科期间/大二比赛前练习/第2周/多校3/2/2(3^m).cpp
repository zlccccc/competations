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
const LL maxn=5e5+7;
const LL M=998244353;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

inline void read(int &x){
    x=0;char p=getchar();
    while(!(p<='9'&&p>='0'))p=getchar();
    while(p<='9'&&p>='0')x*=10,x+=p-48,p=getchar();
}
int T;
int n;
int A[20][1<<19|7],B[20][1<<19|7],C[20][1<<19|7];
int ans,mul;
inline void UPD(int &x,int y){x+=y;if (x>M) x-=M;}
void solve(int dep,int len){
	int i;
	int *X=A[dep],*Y=B[dep],*Z=C[dep];
	if (len==1) {Z[0]=1ll*X[0]*Y[0]%M;return;}
	int *U=A[dep-1],*V=B[dep-1],*W=C[dep-1];
	memset(Z,0,len*sizeof(int));
	len>>=1;
	memcpy(U,X,len*sizeof(int));
	memcpy(V,Y,len*sizeof(int));
	solve(dep-1,len);
	REP(i,len) UPD(Z[i],W[i]);
	memcpy(V,Y+len,len*sizeof(int));
	solve(dep-1,len);
	REP(i,len) UPD(Z[i+len],W[i]);
	memcpy(U,X+len,len*sizeof(int));
	solve(dep-1,len);
	REP(i,len) UPD(Z[i],W[i]),UPD(Z[i],W[i]);
}
int main()
{
	int i;
	scanf("%d",&n);
	REP(i,(1<<n)) read(A[n][i]);
	REP(i,(1<<n)) read(B[n][i]);
	solve(n,1<<n);
//	REP(i,(1<<n)) printf("%d ",C[n][i]);
	mul=1;
	REP(i,(1<<n)) UPD(ans,1ll*mul*C[n][i]%M),mul=1526ll*mul%M;
	printf("%d\n",ans);
	return 0;
}
/*
2
1 2 3 4
5 6 7 8
*/
