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

struct node {
	int sum,ans,lazy;
} T[maxn];
void change(int x,int val,int L,int R) {
	add_(T[x].ans,(ll)(R-L+1)*(R-L)/2%M*val%M*val%M);
	// printf("change : %d %d %d %d   %d %d\n",x,val,L,R,T[x].sum,T[x].ans);
	add_(T[x].ans,(ll)(R-L)*val%M*T[x].sum%M);
	add_(T[x].sum,(ll)(R-L+1)*val%M);
	add_(T[x].lazy,val);
}
void pushdown(int x,int L,int R) {
	if (T[x].lazy) {
		int mid=(L+R)/2;
		change(x<<1,T[x].lazy,L,mid);
		change(x<<1|1,T[x].lazy,mid+1,R);
		T[x].lazy=0;
	}
}
node merge(node &A,node &B) {
	node ret=A; ret.lazy=0;
	add_(ret.ans,B.ans);
	add_(ret.ans,(ll)A.sum*B.sum%M);
	add_(ret.sum,B.sum);
	return ret;
}
void update(int x,int l,int r,int val,int L,int R) {
	if (l<=L&&R<=r) {
		// printf("%d-%d : %d\n",l,r,val);
		change(x,val,L,R);
		return;
	} int mid=(L+R)/2;
	pushdown(x,L,R);
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
node ans;
void query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {
		// printf("query: %d-%d  %d %d\n",l,r,T[x].sum,T[x].ans);
		ans=merge(ans,T[x]);
		return;
	} int mid=(L+R)/2;
	pushdown(x,L,R);
	if (l<=mid) query(x<<1,l,r,L,mid);
	if (mid<r) query(x<<1|1,l,r,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}

vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],dep[maxn];
int id[maxn],out[maxn],tot;
void dfs1(int u,int from,int depth) {
	int mx=-1;
	sz[u]=1; fa[u]=from; dep[u]=depth; son[u]=0;
	for (int v:edge[u]) {
		if (v==from) continue;
		dfs1(v,u,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x) {
	top[u]=x; id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for (int v:edge[u]) {
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	} out[u]=tot;
}
inline void Update(int x,int y,int val){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],val,1,tot);
		x=fa[top[x]];
	} if (dep[x]>dep[y]) swap(x,y);
	update(1,id[x],id[y],val,1,tot);
}
inline void Query(int x,int y){
	ans.sum=ans.ans=ans.lazy=0;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		query(1,id[top[x]],id[x],1,tot);
		x=fa[top[x]];
	} if (dep[x]>dep[y]) swap(x,y);
	query(1,id[x],id[y],1,tot);
}
int A[maxn];
int main() {
	int i; read(n); read(m);
	FOR(i,1,n) read(A[i]);
	FOR(i,1,n-1) {
		int u,v; read(u); read(v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs1(1,0,1); dfs2(1,1);
	FOR(i,1,n) Update(i,i,A[i]);
	FOR(i,1,m){
		int op; read(op);
		if (op==1){
			int u,val;
			read(u); read(val);
			update(1,id[u],out[u],val,1,tot);
		} if (op==2){
			int u,v,val;
			read(u); read(v); read(val);
			Update(u,v,val);
		} if (op==3){
			int u,v;
			read(u); read(v);
			Query(u,v);
			println(ans.ans);
		}
	}
}
/*
3 8
1 1 1
1 2
2 3
3 1 3
1 1 2
3 1 3
1 1 2
3 1 3
1 1 2
3 1 3
1 1 2

3 16
1 1 1
1 2
2 3
3 1 3
1 1 1
3 1 3
1 1 1
3 1 3
1 1 1
3 1 3
1 1 1
3 1 3
1 1 1
3 1 3
1 1 1
3 1 3
1 1 1
3 1 3
1 1 1
*/
