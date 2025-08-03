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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,ll B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b,ll MOD=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%MOD)
		if (b&1) ret=(LL)ret*a%MOD;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int C[10];
int VAL[]={0,0,0,0,0,0,
			10000,36,720,360,80,
			252,108,72,54,180,72,
			180,119,36,360,1080,
			144,1800,3600};
double ans[10];
void add_ans(){
	ans[1]+=VAL[C[1]+C[2]+C[3]];
	ans[2]+=VAL[C[4]+C[5]+C[6]];
	ans[3]+=VAL[C[7]+C[8]+C[9]];
	ans[4]+=VAL[C[1]+C[4]+C[7]];
	ans[5]+=VAL[C[2]+C[5]+C[8]];
	ans[6]+=VAL[C[3]+C[6]+C[9]];
	ans[7]+=VAL[C[1]+C[5]+C[9]];
	ans[8]+=VAL[C[3]+C[5]+C[7]];
}
bool mark[10];
double fac[10];
double Ans;
void DFS(int i){
	int j;
	for (;i<=9;i++) if (str[i]=='#'){
		FOR(j,1,9) if (!mark[j]){
			C[i]=j; mark[j]=1;
			DFS(i+1);
			C[i]=0; mark[j]=0;
		} return;
	} add_ans();
	// FOR(i,1,9) printf("%d ",C[i]);puts(" <- dfs2");
}
int cnt1,cnt2;
void dfs(int i){
	int j;
	for (;i<=9;i++) if (str[i]=='*'){
		FOR(j,1,9) if (!mark[j]){
			C[i]=j; mark[j]=1;
			dfs(i+1);
			C[i]=0; mark[j]=0;
		} return;
	} DFS(1); double now=0;
	FOR(i,1,8) max_(now,ans[i]);
	add_(Ans,now);
	FOR(i,1,8) ans[i]=0;
}
double _C(int n,int m){
	return fac[n]/fac[m]/fac[n-m];
}
int main() {
	fac[0]=1; int i,T;
	FOR(i,1,9) fac[i]=fac[i-1]*i;
	scanf("%d",&T);
	while (T--){
		scanf("%s%s%s",str+1,str+4,str+7);
		cnt1=cnt2=0;
		FOR(i,1,9) mark[i]=0;
		FOR(i,1,9) {
			if (str[i]=='*') cnt1++;
			else if (str[i]=='#') cnt2++;
			else mark[str[i]-'0']=1,C[i]=str[i]-'0';
		} Ans=0; dfs(1);
		printf("%.10f\n",Ans/fac[cnt1+cnt2]);
	}
}
/*
*/
