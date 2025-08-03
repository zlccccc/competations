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
typedef long long ll;
const ll M=1e9+7;
const ll maxn=1e6+107;
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int k;
inline int lowbit(int x) {return x&-x;}
inline void add_(int &A,int B) {
	A+=B; (A>=M) &&(A-=M);
}
int V[maxn][21],now[21];
inline void add(int x,int val[]) {
	int i;
	for (; x<=1000000; x+=lowbit(x)) REP(i,k+1)
		add_(V[x][i],val[i]);
}
inline void clr(int x) {
	int i;
	for (; x<=1000000; x+=lowbit(x)) REP(i,k+1)
		V[x][i]=0;
}
inline void query(int x,int ret[]) {
	int i; REP(i,k+1) ret[i]=0;
	for (; x; x-=lowbit(x)) REP(i,k+1)
		add_(ret[i],V[x][i]);
}
ll inv[21],fac[21];
ll C(int n,int m) {
	return (ll)fac[n]*inv[m]%M*inv[n-m]%M;
}
int A[maxn];
char str[maxn];
int main() {
	startTimer();
	int i,T,_;
	fac[0]=1;
	FOR(i,1,20) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,20) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,20) inv[i]=inv[i]*inv[i-1]%M;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n;
		scanf("%d%d",&n,&k);
		assert(0<=n&&n<=100000);
		assert(0<=k&&k<=20);
		FOR(i,1,n) {
			int x;
			scanf("%d%d",&A[i],&x);
			assert(1<=A[i]&&A[i]<=1000000);
			assert(0<=x&&x<=1000000000);
			query(A[i]-1,now);
			int a,b;
			rREP(a,k+1) {
				REP(b,a) add_(now[a],now[b]*C(a,b)%M);
				now[a]=((ll)(now[a]+1)*x)%M;
			} add(A[i],now);
		} query(1000000,now);
		printf("%d\n",now[k]);
		FOR(i,1,n) clr(A[i]);
	} assert(scanf("%s",str)==EOF);
	printTimer();
}
/*
10
3 2
4 1
3 2
5 1

3 2
4 1
3 2
5 1

3 10
4 2
3 2
5 1

3 0
4 2
3 2
5 1
*/