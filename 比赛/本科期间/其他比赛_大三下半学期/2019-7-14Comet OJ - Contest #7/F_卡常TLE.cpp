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
	int L[maxn/SIZE],R[maxn/SIZE],id[maxn];
	void ini_init(int n) {
		int i;
		FOR(i,0,n+1) {
			id[i]=i/SIZE; R[id[i]]=i;
			if (!L[id[i]]) L[id[i]]=i;
		}
	}
	ll C[maxn]; ll CSUM[maxn/SIZE];
	void init(int n) {
		int i;
		FOR(i,1,n) val[i]=C[i]=CSUM[id[i]]=0;
	}
	ll getsum_bruteforce(int l,int r) {
		ll ret=0; int i;
		FOR(i,l,r) ret+=C[i];
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
		if (R[id[l]]<=r) {
			for (i=id[l]; R[i]<=r; i++) ret+=CSUM[i];
			l=L[i];
		}//否则这里会炸
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
		while (CSUM[i]<val) val-=CSUM[i],i++;
		i=L[i];
		while (C[i]<val) val-=C[i],i++;
		return i;
	}
	int pl[maxn],pr[maxn];//left|right id
	inline void update(int x,int y) {
		// debug(" update(position,initcnt,nxtcnt): %d %lld %d; SUM=%lld\n",x,C[x],y,CSUM[id[x]]);
		CSUM[id[x]]-=C[x];
		C[x]=(ll)y*(y+1)/2;
		CSUM[id[x]]+=C[x];
	}
	void removePos(int x) {//remove的同时要维护pl和pr
		if (val[x]==0) return;
		int l=getfront(getsum(1,x)),r=pr[l];
		val[x]=0;
		if (l<x) {
			pl[x-1]=l; pr[l]=x-1;
		} update(l,x-l);
		if (x<r) {
			pr[x+1]=r; pl[r]=x+1;
			update(x+1,r-x);
		}
	}
	struct insNode {int l,x,r;};
	vector<insNode> P;//insert_calculate
	void clean() {P.clear();}
	void rollback() { //roll_back_all
		reverse(P.begin(), P.end());
		for (insNode &w:P) {
			int l=w.l,x=w.x,r=w.r;
			val[x]=0;
			if (l<x) {
				pl[x-1]=l; pr[l]=x-1;
			} update(l,x-l);
			if (x<r) {
				pr[x+1]=r; pl[r]=x+1;
				update(x+1,r-x);
			}
		} P.clear();
	}
	void insertPos(int x,bool rollBack=false) {//insert的时候直接用pl和pr
		if (val[x]==1) return;
		int l=x,r=x;
		if (val[x-1]) l=pl[x-1];
		if (val[x+1]) r=pr[x+1],update(x+1,0);
		pr[l]=r; pl[r]=l; val[x]=1;
		update(l,r-l+1);
		if (rollBack) P.push_back(insNode{l,x,r});
	}
	ll query(int l,int r) {//sqrt
		int vl=val[l-1],vr=val[r+1];
		removePos(l-1); removePos(r+1);
		ll ret=getsum(l,r);
		if (vl) insertPos(l-1);
		if (vr) insertPos(r+1);
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
const int SIZE=2000;
bool cmpx(const pnode &A,const pnode &B) {
	if (A.x!=B.x) return A.x<B.x;
	return A.time<B.time;
}
bool cmptime(const pnode &A,const pnode &B) {//time一定不同
	if (A.time!=B.time) return A.time<B.time;
	return A.x<B.x;
}
bool cmpQ(const pnode &A,const pnode &B) {
	if (A.o!=B.o) return A.o<B.o;//time
	if (A.x!=B.x) return A.x<B.x;
	return A.time<B.time;
}
int initime[maxn],inival[maxn];//actually
int preval[maxn];//o_smaller
int nowtime[maxn],nowval[maxn];//考虑change时间
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
	sort(to+1,to+1+n,cmpx);
	FOR(i,1,n+1) {BID[i]=i/SIZE; if (!L[BID[i]]) L[BID[i]]=i;}
	// FOR(i,1,n) printf("%d ",BID[i]); puts("");
	sort(re+1,re+1+n,cmptime);
	FOR(i,1,n) {
		to[i].o=BID[lower_bound(re+1,re+1+n,to[i],cmptime)-re];
		re[i].o=BID[i];
	} // first
	FOR(i,1,q) {
		queries[i].o=BID[lower_bound(re+1,re+1+n,queries[i],cmptime)-re];
	} sort(queries+1,queries+1+q,cmpQ);
	int j;
	O::ini_init(MAX);
	// deputs("to_time:(time,x,l,r)");
	// FOR(i,1,n) debug("(%d %d %d %d)\n",to[i].time,to[i].x,to[i].l,to[i].r);
	// deputs("re_time:(time,x,l,r)");
	// FOR(i,1,n) debug("(%d %d %d %d)\n",re[i].time,re[i].x,re[i].l,re[i].r);
	FOR(j,1,MAX) initime[j]=-1;
	int left_repos=1;
	FOR(i,1,q) {//按时间分块
		if (i==1||queries[i].o!=queries[i-1].o) {
			for (int k=left_repos;k<L[queries[i].o];k++) {
				if (re[k].time>initime[re[k].l]) {
					// printf("re_change_initial: %d %d\n",re[k].time,re[k].x);
					inival[re[k].l]=re[k].x;//ini_value
					initime[re[k].l]=re[k].time;
				}
			} left_repos=L[queries[i].o];
			FOR(j,1,MAX) preval[j]=inival[j];
			O::init(MAX); j=1;
			//save changes
			for (int k=L[queries[i].o]; k<=n&&BID[k]==queries[i].o; k++) {//save_i
				//清空value; 否则无法全进行insert操作;
				//这里是个max以降低常数
				preval[re[k].l]=max(preval[re[k].l],re[k].x);
			}
		}
		// debug("query(t,x,l,r): %d %d %d %d, o=%d\n",queries[i].time,queries[i].x,queries[i].l,queries[i].r,queries[i].o);
		//time小的不能带删除,只能判断是否加进去
		for (; j<=n&&to[j].x<=queries[i].x; j++) {//changes
			// debug("to:(t,x,l,r): %d %d %d %d, o=%d (t=%d)\n",to[j].time,to[j].x,to[j].l,to[j].r,to[j].o,initime[to[j].l]);
			if (to[j].o<queries[i].o&&initime[to[j].l]==to[j].time) {
				int o=(preval[to[j].l]<=queries[i].x);
				if (o==0) continue;
				O::insertPos(to[j].l);
			}
		}
		// deputs("temp changes");
		for (int k=L[queries[i].o]; k<=n&&BID[k]==queries[i].o; k++) {//save
			nowval[re[k].l]=inival[re[k].l];
			nowtime[re[k].l]=initime[re[k].l];
		}
		// debug("ok2");
		for (int k=L[queries[i].o]; k<=n&&BID[k]==queries[i].o; k++) {
			if (re[k].time<=queries[i].time) {
				pnode &e=re[k];
				if (e.time>nowtime[e.l]) {
					nowtime[e.l]=e.time;
					nowval[e.l]=e.x;
				}
			}
		} //TODO: change time
		for (int k=L[queries[i].o]; k<=n&&BID[k]==queries[i].o; k++) {
			int o=(nowval[re[k].l]<=queries[i].x);
			if (o==0) continue;
			O::insertPos(re[k].l,true);
		}
		// debug("ok3");
		// debug("query(t,x,l,r): %d %d %d %d, o=%d\n",queries[i].time,queries[i].x,queries[i].l,queries[i].r,queries[i].o);
		// debug("query: %d %d %d %d\n",queries[i].time,queries[i].x,queries[i].l,queries[i].r);
		// debug("start_query\n");
		ans[queries[i].time]=O::query(queries[i].l,queries[i].r);
		O::rollback();
	}
	FOR(i,1,m) if (ans[i]!=-1) println(ans[i]);
	printTimer();
}
/*
6 6
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