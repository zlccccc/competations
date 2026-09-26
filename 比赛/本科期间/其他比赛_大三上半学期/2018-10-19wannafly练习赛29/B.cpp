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

int A[4][4],ans;
pii l[4][2],r[4][2];
int c[4];
pii fl[4][2],fr[4][2];
int fc[4];
int main() {
	scanf("%d",&n); int i,j,k;
	FOR(i,1,n) {
		REP(j,4) REP(k,4) scanf("%1d",&A[j][k]);
		REP(j,4) {
			REP(k,4) if (!A[j][k]) break;
			if (k==4) c[j]+=k;
			else {
				if (r[j][1]<make_pair(k,j)) r[j][1]=make_pair(k,j);
				if (r[j][0]<r[j][1]) swap(r[j][0],r[j][1]);
				REP(k,4) if (!A[j][3-k]) break;
				if (l[j][1]<make_pair(k,j)) l[j][1]=make_pair(k,j);
				if (l[j][0]<l[j][1]) swap(l[j][0],l[j][1]);
			}
		}
		REP(j,4) {
			REP(k,4) if (!A[k][j]) break;
			if (k==4) fc[j]+=k;
			else {
				if (fr[j][1]<make_pair(k,j)) fr[j][1]=make_pair(k,j);
				if (fr[j][0]<fr[j][1]) swap(fr[j][0],fr[j][1]);
				REP(k,4) if (!A[3-k][j]) break;
				if (fl[j][1]<make_pair(k,j)) fl[j][1]=make_pair(k,j);
				if (fl[j][0]<fl[j][1]) swap(fl[j][0],fl[j][1]);
			}
		}
	}
	int ans=0;
	REP(j,4) {
		int s=max(l[j][0].first+r[j][1].first,l[j][1].first+r[j][0].first);
		if (l[j][0].second!=r[j][0].second) s=max(s,l[j][0].first+r[j][0].first);
		max_(ans,s+c[j]);
		s=max(fl[j][0].first+fr[j][1].first,fl[j][1].first+fr[j][0].first);
		if (fl[j][0].second!=fr[j][0].second) s=max(s,fl[j][0].first+fr[j][0].first);
		max_(ans,s+fc[j]);
	}
	// REP(j,4) printf("%d: %d %d %d\n",j,l[j],r[j],c[j]);
	// REP(j,4) printf("%d: %d %d %d\n",j,fl[j],fr[j],fc[j]);
	printf("%d\n",ans);
}
/*
1
1001
0000
0000
1001
*/
