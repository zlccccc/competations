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
const LL maxn=1e7+107;
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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];

int more,cnt=0;
int A[maxn];
int ask(int A,int B){
	int ret=0;
	if (more==-1) swap(A,B);
	printf("? %d %d\n",A,B);
	fflush(stdout);
	scanf("%d",&ret);
	if (more==-1) ret=-ret;
	cnt++;
	return ret;
}
int main() {
	int i;
	int A=0,B=0;
	more=ask(0,0);
	rREP(i,30){
		int now=1<<i;
		if (more==0) {//a=b
			int mask=ask(A^now,B);
			if (mask==-1) A^=now,B^=now;
		} else {//a>b
			int nxtmore=more;
			if (more==-1) swap(A,B);
			int mask=ask(A^now,B);
			if (mask==1) {
				mask=ask(A^now,B^now);
				if (mask==1) {}//0 0 more不变
				else {A^=now;}//1 0 more不变
			} else if (mask==0){//1 0 more=0
				A^=now; nxtmore=0;
			} else if (mask==-1){
				mask=ask(A^now,B^now);
				if (mask==1){A^=now; B^=now;}//1 1 more不变
				else {A^=now; nxtmore=-more;}//1 0more变
			} if (more==-1) swap(A,B);
			more=nxtmore;
		}
	} printf("! %d %d\n",A,B);
	// printf("%d\n",cnt);
}
/*
*/