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
const LL maxn=1e5+107;
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
inline ll powMM(ll a,ll b,ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

inline bool blank(char ch) {
	return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';
}
#define BUF_SIZE 100000
bool IOerror=0;
inline char ic() {
	static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
	if (p1==pend) {
		p1=buf;
		pend=buf+fread(buf,1,BUF_SIZE,stdin);
		if (pend==p1) {IOerror=1; return -1;}
	} return *p1++;
}
void read(int &x) {
	char ch; x=0;
	while (blank(ch=ic()));
	if (IOerror) return;
	for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
}


char buf[BUF_SIZE], *p1 = buf, *pend = buf + BUF_SIZE;
inline void flush() {
	fwrite(buf,1,p1-buf,stdout);
	p1=buf;
}
inline void oc(char ch) {
	if (p1 == pend) flush();
	*p1++=ch;
}
inline void print(int x) {
	static char s[27],*s1=s;
	if (!x) *s1++='0';
	if (x<0) oc('-'),x=-x;
	while (x) *s1++=x%10+'0',x/=10;
	do {s1--; oc(*s1);} while (s1!=s);
}
inline void print(const char *s) {
	for (; *s; oc(*s++));
}
struct _flush {
	~_flush() {flush();}
} ffflush;

int sum[maxn],m;
inline int lowbit(int x) {
	return x&-x;
}
void update(int x,int val) {
	for (; x<=m; x+=lowbit(x)) sum[x]+=val;
}
int query(int x) {
	int ret=0;
	for (; x; x-=lowbit(x)) ret+=sum[x];
	return ret;
}
int val[207][207],nowcnt[maxn];
int A[maxn],B[maxn],C[maxn],D[maxn],Q[maxn];//Q:cnt
vector<int> queries[maxn];//id
vector<pii> pos[maxn];//insert
vector<pair<pii,pii> > now;//x,y;id,op
int ans[maxn];
void solve(int i,int l,int r) { //l->r区间
	if (l==r||!queries[i].size()) {
		for (int v:queries[i]) ans[v]=l;
		queries[i].clear();
		pos[i].clear();
		return;
	} now.clear();
	//position,queryid;
	for (int v:queries[i]) {
		nowcnt[v]=0;
		now.push_back(make_pair(make_pair(A[v]-1,B[v]-1),make_pair(v,1)));
		now.push_back(make_pair(make_pair(A[v]-1,D[v]),make_pair(v,-1)));
		now.push_back(make_pair(make_pair(C[v],B[v]-1),make_pair(v,-1)));
		now.push_back(make_pair(make_pair(C[v],D[v]),make_pair(v,1)));
	}//left:insert
	int mid=(l+r)/2;
	for (pii v:pos[i]) {
		int x=v.first,y=v.second;
		if (val[x][y]<=mid) {
			pos[i<<1].push_back(v);
			now.push_back(make_pair(make_pair(x,y),make_pair(0,0)));
		} else
			pos[i<<1|1].push_back(v);
	} pos[i].clear();
	sort(now.begin(), now.end());
	for (auto v:now) {
		pii pos=v.first,op=v.second;
		if (!op.first) update(pos.second,1);
		else {
			// printf("%d; %d += %d\n",op.first,pos.second,op.second);
			nowcnt[op.first]+=query(pos.second)*op.second;
		}
	}
	for (int v:queries[i]) {
		// printf("i=%d; q=%d-%d(r%d) : %d: nowcnt=%d;Q=%d\n",i,l,mid,r,v,nowcnt[v],Q[v]);
		if (nowcnt[v]<Q[v]) {
			Q[v]-=nowcnt[v];
			queries[i<<1|1].push_back(v);
		} else
			queries[i<<1].push_back(v);
	} queries[i].clear();
	for (auto v:now) { // back
		pii pos=v.first,op=v.second;
		if (!op.first) update(pos.second,-1);
	}
	solve(i<<1,l,mid);
	solve(i<<1|1,mid+1,r);
}
int main() {
	freopen("important.in", "r", stdin);
	int T,_; T=1; read(T);
	// printf("%d\n",T);
	FOR(_,1,T) {
		int i,j,n,q;
		read(n); read(m); read(q);
		// printf("%d %d %d\n",n,m,q);
		FOR(i,1,n) FOR(j,1,m) {
			pos[1].push_back(make_pair(i,j));
			read(val[i][j]);
		}
		FOR(i,1,q) {
			read(A[i]); read(B[i]); read(C[i]); read(D[i]);
			queries[1].push_back(i); Q[i]=((D[i]-B[i]+1)*(C[i]-A[i]+1)+2)/2;
		} solve(1,1,2000);
		printf("Case %d:\n",_);
		FOR(i,1,q) printf("%d\n",ans[i]);
	}
}
/*
*/