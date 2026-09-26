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
const LL maxn=8e5+107;
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


struct SAM {
	int next[maxn][27],fail[maxn],len[maxn];
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
	LL query() {
		ll ret=0; int i;
		FOR(i,1,cnt) ret+=len[i]-len[fail[i]];
		return ret;
	}

	char a[maxn];
	void dfs(int x=0,int len=0) {
		int i;
		// printf("%-20s %-10d %-10d %-10d");
		printf("%-3d(fail:%-3d,len=%-2d):%-30s",x,fail[x],this->len[x],a);
		if (fail[x]) printf("%d",this->len[fail[x]]); puts("");
		REP(i,26) {
			if (next[x][i]) {
				a[len]=i+'a';
				dfs(next[x][i],len+1);
				a[len]=0;
			}
		}
	}
} sam;

struct Ptree {
	int next[maxn][27];//空间可优化
	int fail[maxn];
	// cnt:这个所代表的字符串个数(下到上所有),num:上到下的length
	// int cnt[maxn],num[maxn];
	int len[maxn];//长度
	int diff[maxn];//length(this-fail)
	int slink[maxn];//diff不同的fail,共log个
	// slink用来算sans,sabs转移得到ans //用来求的是分成串的个数
	int S[maxn];//字符
	int last;//上一个字符节点
	int n,tot;//n表示字符位置
	int newnode(int l) {
		memset(next[tot],0,sizeof(next[tot]));
		// cnt[tot]=num[tot]=0;
		len[tot]=l;//不是1...
		return tot++;
	}
	void init() {
		tot=0; last=n=0;
		newnode(0); newnode(-1);
		S[n]=-1;//减少特判
		fail[0]=1;
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
			diff[now]=len[now]-len[fail[now]];
			if (diff[now]==diff[fail[now]])
				slink[now]=slink[fail[now]];
			else slink[now]=fail[now];
			// num[now]=num[fail[now]]+1;
		}
		last=next[cur][c];
		// cnt[last]++;
	}
} ptree;
char str[maxn];
int main() {
	// int T,_; T=1;
	// scanf("%d",&T);
	int i;
	scanf("%s",str);
	int len=strlen(str);
	sam.init(); ptree.init();
	REP(i,len) sam.add(str[i]-'a');
	REP(i,len) ptree.add(str[i]-'a');
	sam.last=0;
	reverse(str,str+len);
	REP(i,len) sam.add(str[i]-'a');
	// sam.dfs();
	// printf("%lld %d\n",sam.query(),ptree.tot-2);
	printf("%lld\n",(sam.query()+ptree.tot-2)/2);
}
/*
abac
*/