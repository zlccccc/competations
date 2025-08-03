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
const LL maxn=1e4+107;
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

struct SAM {
	int next[maxn][26],fail[maxn],len[maxn];
	int cnt,last;
	void init() {
		cnt=last=0; fail[0]=-1; len[0]=0;
		memset(next[0],0,sizeof(next[0]));
	}
	void add(int c) {
		int np=++cnt,p=last; c-='a';
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
	int solve(char s[]){//length
		int len=strlen(s),p=0,i;
		REP(i,len) {
			if (!next[p][s[i]-'a']) return i-1;
			else p=next[p][s[i]-'a'];
		} return len-1;
	}
	void print() {
		int i;
		FOR(i,1,cnt) {
		}
	}
	char a[maxn];
	void dfs(int x=0,int len=0) {
		int i;
		puts("");
		printf("%-3d(fail:%-3d,len=%-2d):%s\n",x,fail[x],this->len[x],a);
		REP(i,26) {
			if (next[x][i]) {
				a[len]=i+'a';
				dfs(next[x][i],len+1);
				a[len]=0;
			}
		}
	}
} sam;
int l[maxn];//a->b: substring of x
ll ans[maxn];
char str[maxn];
int main() {
	int i,j; sam.init();
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	scanf("%s",str+1);
	FOR(i,1,n) {
		l[i]=sam.solve(str+i);//start from this
		// printf("%d : %d\n",i,l[i]);
		sam.add(str[i]);
	} FOR(i,1,n) {
		ans[i]=ans[i-1]+a;
		FOR(j,1,i-1) if (j+1+l[j+1]>=i){//j+1->i
			ans[i]=min(ans[i],ans[j]+b);
		}
	} printf("%lld\n",ans[n]);
}
/*
*/