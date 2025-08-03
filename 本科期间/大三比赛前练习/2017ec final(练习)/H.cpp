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
const double eps=1e-15;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[maxn],B[maxn],X,Y;
int pre[maxn][2],suf[maxn][2],pos[4];
int checknotlike(){//could not like
	int i;
	FOR(i,1,n) if (A[i]==2) B[i]=1; else B[i]=A[i];
	pos[0]=pos[1]=0;
	FOR(i,1,n) {
		pos[B[i]]++; pos[B[i]^1]=0;
		if (B[i]==1&&pos[B[i]]>=X) return 1;
		if (B[i]==0&&pos[B[i]]>=Y) return 1;
	} pos[0]=pos[1]=0;
	FOR(i,1,n) if (A[i]==2) B[i]=0; else B[i]=A[i];
	FOR(i,1,n) {
		pos[B[i]]++; pos[B[i]^1]=0;
		if (B[i]==1&&pos[B[i]]>=X) return 1;
		if (B[i]==0&&pos[B[i]]>=Y) return 1;
	}
	return 0;
}
int checklike(){
	int i; pos[0]=pos[1]=0;
	if (X==1) FOR(i,1,n) if (A[i]==2) A[i]=0;
	if (Y==1) FOR(i,1,n) if (A[i]==2) A[i]=1;
	rFOR(i,2,n) {//done
		if (A[i]==1&&X==2&&A[i-1]==2) A[i-1]=0;
		if (A[i]==0&&Y==2&&A[i-1]==2) A[i-1]=1;
	} FOR(i,1,n-1) {//done
		if (A[i]==1&&X==2&&A[i+1]==2) A[i+1]=0;
		if (A[i]==0&&Y==2&&A[i+1]==2) A[i+1]=1;
	}//first_done
	FOR(i,1,n) {
		B[i]=A[i];
		if (A[i]==2) {
			if (X==1) B[i]=0;
			if (Y==1) B[i]=1;
		}
		if (B[i]==2){
			if (pos[1]==X-1) B[i]=0;
			else if (pos[0]==Y-1) B[i]=1;
			else if (A[i+1]==1) B[i]=0;
			else if (A[i+1]==0) B[i]=1;
			else B[i]=B[i-1]^1;//保存现场
			// printf("check %d : %d; len= %d %d\n",i,B[i],pos[0],pos[1]);
		}
		// printf("B=%d  : %d\n",i,B[i]);
		pos[B[i]]++; pos[B[i]^1]=0;
		if (B[i]==1&&pos[B[i]]>=X) return 0;
		if (B[i]==0&&pos[B[i]]>=Y) return 0;
	} return 2;
}
map<char,int> MP;
int main() {
	MP['a']=MP['o']=MP['e']=MP['i']=MP['u']=1; MP['?']=2;//1:fu
	int _t,T; scanf("%d",&T);
	FOR(_t,1,T){
		scanf("%s%d%d",str+1,&X,&Y);
		n=strlen(str+1); int i;
		FOR(i,1,n) A[i]=MP[str[i]];
		int ans=checknotlike()|checklike();
		if (ans==1) printf("Case #%d: DISLIKE\n",_t);
		if (ans==2) printf("Case #%d: LIKE\n",_t);
		if (ans==3) printf("Case #%d: SURPRISE\n",_t);
		// FOR(i,1,n) printf("%d ",A[i]); puts("<- A");
		// FOR(i,1,n) printf("%d ",B[i]); puts("<- B");
		// printf("ans=%d\n",ans);
	}
}
/*
5
?????? 2 2
happybirth?ay 3 5
happybirthd?y 3 5
hellow?rld 3 5
helllllowooorld 3 5
*/
