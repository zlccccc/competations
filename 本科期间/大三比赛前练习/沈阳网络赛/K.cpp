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

namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	const int MAXP=166666;
	const int MAX=700001;
	int mu[MAX];
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init() {
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0; mu[1]=1;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i,mu[i]=-1;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) break;
				else mu[i*p[j]]=-mu[i];
			}
		}
	}
}using namespace seives;

bool okay(int n){
	bool ret=true;
	// printf("check : %d\n",n);
	while (n){
		int k=n; int del=1;
		while (k){
			// printf("k=%d okay=%d\n",k,(int)ret);
			if (k!=1&&!isprime(k)) ret=false;
			if (k<10) del*=k;
			else del*=10;
			k/=10;
		} n-=del;
		// printf("n=%d\n",n);
	}return ret;
}

int F[]={1 ,2 ,3 ,5 ,7  ,11 ,13 ,17 ,23 ,31,
		 37,53,71,73,113,131,137,173,311,317,INF};
int main() {
	int T,_t,i,k;
	// seives::init(); int ans=1;
	// REP(i,seives::tot)
	// 	if (okay(seives::p[i])) printf("%d,",seives::p[i]),ans++;
	// printf("%d ",ans);
	scanf("%d",&T);
	FOR(_t,1,T){
		scanf("%s",str);
		int len=strlen(str);
		if (len>5) printf("Case #%d: 317\n",_t);
		else {
			n=0;
			REP(i,len) n=n*10+str[i]-'0';
			printf("Case #%d: %d\n",_t,*(upper_bound(F,F+20,n)-1));
		}
	}
}
/*
*/
