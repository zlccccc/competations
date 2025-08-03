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

struct SAM {
	int next[maxn][26],fail[maxn],len[maxn];
	int cnt,last,CNT[maxn];
	void init() {
		cnt=last=0; fail[0]=-1; len[0]=0;
		memset(next[0],0,sizeof(next[0]));
	}
	void add(int c) {
		int np=++cnt,p=last;
		memset(next[np],0,sizeof(next[np]));
		len[np]=len[p]+1;
		for (; p!=-1&&!next[p][c]; p=fail[p]) next[p][c]=np;
		if (p==-1) fail[np]=0;
		else {
			int q=next[p][c];
			if (len[p]+1==len[q]) fail[np]=q;
			else {
				int nq=++cnt; len[nq]=len[p]+1;
				memcpy(next[nq],next[q],sizeof(next[q]));
				fail[nq]=fail[q];
				fail[np]=fail[q]=nq;
				for (; p!=-1&&next[p][c]==q; p=fail[p]) next[p][c]=nq;
			}
		}
		last=np; CNT[last]=1;
	}
	int S[maxn],K[maxn];
	ll solve(int a,int b) {
		ll ans=0; int i;
		FOR(i,1,cnt) S[len[i]]++;
		FOR(i,1,cnt) S[i]+=S[i-1];
		FOR(i,1,cnt) K[S[len[i]]--]=i;
		rFOR(i,1,cnt) CNT[fail[K[i]]]+=CNT[K[i]];
		// FOR(i,1,cnt) printf("%d ",K[i]);puts("");
		FOR(i,1,cnt) if (a<=CNT[i]&&CNT[i]<=b) ans+=len[i]-len[fail[i]];
		FOR(i,1,cnt) CNT[i]=S[i]=0;
		return ans;
	}
	char a[maxn];
	void dfs(int x=0,int len=0) {
		int i;
		printf("%-3d(fail:%-3d,len=%-2d cnt=%-2d):%s\n",x,fail[x],this->len[x],CNT[x],a);
		REP(i,26) {
			if (next[x][i]) {
				a[len]=i+'a';
				dfs(next[x][i],len+1);
				a[len]=0;
			}
		}
	}
} sam;
int main() {
	int a,b;
	while (~scanf("%s%d%d",str,&a,&b)) {
		int len=strlen(str),i; sam.init();
		REP(i,len) sam.add(str[i]-'A');
		// sam.dfs();
		printf("%lld\n",sam.solve(a,b));
		// sam.dfs();
	}
}
/*
*/
