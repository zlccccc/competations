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
const LL maxn=2e5+107;
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

const ll allsize=1e5+7;
const int SIZE=400;
const int rsize=1000;
int C[rsize][allsize][2];//m
int base[rsize];
int e[maxn][2];
int L[rsize],R[rsize];
int value[maxn];
int n,m;
int id[maxn];
void change(int l,int r) {
	// l/SIZE; r/SIZE
	int i;
	if (L[id[l]]!=l) {
		int ll=l,rr=min(r,R[id[l]]);
		int le=L[id[ll]],ri=R[id[rr]];
		if (rr-ll>=SIZE/2) {
			base[id[ll]]^=1;
			FOR(i,le,ll-1) {
				C[id[i]][e[i][0]][0]^=value[e[i][1]];
				C[id[i]][e[i][1]][0]^=value[e[i][0]];
			}
			FOR(i,rr+1,ri) {
				C[id[i]][e[i][0]][0]^=value[e[i][1]];
				C[id[i]][e[i][1]][0]^=value[e[i][0]];
			}
		} else {
			FOR(i,ll,rr) {
				C[id[i]][e[i][0]][0]^=value[e[i][1]];
				C[id[i]][e[i][1]][0]^=value[e[i][0]];
			}
		} l=rr+1;
	} if (l>r) return;
	// printf("change_1: %d %d; id=%d\n",l,r,id[l]);
	i=id[l];
	for (;R[i]<=r;i++) base[i]^=1;
	l=R[i-1]+1;
	// printf("change_2: %d %d\n",l,r);
	if (l<=r) {
		int ll=l,rr=r;
		int le=L[id[ll]],ri=R[id[rr]];
		if (rr-ll>=SIZE/2) {
			base[id[ll]]^=1;
			FOR(i,le,ll-1) {
				C[id[i]][e[i][0]][0]^=value[e[i][1]];
				C[id[i]][e[i][1]][0]^=value[e[i][0]];
			}
			FOR(i,rr+1,ri) {
				C[id[i]][e[i][0]][0]^=value[e[i][1]];
				C[id[i]][e[i][1]][0]^=value[e[i][0]];
			}
		} else {
			FOR(i,ll,rr) {
				C[id[i]][e[i][0]][0]^=value[e[i][1]];
				C[id[i]][e[i][1]][0]^=value[e[i][0]];
			}
		} l=rr+1;
	}
}
int query(int x) {
	int ret=0,i;
	REP(i,id[m]+1) {
		ret^=C[i][x][0];
		if (base[i]) ret^=C[i][x][1];
	} return ret;
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		// startTimer();
		n=100000; m=200000;
		read(n); read(m);
		int i; value[0]=1;
		FOR(i,1,n) value[i]=(ll)value[i-1]*23%M;
		FOR(i,1,m) {
			read(e[i][0]); read(e[i][1]);
			id[i]=i/SIZE;
			if (i%SIZE==0) L[id[i]]=i;
			R[id[i]]=i;
			C[id[i]][e[i][0]][0]^=value[e[i][1]];
			C[id[i]][e[i][0]][1]^=value[e[i][1]];
			C[id[i]][e[i][1]][0]^=value[e[i][0]];
			C[id[i]][e[i][1]][1]^=value[e[i][0]];
		} R[id[m]+1]=m+1;
		int q;
		q=600000;
		read(q);
		REP(i,q) {
			int op,l,r;
			op=1; l=1; r=m;
			read(op); read(l); read(r);
			if (op==1) {
				change(l,r);
			} else {
				if (query(l)==query(r)) print('1');
				else print('0');
			}
		} println("");
 		FOR(i,1,m) {
 			C[id[i]][e[i][0]][0]=0;//clear
 			C[id[i]][e[i][1]][0]=0;//clear
 			C[id[i]][e[i][0]][1]=0;//clear
 			C[id[i]][e[i][1]][1]=0;//clear
 			L[id[i]]=R[id[i]]=base[id[i]]=0;
 		}
		// printTimer();
	}
}
/*

*/