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
const LL M=998244353;
const LL maxn=3e5+107;
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

int fa[maxn],top[maxn];
vector<int> edge[maxn];
int id[maxn],son[maxn],sz[maxn],tot;
void dfs(int x,int father) {
	sz[x]=1; fa[x]=father; int mx=-1;
	for (int v:edge[x]) {
 		dfs(v,x); sz[x]+=sz[v];
 		if (sz[v]>mx) mx=sz[v],son[x]=v;
	} return;
}
void dfs2(int u,int x) {
	top[u]=x; id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for (int v:edge[u]) if (v!=son[u])
		dfs2(v,v);
}
vector<pair<int,int> > now;
void getnow(int x) {
	now.clear();
	while (x) {
		now.push_back(make_pair(id[top[x]],id[x]));
		x=fa[top[x]];
	}
}
ll lz[maxn*4],sum[maxn*4];
ll query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) return sum[x];
	int mid=(L+R)/2;
	ll ret=lz[x]*(min(R,r)-max(l,L)+1);
	if (l<=mid) ret+=query(x<<1,l,r,L,mid);
	if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
	return ret;
}
void update(int x,int l,int r,int val,int L,int R) {
	if (l<=L&&R<=r) {
		lz[x]+=val,sum[x]+=val*(R-L+1);
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	sum[x]=lz[x]*(R-L+1)+sum[x<<1]+sum[x<<1|1];
}
vector<pair<pair<int,int>,int> > UP[maxn],queries[maxn];
int V[maxn],L[maxn],R[maxn];
ll ans[maxn];
int main() {
	int n,m,q,i;
	read(n); read(m);
	FOR(i,1,m) {
		int f; read(f);
		read(V[i]); read(L[i]); read(R[i]);
		fa[V[i]]=f;
		edge[f].push_back(V[i]);
	}
	FOR(i,1,m+1) if (!fa[i]) {
		dfs(i,0); dfs2(i,i);
	}
	// FOR(i,1,n) printf("%d ",id[i]); puts("id");
	FOR(i,1,m) {
		getnow(V[i]);
		for (auto p:now) {
			UP[p.first].push_back(make_pair(make_pair(L[i],R[i]),1));
			UP[p.second+1].push_back(make_pair(make_pair(L[i],R[i]),-1));
			// printf("%d-%d : %d-%d\n",L[i],R[i],p.first,p.second);
		}
	}
	read(q);
	FOR(i,1,q) {
		int x,l,r; read(x);
		read(l); read(r);
		if (x==1) ans[i]=r-l+1;
		queries[id[x]].push_back(make_pair(make_pair(l,r),i));
	}
	FOR(i,1,m+1) {
		for (auto now:UP[i]) {
			update(1,now.first.first,now.first.second,now.second,1,m+1);
		}for (auto now:queries[i]) {
			ans[now.second]+=query(1,now.first.first,now.first.second,1,m+1);
		}
	}
	FOR(i,1,q) println(ans[i]);
}
/*
*/