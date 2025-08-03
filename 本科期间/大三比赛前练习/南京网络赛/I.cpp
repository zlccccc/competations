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
const LL maxn=2e6+7;
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

int ans;
int pw10[maxn];
struct Ptree {
	int next[maxn][10];//空间可优化
	int fail[maxn];
	// cnt:这个所代表的字符串个数(下到上所有),num:上到下的length
	int len[maxn],val[maxn];
	int S[maxn];
	int last,n,tot;
	int newnode(int l) {
		memset(next[tot],0,sizeof(next[tot]));
		len[tot]=l;//不是1...
		return tot++;
	}
	void init() {
		tot=0; last=n=0;
		newnode(0); newnode(-1);
		S[n]=-1; fail[0]=1;
	}
	int getfail(int x) {
		while (S[n-len[x]-1]!=S[n]) x=fail[x];
		return x;
	}
	void add(int c) {
		S[++n]=c;
		int cur=getfail(last);
		if (!next[cur][c]) {
			int now=newnode(len[cur]+2);
			fail[now]=next[getfail(fail[cur])][c];
			next[cur][c]=now;//这里一定要在fail后边=_=
			if (len[now]==1) val[now]=c;
			else val[now]=((ll)val[cur]*10+(ll)(pw10[len[now]-1]+1)*c)%M;
			add_(ans,val[now]);
			// printf("%d \n",val[now]);
		} last=next[cur][c];
	}
} T;
int main() {
	scanf("%s",str);
	int len=strlen(str),i;
	pw10[0]=1;
	FOR(i,1,len) pw10[i]=(ll)pw10[i-1]*10%M;
	T.init();
	REP(i,len) T.add(str[i]-'0');
	printf("%d\n",ans);
}
/*
*/
