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
const LL maxn=1<<20|7;
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

namespace SAM {
	int next[maxn][88],fail[maxn],len[maxn];
	int cnt,last;
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
		last=np;
	}
	void ins(char a[]) {
		int n=strlen(a),i; init();
		REP(i,n) add(a[i]-1);
	}
	int ask(char a[]) {
		int i; int ret=0;
		int n=strlen(a),p=0,l=0;
		REP(i,n) {
			int c=a[i]-1;
			if (next[p][c]) l++,p=next[p][c];
			else {
				while (p!=-1&&!next[p][c]) p=fail[p];
				if (p==-1) p=l=0;
				else l=len[p]+1,p=next[p][c];
			} ret=max(l,ret);
		} return ret;
	}
}
int okay[27][27];
char str[27][40007];
int cnt[maxn],LEN[27];
int _no[27];
int ans=0,_k;
void dfs(int sta,int now) { //从前往后
	int i;
	// printf("sta=%d\n",sta);
	ans=max(ans,cnt[sta]);
	for (;now<n;now++) if (!_no[now]&&LEN[now]>=_k){
		REP(i,n) _no[i]+=!okay[now][i];
		dfs(sta|(1<<now),now+1);
		REP(i,n) _no[i]-=!okay[now][i];
	}
}
int main() {
	int T; T=1;
	// scanf("%d",&T);
	while (T--) {
		int k,i,j;
		scanf("%d%d",&n,&_k);
		REP(i,n) {
			scanf("%d",&m); int t;
			LEN[i]=m;
			REP(k,m) {
				scanf("%d",&t);
				str[i][k]=t;
			}
		} REP(i,n) {
			SAM::ins(str[i]);
			REP(j,n) {
				int l=SAM::ask(str[j]);
				okay[i][j]=l<_k;
				// printf("%d-(%d: %d) : %d  (%d)\n",i,j,len,l,okay[i][j]);
			}
		} cnt[1]=0; ans=0;
		rep(i,1,(1<<20)) cnt[i]=cnt[i>>1]+(i&1);
		dfs(0,0); printf("%d\n",ans);
	}
}
/*
4 3
8
1 1 1 1 2 2 2 2
5
1 1 2 2 3
1
2
2
1 2
*/