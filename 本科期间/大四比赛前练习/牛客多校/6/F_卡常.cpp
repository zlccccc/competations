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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
	if (m>n||n<0) return 0;
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
// 选定前缀后, 后面全是一堆子树
// remain的从大开始选, 答案就是C(more,...)
int sz[maxn],fa[maxn];
int A[maxn],cnt[maxn],now[maxn];//C:cound
ll Cl[maxn],Cr[maxn],base[maxn];
vector<int> p[maxn];//sizes
int main() {
	int i;
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,k,i,j;
		scanf("%d%d",&n,&k);
		REP(i,n) scanf("%d",&A[i]);
		rREP(i,n) {
			base[i]=1; sz[i]=1;
			FOR(j,k*i+1,min(k*i+k,n-1)) {
				sz[i]+=sz[j]; fa[j]=i;
				base[i]=base[i]*inv[sz[j]]%M*base[j]%M;
				// printf("%d-%d; base=%d\n",i,j,base[i]);
			} base[i]=base[i]*fac[sz[i]-1]%M;
		}
		FOR(i,1,n) cnt[i]=1;//more than x
		int ans=0;
		Cr[n+1]=1;
		REP(i,n) {
			FOR(j,1,n) p[j].clear();
			ll base_this=base[i];
			rep(j,i+1,n) if (fa[j]<i) {
				p[A[fa[j]]].push_back(sz[j]);
				base_this=base_this*base[j]%M;
			} now[n+1]=0;
			//count
			rFOR(j,1,n) {
				now[j]=cnt[j]+now[j+1]; Cr[j]=1; Cl[j]=1;//需做前缀|后缀mul
				for (int k:p[j]) {
					// printf("%d: C(%d,%d); ",j,now[j],k);
					Cr[j]=Cr[j]*C(now[j],k)%M;
					Cl[j]=Cl[j]*C(now[j]-sz[i],k)%M;
					now[j]-=k;
				}
			}
			//base[i]
			Cr[n+1]=Cl[0]=1;
			FOR(j,1,n) Cl[j]=Cl[j]*Cl[j-1]%M;
			rFOR(j,1,n) Cr[j]=Cr[j]*Cr[j+1]%M;
			// puts("  <- C");
			// FOR(j,1,n) printf("%d ",cnt[j]); puts(" <- cnt");
			// FOR(j,1,n) printf("%d ",now[j]); puts(" <- rsum_cnt");
			// FOR(j,1,n) printf("%d ",Cl[j]); printf("  <- %d (l)\n",i);
			// FOR(j,1,n) printf("%d ",Cr[j]); printf("  <- %d (r)\n",i);
			FOR(j,i?A[fa[i]]:1,A[i]-1) if (cnt[j]) {
				if (now[j+1]>=sz[i]-1)//choose_other
					add_(ans,Cl[j]*Cr[j+1]%M*C(now[j+1],sz[i]-1)%M*base_this%M);//this_count
			}
			cnt[A[i]]=0;
		} ans=(ans+1)%M;
		// printf("%d\n",base[0]);
		printf("Case #%d: %d\n",_,ans);
	}
}
/*
*/