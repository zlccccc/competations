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
const LL maxn=3e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct matrix{
	LL A[2][2];
	matrix(LL a00=1,LL a01=0,LL a10=0,LL a11=1){
		A[0][0]=a00;A[0][1]=a01;
		A[1][0]=a10;A[1][1]=a11;
	}
}MUL,ST;
matrix mul(matrix x,matrix y){
	matrix ret;
	int i,j;
	REP(i,2)
		REP(j,2) ret.A[i][j]=(x.A[i][0]*y.A[0][j]+x.A[i][1]*y.A[1][j])%M;
	return ret;
}
matrix poww(matrix a,LL b){
	matrix ret;
	for (;b;b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
}
void solve(){
	LL q,p,k;
	scanf("%lld%lld%lld",&p,&q,&k);
	MUL.A[0][0]=(p-q)*powMM(p,M-2)%M;
	MUL.A[0][1]=q*powMM(p,M-2)%M;
	MUL.A[1][0]=q*powMM(p,M-2)%M;
	MUL.A[1][1]=(p-q)*powMM(p,M-2)%M;
	ST=matrix(0,1,0,0);
	printf("%lld\n",mul(ST,poww(MUL,k)).A[0][1]);
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
