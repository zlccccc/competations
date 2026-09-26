#include <cstdio>
#include <cstring>
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
struct node{
	LL A[2][2];
	node(){
		A[0][0]=1;A[0][1]=0;
		A[1][0]=0;A[1][1]=1;
	}
};
node MUL(node x,node y){
	node ret;
	int i,j;
	REP(i,2)
		REP(j,2)
			ret.A[i][j]=((x.A[i][0]*y.A[0][j]%M+x.A[i][1]*y.A[1][j]%M)%M+M)%M;
	return ret;
}
node powMM(node a,LL b){
    node ret;
    while (b){
        if (b&1) ret=MUL(ret,a);
        a=MUL(a,a);
        b>>=1;
    }
    return ret;
}
LL n,m;
int i,j,k;
int main(){
	int T;
	node A,mul;
	A.A[0][0]=31;A.A[0][1]=197;
	A.A[1][0]=0;A.A[1][1]=0;
	mul.A[0][0]=0;mul.A[0][1]=-4;
	mul.A[1][0]=1;mul.A[1][1]=7;
//	printf("%lld",MUL(A,mul).A[0][0]);
	scanf("%d",&T);
	while (T--){
		scanf("%lld",&n);
		n-=2;
		printf("%lld\n",(MUL(A,powMM(mul,n))).A[0][0]);
	}
}
/*
*/

