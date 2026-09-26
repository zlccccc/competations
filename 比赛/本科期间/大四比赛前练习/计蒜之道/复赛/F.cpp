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
const LL maxn=1e6+107;
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


bool mark[maxn];
int mu[maxn];
int p[maxn],tot;
const int MAX=1e6+7;
void init() {
	tot=0; int i,j;
	mu[1]=1;
	FOR(i,2,MAX) {
		if (!mark[i]) p[tot++]=i,mu[i]=-1;
		REP(j,tot) {
			//感觉上不会爆,因为是从小往筛的
			if (i*p[j]>MAX) break;
			mark[i*p[j]]=1;
			if (i%p[j]==0) break;
			else mu[i*p[j]]=-mu[i];
		}
	}
}
int getphi(int x) {
	int i; int ret=x;
	for (i=2;i*i<=x;i++) if (x%i==0){
		ret=ret/i*(i-1);
		while (x%i==0) x/=i;
	} if (x>1) ret=ret/x*(x-1);
	// printf("%ret=d\n",ret);
	return ret;
}
int N,mod;
char str[maxn];
ll PW[maxn];
int main() {
	int i,k;
	scanf("%d%s%d",&N,str,&mod);
	ll pp=getphi(mod); ll mp=0;
	int n=strlen(str);
	// puts("ok");
	REP(i,n) {
		mp=mp*10+str[i]-'0';
		if (mp>pp) mp=mp%pp+pp;
	}
	// printf("%lld %lld\n",mp,pp);
	init();
	ll ans=0;
	// printf("mod=%d\n",mod);
	FOR(i,1,N) {
		ll now=0;
		FOR(k,1,N/i) {
			now=(now+((ll)k*2*i+1));
			if ((k&3)==3) now%=mod;
		} now%=mod;
		now=powMM(now,mp,mod);
		PW[i]=now;
	}
	FOR(i,1,N) {
		ll now=0;
		FOR(k,1,N/i) {
			now=now+PW[k*i]*mu[k];
		} now%=mod; now+=mod; now%=mod;
		// printf("i=%d: now=%lld\n",i,now);
		ans=(ans+now*i%mod)%mod;
	}
	printf("%lld\n",ans);
}
/*
123 234 1000000000
*/