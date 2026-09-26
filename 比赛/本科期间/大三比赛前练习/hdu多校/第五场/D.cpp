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

namespace T_T{
	int pool[maxn*40],*CNT[maxn],*SUBCNT[maxn],*st=pool;
	int sz[maxn]; bool mark[maxn];
	int minweight,root;
	struct Node{
		int to,next;
		Node(int _to=0,int _next=0):to(_to),next(_next){};
	}edge[maxn*2];
	int head[maxn],tot;
	void addedge(int u,int v){
		edge[++tot]=Node(v,head[u]); head[u]=tot;
	}
	void dfs1(int x,int fa,int n){
		int weight=0; sz[x]=1;
		for (int i=head[x]; ~i; i=edge[i].next){
			int v=edge[i].to;
			if (v==fa||mark[v]) continue;
			dfs1(v,x,n); sz[x]+=sz[v];
			max_(weight,sz[v]);
		} weight=max(weight,n-sz[x]);
		if (weight<minweight) {root=x; minweight=weight;}
	}
	struct node{
		int top,sub,len,next;
		node(int _top=0,int _sub=0,int _len=0,int _next=0):top(_top),sub(_sub),len(_len),next(_next){};
	}nodes[maxn*20];
	int calhead[maxn],caltot;
	int maxdep;
	void addnode(int x,int top,int sub,int len){
		nodes[++caltot]=node(top,sub,len,calhead[x]); calhead[x]=caltot;
	}
	void dfs2(int x,int fa,int top,int sub,int dep){
		addnode(x,top,sub,dep); sz[x]=1;
		for (int i=head[x]; ~i; i=edge[i].next){
			int v=edge[i].to;
			if (v==fa||mark[v]) continue;
			dfs2(v,x,top,sub,dep+1); sz[x]+=sz[v];
		} maxdep=max(maxdep,dep);
	}
	int len[maxn],sublen[maxn];
	void dfs3(int x){
		mark[x]=1; root=x;
		maxdep=0; int xdep=0;
		addnode(x,x,0,0);
		for (int i=head[x]; ~i; i=edge[i].next){
			int v=edge[i].to;
			if (mark[v]) continue;
			minweight=sz[v]; dfs1(v,0,sz[v]);
			maxdep=0; dfs2(v,0,x,root,1);
			sublen[root]=maxdep; xdep=max(xdep,maxdep);
			SUBCNT[root]=st; st+=sublen[root]+1;
			dfs3(root);
		} len[x]=xdep;
		CNT[x]=st; st+=len[x]+1;
	}
	inline void update(int x){
		for (int i=calhead[x]; ~i; i=nodes[i].next){
			int v=nodes[i].top,length=nodes[i].len;
			CNT[v][length]++;
			v=nodes[i].sub;
			if (v) SUBCNT[v][length]++;
		}
	}
	inline int query(int x,int dis){
		int ret=0;
		for (int i=calhead[x]; ~i; i=nodes[i].next) {
			int v=nodes[i].top,length=nodes[i].len;
			if (dis>=length){
				ret+=CNT[v][min(dis-length,len[v])];
				v=nodes[i].sub;
				if (v) ret-=SUBCNT[v][min(dis-length,sublen[v])];
			}
		} return ret;
	}
	void init(int n){
		int i;
		FOR(i,1,n) mark[i]=0,CNT[i]=SUBCNT[i]=nullptr,len[i]=sublen[i]=0;
		memset(pool,0,sizeof(int)*(st-pool)); st=pool;
		FOR(i,1,n) head[i]=calhead[i]=-1; tot=caltot=0;
	}
	void initsolve(int n){
		int i,j;
		minweight=INF;
		dfs1(1,0,n+n-1);
		dfs3(T_T::root);
		FOR(i,1,n) T_T::update(i);
		FOR(i,1,n+n-1) {
			FOR(j,1,len[i]) CNT[i][j]+=CNT[i][j-1];
			FOR(j,1,sublen[i]) SUBCNT[i][j]+=SUBCNT[i][j-1];
		}
	}
}
namespace lca{
	int fa[maxn][17],dep[maxn];
	vector<int> edge[maxn];
	void dfs(int x,int father,int depth){
		int i; fa[x][0]=father; dep[x]=depth;
		rep(i,1,17) fa[x][i]=fa[fa[x][i-1]][i-1];
		for (int v:edge[x]) if (v!=father) dfs(v,x,depth+1);
	}
	void addedge(int u,int v){
		edge[u].push_back(v);
	}
	inline int lca(int x,int y){
		int i;
		if (dep[x]<dep[y]) swap(x,y);
		rREP(i,17) if (dep[x]-dep[y]>=(1<<i)) x=fa[x][i];
		if (x==y) return x;
		rREP(i,17) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	inline int len(int x,int y){
		return dep[x]+dep[y]-2*dep[lca(x,y)];
	}
	inline int kthfa(int x,int k){
		int i;
		rREP(i,17) if (k>=1<<i) x=fa[x][i],k-=1<<i;
		return x;
	}
	void init(int n){
		int i;
		FOR(i,1,n) edge[i].clear();
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
	startTimer();
	int T; read(T);
	while (T--) {
		int i; read(n); read(q);
		T_T::init(n+n-1);
		lca::init(n+n-1);
		FOR(i,1,n-1) {
			int u,v; read(u); read(v);
			T_T::addedge(u,i+n);
			T_T::addedge(i+n,u);
			T_T::addedge(v,i+n);
			T_T::addedge(i+n,v);
			lca::addedge(u,i+n);
			lca::addedge(i+n,u);
			lca::addedge(v,i+n);
			lca::addedge(i+n,v);
		} lca::dfs(1,0,0);
		int ans=0;
		T_T::initsolve(n);
		while (q--) {
			int u,v,l; read(u); read(v); read(l);
			u=(u+ans)%n+1; v=(v+ans)%n+1;
			l=(l+ans)%n; l*=2;
			// printf("ask : %d %d %d\n",u,v,l);
			if (lca::dep[u]<lca::dep[v]) swap(u,v);
			ans=T_T::query(u,l)+T_T::query(v,l);
			// printf("ans1= %d\n",ans);
			int len=lca::len(u,v);
			if (len<=l*2) {
				int x=lca::kthfa(u,len/2);
				ans-=T_T::query(x,l-len/2);
				// printf("ans2= %d  (%d %d)\n",ans,x,l-len/2);
			} println(ans);
		}
	}
	printTimer();
	exit(0);
}
/*
*/
