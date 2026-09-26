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
#include <unordered_map>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG1
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
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
// template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
// template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
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

const int C=1000;//block_size
ll base1[maxn];
unordered_map<int,int> MP;
int pval[maxn];
void getpval(int x0,ll a,ll b,ll p) {
	int i=0; pval[0]=x0;
	FOR(i,1,1000) {
		pval[i]=((ll)pval[i-1]*a+b)%p;
		printf("gval=%lld\n",((b+(a-1+p)*x0)%p*powMM(a,i,p)-b+p-pval[i]*(a-1+p)%p+p)%p);
	}
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		/*to solve the problem*/
		ll n,x0,a,b,p;
		scanf("%lld%lld%lld%lld%lld",&n,&x0,&a,&b,&p);
		x0%=p; a%=p; b%=p;
		int C=1000,t=1e9/C+1;//last; t=last_cnt
		t=min((ll)t,min(n,p)/C+1);
		if (a==1) {
			int i;
			base1[0]=0;
			FOR(i,1,C) base1[i]=((ll)base1[i-1]+b)%p;
			ll base_p=x0;//*leftbase
			MP.clear();
			startTimer();
			FOR(i,1,t) {
				base_p=(base_p+base1[C])%p;
				if (!MP.count(base_p)) MP[base_p]=i*C;
			}
			printTimer();
		} else if (a>=2) {
			int i;
			base1[0]=1;
			FOR(i,1,C) base1[i]=(ll)base1[i-1]*a%p;
			ll base_p=(b+(a-1+p)*x0)%p;//*leftbase
			MP.clear();
			startTimer();
			FOR(i,1,t) {
				base_p=base_p*base1[C]%p;
				if (!MP.count(base_p)) MP[base_p]=i*C;
			}
			printTimer();
		}
		int o,q; scanf("%d",&q);
		// getpval(x0,a,b,p);
		REP(o,q) {
			int v; scanf("%d",&v);
			// int v=pval[o];
			// printf("getans: %d %d\n",o,pval[o]);
			if (v==x0) {puts("0"); continue;}
			if (v==(x0*a+b)%p) {puts("1"); continue;}
			if (a==0) {
				int ans=INF;
				if (v==x0) ans=0;
				else if (v==b) ans=1;
				if (ans==INF||ans>=n) puts("-1");
				else printf("%d\n",ans);
			} else if ((b+a*x0)%p==x0) {
				int ans=INF;
				if (v==x0) ans=0;
				if (ans==INF||ans>=n) puts("-1");
				else printf("%d\n",ans);
			} else if (a==1) {
				ll base=v;
				int i,ans=INF;
				FOR(i,1,C) {
					unordered_map<int,int>::iterator it=MP.find((base+base1[i]));
					if (it!=MP.end()) ans=min(ans,it->second-i);
				}
				if (ans==INF||ans>=n) puts("-1");
				else printf("%d\n",ans);
			} else {
				ll base=(v*(a-1+p)+b)%p;
				int i,ans=INF;
				FOR(i,1,C) {
					unordered_map<int,int>::iterator it=MP.find(base*base1[i]%p);
					if (it!=MP.end()) ans=min(ans,it->second-i);
				}
				if (ans==INF||ans>=n) puts("-1");
				else printf("%d\n",ans);
			}
		}
	}
}
/*
3
20 15 7 4 17 20
*/