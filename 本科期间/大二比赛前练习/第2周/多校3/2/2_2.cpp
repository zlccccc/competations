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
int A[1<<19|7],B[1<<19|7],Z[20][1<<20|7];
int ans,mul;
inline void UPD(int &x,int y){x+=y;if (x>M) x-=M;}
void solve(int *A,int *B,int *C,int dep,int len){
	int i;
	if (len==1) {C[0]=1ll*A[0]*B[0]%M;return;}
	len>>=1;
	int *D=Z[dep-1];
	solve(A,B,D,dep-1,len);
	solve(A,B+len,D+len,dep-1,len);
	solve(A+len,B+len,D+len+len,dep-1,len);
	REP(i,len){
		C[i+len]=D[i+len];
		C[i]=D[i+len+len]*2;
		if (C[i]>M) C[i]-=M;
		C[i]+=D[i];
		if (C[i]>M) C[i]-=M;
	}
}
int main()
{
	int i;
	scanf("%d",&n);
	REP(i,(1<<n)) read(A[i]);
	REP(i,(1<<n)) read(B[i]);
	solve(A,B,Z[n],n,1<<n);
	mul=1;
	REP(i,(1<<n)) UPD(ans,1ll*mul*Z[n][i]%M),mul=1526ll*mul%M;
	printf("%d\n",ans);
	return 0;
}
/*
2
1 2 3 4
5 6 7 8
*/
