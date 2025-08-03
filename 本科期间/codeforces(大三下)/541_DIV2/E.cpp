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
const LL maxn=4e5+107;
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
char pool[maxn],*st=pool;

char *str[maxn];
int ans;
struct node{
	char lc,rc; bool same;
	int l_len,r_len;
	node(char c){
		same=1; lc=rc=c;
		l_len=r_len=1;
		ans=max(ans,1);
	}
	node(){};//只有merge使用
};
node merge(node A,node B) {
	if (A.rc==B.lc) ans=max(ans,A.r_len+B.l_len);
	node ret;
	ret.lc=A.lc; ret.rc=B.rc;
	ret.same=(A.lc==B.rc)&&(A.same&&B.same);
	ret.l_len=A.l_len; ret.r_len=B.r_len;
	if (A.same&&A.lc==B.lc) ret.l_len=A.l_len+B.l_len;
	if (B.same&&A.rc==B.rc) ret.r_len=A.r_len+B.r_len;
	return ret;
}
//倒着merge即可
int main() {
	int i,j;
	node now;
	scanf("%d",&n);
	FOR(i,1,n) {
		str[i]=st;
		scanf("%s",st); int len=strlen(st);
		st+=len+1;
	}
	rFOR(i,1,n) {
		node tmp; int len=strlen(str[i]);
		if (i==n) tmp=node(str[i][0]);
		else tmp=merge(merge(now,node(str[i][0])),now);
		rep(j,1,len) {
			tmp=merge(tmp,node(str[i][j]));
			if (i!=n) tmp=merge(tmp,now);
		} now=tmp;
		// printf("%c %c: %d %d, %d\n",now.lc,now.rc,now.l_len,now.r_len,now.same);
	} printf("%d\n",ans);
}
/*
2
aa
aa

2
bnn
a

2
a
nnn
*/