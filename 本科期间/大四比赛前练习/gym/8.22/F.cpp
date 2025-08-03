#include <sstream>
#include <fstream>
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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace Simplex {
	int n,m;//n变量, m式子
	const int maxn=500,maxm=5000;
	double A[maxm][maxn];//
	int id[maxn+maxm];//base
	const double inf=1e20;
	const double eps=1e-7;
	void pivot(int l,int e) {
		int tt=id[n+l]; id[n+l]=id[e]; id[e]=tt;
		int i,j; double t=A[l][e]; A[l][e]=1;
		FOR(j,0,n) A[l][j]/=t;
		FOR(i,0,m) if (i!=l && abs(A[i][e])>eps) {
			t=A[i][e]; A[i][e]=0;
			for (j=0; j<=n; j++)
				A[i][j]-=A[l][j]*t;
		}
	}
	bool initialize() {
		int i,j;
		FOR(i,1,n) id[i]=i;
		while (1) {
			int e=0,l=0;
			FOR(i,1,m) if (A[i][0]<-eps && (!l || (rand()&1))) l=i;
			if (!l) break;
			FOR(j,1,n) if (A[l][j]<-eps && (!e || (rand()&1))) e=j;
			if (!e) return 0;//Infeasible,无解
			pivot(l,e);
		} return 1;
	}
	double ans[maxn],value;
	bool simplex() {
		int i,j;
		while (true) {
			int l=0,e=0; double minn=inf;
			FOR(j,1,n) if (A[0][j]>eps) {e=j; break;}
			if (!e) break;
			FOR(i,1,m) if (A[i][e]>eps && A[i][0]/A[i][e]<minn)
				minn=A[i][0]/A[i][e],l=i;
			if (!l) return 0;//Unbounded,inf
			pivot(l,e);
		}
		FOR(i,1,m) ans[id[n+i]]=A[i][0];
		value=-A[0][0];//maxvalue
		return 1;
	}
}
const int MAX=600;
int A[maxn];
//				0,	1	2	3	4	5	6	7	8	9	10	11	12
int B[2][13]={{	0,	1,	-1,	2,	-1,	2,	0,	3,	0,	-1,	0,	-1,	1},
			{	0,	0,	2,	0,	3,	-1,	1,	-1,	2,	0,	-1,	1,	-1}};
int main(){
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int i,k;
		int a,b; scanf("%d%d",&a,&b);
		FOR(i,1,7) scanf("%d",&A[i]);
		int t; scanf("%d",&t);
		if (t==1) a--; else b--;
		Simplex::m=4;
		Simplex::A[1][0]=a;		Simplex::A[2][0]=b;
		Simplex::A[3][0]=-a;	Simplex::A[4][0]=-b;
		Simplex::n=12;
		Simplex::A[0][1]=A[1];		Simplex::A[0][2]=A[1];
		Simplex::A[0][3]=A[2];		Simplex::A[0][4]=A[2];
		Simplex::A[0][5]=A[3];		Simplex::A[0][6]=A[3];
		Simplex::A[0][7]=A[4];		Simplex::A[0][8]=A[4];
		Simplex::A[0][9]=A[5];		Simplex::A[0][10]=A[6];
		Simplex::A[0][11]=A[7];		Simplex::A[0][12]=A[7];
		FOR(i,1,12) Simplex::A[0][i]=-Simplex::A[0][i];
		REP(i,2) FOR(k,1,12) {
			Simplex::A[i+1][k]=B[i][k];
			Simplex::A[i+3][k]=-B[i][k];
		}
		if (!Simplex::initialize()) puts("no answer");
		if (!Simplex::simplex()) puts("ans inf");
		FOR(i,1,12) printf("%f ",Simplex::ans[i]); puts("<- ans");
		{//check
			Simplex::m=4;
			Simplex::A[1][0]=a;		Simplex::A[2][0]=b;
			Simplex::A[3][0]=-a;	Simplex::A[4][0]=-b;
			Simplex::n=12;
			Simplex::A[0][1]=A[1];		Simplex::A[0][2]=A[1];
			Simplex::A[0][3]=A[2];		Simplex::A[0][4]=A[2];
			Simplex::A[0][5]=A[3];		Simplex::A[0][6]=A[3];
			Simplex::A[0][7]=A[4];		Simplex::A[0][8]=A[4];
			Simplex::A[0][9]=A[5];		Simplex::A[0][10]=A[6];
			Simplex::A[0][11]=A[7];		Simplex::A[0][12]=A[7];
			FOR(i,1,12) Simplex::A[0][i]=-Simplex::A[0][i];
			REP(i,2) FOR(k,1,12) {
				Simplex::A[k][i+1]=B[i][k];
				Simplex::A[k][i+3]=-B[i][k];
			}
			FOR(i,1,4) {
				double all=0;
				FOR(k,1,12) printf("%f ",Simplex::A[k][i]); puts("<- A");
				FOR(k,1,12) all+=Simplex::ans[k]*Simplex::A[k][i];
				printf(" check: %f %f\n",all,Simplex::A[i][0]);
			}
		}
		printf("%f\n",Simplex::value);
	}
}