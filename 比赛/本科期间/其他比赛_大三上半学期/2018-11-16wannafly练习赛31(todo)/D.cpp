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

char op[maxn];
int l[maxn],r[maxn],rp[maxn][26];//rp:r or this of char
void changerp(int pos) {
	if (!pos) return; int k;
	REP(k,26) rp[pos][k]=rp[r[pos]][k];
	rp[pos][str[pos]-'a']=pos;
}
int main() {
	int i,k;
	scanf("%s",str+1);
	n=strlen(str+1);
	FOR(i,1,n) l[i]=i-1,r[i]=i+1;
	r[n]=0; l[0]=0;
	r[0]=1; l[n+1]=n;
	rFOR(i,1,n) {
		REP(k,26) rp[i][k]=rp[r[i]][k];
		rp[i][str[i]-'a']=i;
	} n++;
	scanf("%s",op);
	int len=strlen(op);
	bool ins=0; int pos=1;
	REP(i,len) {
		char c=op[i];
		if (!ins) {
			if (c=='i') ins=1;
			else if (c=='f') {
				i++; char c=op[i];
				if (rp[r[pos]][c-'a']) pos=rp[r[pos]][c-'a'];
			} else if (c=='x') {
				r[l[pos]]=r[pos]; l[r[pos]]=l[pos];
				changerp(pos); pos=r[pos]; //del
			} else if (c=='h') {
				if (l[pos]) pos=l[pos];
				changerp(pos);
			} else if (c=='l') {
				if (r[pos]) pos=r[pos];
			}
		} else {
			if (c=='e') ins=0;
			else if ('a'<=c&&c<='z') {
				n++; str[n]=c;
				l[n]=l[pos]; r[n]=pos;
				REP(k,26) rp[n][k]=rp[r[n]][k];
				rp[n][str[n]-'a']=pos;
				r[l[n]]=n; l[r[n]]=n;
				changerp(l[n]);
			}
		}
		// for (int i=r[0];i;i=r[i]) printf("%c",str[i]);
		// printf(" c=%c, pos=%d ins=%d",c,pos,ins);puts("");
		assert(pos);
	}
	for (int i=r[0]; i; i=r[i]) printf("%c",str[i]);
}
/*
*/
