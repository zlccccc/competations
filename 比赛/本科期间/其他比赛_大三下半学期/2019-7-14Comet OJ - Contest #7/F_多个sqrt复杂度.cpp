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
// #define debug(...) printf(__VA_ARGS__)
// #define deputs(str) printf("%s\n",str)
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
			char ch; x=0;
			while (blank(ch=ic()));
			if (IOerror) return;
			for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
		}
		template<typename T>
		inline void read(T &x) {
			char ch; T op=1; x=0;
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

namespace O {
	const int maxn=3e5+7;
	const int SIZE=700;
	int val[maxn];
	int L[maxn],R[maxn],id[maxn];
	void ini_init(int n) {
		int i;
		FOR(i,0,n+1) {
			id[i]=i/SIZE; R[id[i]]=i;
			if (!L[id[i]]) L[id[i]]=i;
		}
	}
	ll C[maxn]; ll CSUM[maxn];
	void init(int n) {
		// deputs("initialize");
		int i;
		FOR(i,1,n) val[i]=C[i]=CSUM[id[i]]=0;
	}
	ll getsum_bruteforce(int l,int r) {
		ll ret=0; int i;
		FOR(i,l,r) ret+=(ll)C[i]*(C[i]+1)/2;
		return ret;
	}
	ll getsum(int l,int r) {
		ll ret=0; int i;
		if (L[id[l]]!=l) {
			int ll=l,rr=min(r,R[id[l]]),x=id[ll];
			if (rr-ll>=SIZE/2) {
				ret+=CSUM[x];
				ret-=getsum_bruteforce(L[x],ll-1);
				ret-=getsum_bruteforce(rr+1,R[x]);
			} else
				ret+=getsum_bruteforce(ll,rr);
			l=rr+1;
		} 
		if (l>r) return ret;
		// debug("getans 0: l=%d; r=%d; ret=%lld\n",l,r,ret);
		if (R[id[l]]<=r) {
			for (i=id[l]; R[i]<=r; i++) ret+=CSUM[i];
			l=L[i];
		}//否则这里会炸
		// debug("getans 1: l=%d; r=%d; ret=%lld\n",l,r,ret);
		if (l<=r) {
			int ll=l,rr=r,x=id[ll];
			if (rr-ll>=SIZE/2) {
				ret+=CSUM[x];
				ret-=getsum_bruteforce(L[x],ll-1);
				ret-=getsum_bruteforce(rr+1,R[x]);
			} else
				ret+=getsum_bruteforce(ll,rr);
			l=rr+1;
		} return ret;
	}
	int getfront(ll val) {
		int i=0;
		// printf(" _getfront: %lld\n",val);
		while (CSUM[i]<val)
			val-=CSUM[i],i++;
		i=L[i];
		while ((ll)C[i]*(C[i]+1)/2<val){
			// if (C[i]) debug("DEL: %d(%lld) ",i,C[i]);
			val-=C[i]*(C[i]+1)/2,i++;
		}
		// debug("  _getfront : i=%d %lld; C=%lld\n",i,val,(ll)C[i]*(C[i]+1)/2);
		return i;
	}
	void update(int x,int y) {
		// debug(" update(position,initcnt,nxtcnt): %d %lld %d; SUM=%lld\n",x,C[x],y,CSUM[id[x]]);
		CSUM[id[x]]-=(ll)C[x]*(C[x]+1)/2;
		C[x]=y;
		CSUM[id[x]]+=(ll)C[x]*(C[x]+1)/2;
	}
	void change(int x,int y) {//val[x]->y
		if (val[x]==y) return;
		// printf("   change: %d %d\n",x,y);
		// debug("   change: %d %d\n",x,y);
		// int p0=getsum(1,x),p1=getfront(p0),p2=C[p1];
		// debug("     sum_value,pos_value,cnt=%d %d %d;preval=%d\n",p0,p1,p2,C[x-1]);
		//change TODO:减少常数
		if (y==0) {//remove
			// printf("REMOVE: pos=%d,val=%d\n",x,val[x]);
			int pos=getfront(getsum(1,x));
			int initcnt=C[pos];
			val[x]=y; initcnt-=x-pos+1;
			update(pos,x-pos);
			if (initcnt) update(x+1,initcnt);
		} else {
			// puts("INSERT: ");
			int pos=x;
			if (val[x-1]) pos=getfront(getsum(1,x-1));
			val[x]=y; int initcnt=C[pos];
			if (val[x+1]) {
				initcnt+=C[x+1];
				update(x+1,0);
			} initcnt++;
			update(pos,initcnt);
		}
	}
	ll query(int l,int r) {
		int vl=val[l-1],vr=val[r+1];
		change(l-1,0); change(r+1,0);
		ll ret=getsum(l,r);
		change(l-1,vl); change(r+1,vr);
		// debug("printf(%d->%d): %lld\n",l,r,ret);
		return ret;
	}
}
//pair<time,x> pair<l,r>
//x:time
//op=0(update):l=pos,y=val
//op=1(query):l,r
struct pnode {
	int time,x,l,r,o;
} to[maxn*2],re[maxn*2],queries[maxn];
int BID[maxn*2],L[maxn*2];
const int SIZE=1000;
bool cmptime(const pnode &A,const pnode &B) {//time一定不同
	if (A.time!=B.time) return A.time<B.time;
	return A.x<B.x;
}
bool cmpx(const pnode &A,const pnode &B) {
	if (A.x!=B.x) return A.x<B.x;
	return A.time<B.time;
}
bool cmpQ(const pnode &A,const pnode &B) {
	if (A.o!=B.o) return A.o<B.o;//time
	if (A.time!=B.time) return A.time<B.time;
	return A.x<B.x;
}
int timeval[maxn];//back
int initval[maxn],inittime[maxn];
ll ans[maxn];
int main() {
	startTimer();
	int n,m,q; int i;
	read(n); read(m);
	FOR(i,1,n) {
		read(to[i].x);
		to[i].l=i; to[i].time=0;
	} q=0;
	int MAX=n;
	FOR(i,1,m) {
		int op; read(op);//time
		if (op==1) {
			int x,y; n++;
			read(x); read(y);
			to[n].l=x; to[n].x=y;
			to[n].time=i; ans[i]=-1;
		} else {
			int l,r,x; q++;
			read(l); read(r); read(x);
			queries[q].l=l; queries[q].r=r;
			queries[q].time=i; queries[q].x=x;
		}
	}
	FOR(i,1,n) re[i]=to[i];
	sort(to+1,to+1+n,cmptime);
	FOR(i,1,n+1) {BID[i]=i/SIZE; if (!L[BID[i]]) L[BID[i]]=i;}
	// FOR(i,1,n) printf("%d ",BID[i]); puts("");
	sort(re+1,re+1+n,cmpx);
	FOR(i,1,n) {
		to[i].o=BID[lower_bound(re+1,re+1+n,to[i],cmpx)-re];
		re[i].o=BID[i];
	} // first
	FOR(i,1,q) {
		queries[i].o=BID[lower_bound(re+1,re+1+n,queries[i],cmpx)-re];
	} sort(queries+1,queries+1+q,cmpQ);
	int j;
	O::ini_init(MAX);
	// puts("to_time:(time,x,l,r)");
	// FOR(i,1,n) printf("(%d %d %d %d) o=%d\n",to[i].time,to[i].x,to[i].l,to[i].r,re[i].o);
	// puts("re_time:(time,x,l,r)");
	// FOR(i,1,n) printf("(%d %d %d %d) o=%d\n",re[i].time,re[i].x,re[i].l,re[i].r,re[i].o);

	// deputs("to_time:(time,x,l,r)");
	// FOR(i,1,n) debug("(%d %d %d %d)\n",to[i].time,to[i].x,to[i].l,to[i].r);
	// deputs("re_time:(time,x,l,r)");
	// FOR(i,1,n) debug("(%d %d %d %d)\n",re[i].time,re[i].x,re[i].l,re[i].r);
	FOR(i,1,q) {
		if (i==1||queries[i].o!=queries[i-1].o) {
			FOR(j,1,MAX) timeval[j]=-1;
			O::init(MAX); j=1;
		}
		// debug("ok0");
		for (; j<=n&&to[j].time<=queries[i].time; j++) {
			if (to[j].o<queries[i].o) {//changes
				timeval[to[j].l]=to[j].time;
				// int o=(e.x<=queries[i].x);
				O::change(to[j].l,1);
			} else if (queries[i].o<to[j].o) {
				timeval[to[j].l]=to[j].time;
				O::change(to[j].l,0);
			}
		}
		// debug("ok1");
		// puts("temp changes");
		for (int k=L[queries[i].o]; k<=n&&BID[k]==queries[i].o; k++) {//save
			initval[re[k].l]=O::val[re[k].l];
			inittime[re[k].l]=timeval[re[k].l];
		}
		// debug("ok2");
		for (int k=L[queries[i].o]; k<=n&&BID[k]==queries[i].o; k++) {
			if (re[k].time<=queries[i].time) {
				pnode &e=re[k];
				int o=(e.x<=queries[i].x);
				if (e.time>timeval[e.l]) {
					timeval[e.l]=e.time;
					O::change(e.l,o);
				}
			}
		} //TODO: change time
		// debug("ok3");
		// printf("query(t,x,l,r): %d %d %d %d, o=%d\n",queries[i].time,queries[i].x,queries[i].l,queries[i].r,queries[i].o);
		// debug("query: %d %d %d %d\n",queries[i].time,queries[i].x,queries[i].l,queries[i].r);
		ans[queries[i].time]=O::query(queries[i].l,queries[i].r);
		for (int k=L[queries[i].o]; k<=n&&BID[k]==queries[i].o; k++) {
			timeval[re[k].l]=inittime[re[k].l];
			O::change(re[k].l,initval[re[k].l]);
		}
		// debug("ok4");
	}
	FOR(i,1,m) if (ans[i]!=-1) println(ans[i]);
	printTimer();
}
/*
6 2
1 1 4 5 1 4
1 1 4
2 1 4 2
2 1 1 4
2 1 5 4
1 5 4 
2 3 3 3

10 5
8 8 5 2 8 3 2 7 4 6
1 1 6
1 2 2
2 5 7 8
2 7 8 2
2 6 9 9

*/