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

ll B[maxn];
ll INV[10007];
LL inv[10002];//inverse
LL fac[10002];//Factorial
LL C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
} ll SUM_N_K(int n,int k) {
	ll pw=1,now=0; int i;
	FOR(i,1,k+1) {
		pw=pw*(n+1)%M;
		now+=INV[k+1]*C(k+1,i)%M*B[k+1-i]%M*pw%M;
	} mod_(now);
	// printf("sumnk %d %d : %lld\n",n,k,now);
	return now;
}
void init() {
	int i,j;
	fac[0]=1;
	FOR(i,1,10000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1; INV[0]=INV[1]=1;
	FOR(i,2,10000) INV[i]=inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,10000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	B[0]=1;
	FOR(i,1,2000) {
		FOR(j,0,i-1) B[i]-=INV[i+1]*C(i+1,j)%M*B[j]%M; mod_(B[i]);
	}
}

namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	const int MAXP=666666;
	const int MAX=2000010;
	int mu[MAX],F[MAX];
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
		rep(i,1,MAX) F[i]=(M+mu[i])%M,add_(F[i],F[i-1]);
	}
	map<int,int> HASH;
	int sum_F(int x){
		if (x<MAX) return F[x];
		if (HASH.count(x)) return HASH[x];
		int l; int ret=1;
		FOR(l,2,x){
			int t=x/l,r=x/t;
			add_(ret,M-(ll)(r-l+1)*sum_F(t)%M);
			l=r;
		} return HASH[x]=ret;
	}
}
map<pair<int,int>,int> HASH1[57];
int solve1_1(int n,int cnt,int g,const vector<int> &p){
	if (HASH1[cnt].count(make_pair(n,g))) return HASH1[cnt][make_pair(n,g)];
	int ans=SUM_N_K(n,cnt); if (!cnt) ans--;
	for(int x:p) if (x<=n){
		vector<int> _p;
		for (int v:p) if ((g/x)%v==0) _p.push_back(v);
		add_(ans,M-solve1_1(n/x,cnt,g/x,_p));
	} return HASH1[cnt][make_pair(n,g)]=ans;
}
int solve1(int n,int cnt,int g) {
	vector<int> p;
	for (int i=1; i*i<=g; i++) {
		if (g%i==0) {
			if (i!=1) p.push_back(i);
			if (i*i!=g) p.push_back(g/i);
		}
	} sort(p.begin(),p.end());
	return solve1_1(n,cnt,g,p);
}
int solve2(int n,int cnt){
	// printf("solve2: %d %d\n",n,cnt);
	int l,ans=0; if (!cnt) return 1;
	FOR(l,1,n){
		int t=n/l,r=n/t;
		add_(ans,(ll)(seives::sum_F(r)-seives::sum_F(l-1)+M)*SUM_N_K(t,cnt)%M);
		l=r;
	} 
	// int now=0,r;
	// FOR(l,1,n) FOR(r,1,n/l) add_(now,(ll)(seives::mu[l]+M)*powMM(r,cnt)%M);
	// printf("now=%d , ans=%d\n",now,ans);
	return ans;
}
int A[maxn];
int main() {
	int T,_t;
	seives::init(); init();
	// int a,b; while (~scanf("%d%d",&a,&b)) solve2(a,b);
	scanf("%d",&T);
	FOR(_t,1,T) {
		int k,cnt=0,i;
		scanf("%d%d",&k,&n); int g=0;
		FOR(i,1,k) scanf("%d",&A[i]);
		FOR(i,1,k) if (~A[i]&&A[i]) g=A[i];
		FOR(i,1,k) if (~A[i]&&A[i]) g=gcd(g,A[i]);
		FOR(i,1,k) if (A[i]==-1) cnt++;
		if (g) printf("Case #%d: %d\n",_t,solve1(n,cnt,g));
		else printf("Case #%d: %d\n",_t,solve2(n,cnt));
	}
}
/*
10
5 10
-1 -1 8 -1 -1
5 10
2 4 8 6 10
5 10
2 4 8 6 -1
3 20
-1 6 18
5 5
-1 -1 -1 -1 -1
5 5
0 0 0 0 -1
*/