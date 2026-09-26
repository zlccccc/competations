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

#define DEBUG1
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
const LL M=998244353;
const LL maxn=2e5+7;
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

int val[maxn][57];
int id[maxn],A[maxn];//id:this_id
vector<pii> queries[maxn];
vector<int> edge[maxn];
int sz[maxn];
bool mark[maxn];
int minweight,root;
void dfs1(int x,int fa,int n) {
	int weight=0; sz[x]=1;
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		dfs1(v,x,n); sz[x]+=sz[v];
		weight=max(weight,sz[v]);
	} weight=max(weight,n-sz[x]);
	if (weight<minweight) root=x,minweight=weight;
}//depth
vector<int> sons; int K;
int ans[maxn];
int now[57];
void dfs2(int x,int fa,int top) {
	int i; sz[x]=1;
	// printf("dfs2: %d\n",x);
	REP(i,K) {
		val[x][i]=val[fa][i];
		add_(val[x][i],val[fa][(i-A[x]+K)%K]);
	} for (pii q:queries[x]) {
		if (id[q.first]==top) {
			//todo: query
			// printf("query: %d\n",q.second);
			REP(i,K) {
				int j=K-i; while (j>=K) j-=K;
				add_(ans[q.second],(ll)val[q.first][i]*val[x][j]%M);
				j=K+K-i-A[top]; while (j>=K) j-=K;
				add_(ans[q.second],(ll)val[q.first][i]*val[x][j]%M);
			}
		}
	} sons.push_back(x);
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		dfs2(v,x,top); sz[x]+=sz[v];
	}
}
void calc(int x) {
	int i; val[x][0]=1; id[x]=x;
	rep(i,1,K) val[x][i]=0;
	for (int v:edge[x]) {
		if (mark[v]) continue;
		dfs2(v,x,x);
		for (int o:sons) id[o]=x;
		sons.clear();
	}
}
void dfs3(int x) {
	debug("dfs3:%d\n",x);
	calc(x); mark[x]=1;
	for (int v:edge[x]) {
		if (mark[v]) continue;
		minweight=sz[v];
		dfs1(v,0,sz[v]);
		dfs3(root);
	}
}

namespace fastIO {//感觉没问题, 测试几次
#define BUF_SIZE 100000
	namespace Istream {
		bool IOerror = 0;
		inline char ic() {
			static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
			if (p1==pend) {
				p1=buf;
				pend=buf+fread(buf,1,BUF_SIZE,stdin);
				if (pend == p1) {IOerror = 1; return -1;}
			} return *p1++;
		}
		inline bool blank(char ch) {
			return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
		}
		template<typename T>
		inline void readPositive(T &x) {//no
			char ch;
			while (blank(ch=ic()));
			if (IOerror) return;
			for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
		}
		template<typename T>
		inline void read(T &x) {
			char ch; T op=1;
			while (blank(ch=ic()));
			if (IOerror) return;
			if (ch=='-') op=-1,ch=ic();
			for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
			x*=op;
		}
		inline void read(char &c) {
			c=ic();
		}
		inline void read(char *s) { //len
			char ch;
			while (blank(ch=ic()));
			if (IOerror) return;
			for (; !blank(ch)&&!IOerror; ch=ic()) *s++=ch;
			*s='\0';
		}
	}
	namespace Ostream {
		char buf[BUF_SIZE], *p1 = buf, *pend = buf + BUF_SIZE;
		inline void flush() {
			fwrite(buf,1,p1-buf,stdout);
			p1=buf;
		}
		inline void oc(char ch) {
			if (p1 == pend) flush();
			*p1++=ch;
		}
		inline void println() {
			oc('\n');
		}
		template<typename T>
		inline void print(T x) {
			static char s[27],*s1=s;
			if (!x) *s1++='0';
			if (x<0) oc('-'),x=-x;
			while (x) *s1++=x%10+'0',x/=10;
			do {s1--; oc(*s1);} while (s1!=s);
		}
		inline void print(char s) {
			oc(s);
		}
		inline void print(char *s) {
			for (; *s; oc(*s++));
		}
		inline void print(const char *s) {
			for (; *s; oc(*s++));
		}
		inline void print(string s) {
			for (unsigned i=0; i<s.length(); i++) oc(s[i]);
		}
		struct _flush {
			~_flush() {flush();}
		} fflush;
	};
	template<typename T>
	inline void read(T &x) {Istream::readPositive(x);}
	inline void read(char *x) {Istream::read(x);}
	template<typename T>
	inline void print(T x) {Ostream::print(x);}
	template<typename T>
	inline void println(T x) {print(x); Ostream::oc('\n');}
}
using namespace fastIO;

int main() {
	int i; read(n); read(K);
	FOR(i,1,n-1) {
		int u,v; read(u); read(v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} FOR(i,1,n) read(A[i]),A[i]%=K;
	read(q);
	FOR(i,1,q) {
		int u,v; read(u); read(v);
		queries[u].push_back(make_pair(v,i));
		queries[v].push_back(make_pair(u,i));
	} minweight=n;
	dfs1(1,0,n); dfs3(root);
	FOR(i,1,q) println(ans[i]);
}
/*
*/
