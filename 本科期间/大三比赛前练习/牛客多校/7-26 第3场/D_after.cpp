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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=B; A+=B; A%=B;}
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

const LL MOD=998244353;
const LL g=3;
LL mul(LL x,LL y) {
    return x*y%MOD;
}
ll poww(ll a,ll b){
	ll ret=1;
	for (;b;b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
}
void ntt(ll *A,int len,int inv){
	int i,j,k;
	for (i=1,j=len/2; i<len-1;i++){
		if (i<j) swap(A[i],A[j]);
		k=len/2;
		while (j>=k) j-=k,k/=2;
		if (j<k) j+=k;
	}for (i=2;i<=len;i<<=1){
		ll wn=poww(g,(MOD-1)/i);
		if (inv==-1) wn=poww(wn,MOD-2);
		for (j=0;j<len;j+=i){
			ll w=1;
			for (k=j;k<j+i/2;k++){
				ll a=A[k],b=mul(w,A[k+i/2]);
				A[k]=a+b; (A[k]>MOD)&&(A[k]-=MOD);
				A[k+i/2]=a-b+MOD; (A[k+i/2]>MOD)&&(A[k+i/2]-=MOD);
				w=mul(w,wn);
			}
		}
	}
	if (inv==-1) {
		ll vn=poww(len,MOD-2);
		REP(i,len) A[i]=mul(A[i],vn);
	}
}
char nxt[256];
char A[maxn],B[maxn];
ll x1[4][maxn],x2[4][maxn],ans[maxn];
vector<int> pos;
// (A-B)^2*((A-B)^2-1)=0
// (A-B)^4-(A-B)^2=0
int TaskA() {
	int i;
	scanf("%s%s",A,B);
	scanf("%s",str);
	REP(i,26) str[i]-='a';
	int lenA=strlen(A),lenB=strlen(B);
	REP(i,lenA) A[i]-='a';
	REP(i,lenB) B[i]-='a';
	REP(i,lenA) A[i]=str[(int)A[i]];
	REP(i,lenB) B[i]=str[(int)B[i]];
	reverse(A,A+lenA);
	// REP(i,lenA) printf("%d ",(int)A[i]);puts("  <- A");
	// REP(i,lenB) printf("%d ",(int)B[i]);puts("  <- B");
	int len=1,t;
	while (len<=lenA+lenB) len<<=1;
	FOR(t,1,3){
		REP(i,lenA) x1[t][i]=poww((int)A[i],t); rep(i,lenA,len) x1[t][i]=0;
		REP(i,lenB) x2[t][i]=poww((int)B[i],t); rep(i,lenB,len) x2[t][i]=0;
	}
	// len<<=1; len<<=1;
	FOR(t,1,3) ntt(x1[t],len,1),ntt(x2[t],len,1);
	REP(i,len){
		ans[i]=0;
		ans[i]-=4*mul(x1[1][i],x2[3][i]);
		ans[i]+=6*mul(x1[2][i],x2[2][i]);
		ans[i]-=4*mul(x1[3][i],x2[1][i]);
		ans[i]+=2*mul(x1[1][i],x2[1][i]);
		mod_(ans[i],MOD);
	}ntt(ans,len,-1);
	// REP(i,lenA+lenB-1) printf("%lld ",ans[i]); puts(" <- inians");
	// REP(i,len) printf("%lld ",ans[i]); puts(" <- inians");
	ll sumA=0,sumB=0;
	REP(i,lenB){
		if (i<lenA) sumA+=poww(A[i],4)-poww(A[i],2);
		if (i>=lenA) sumB-=poww(B[i-lenA],4)-poww(B[i-lenA],2);
		sumB+=poww(B[i],4)-poww(B[i],2);
		mod_(sumB,MOD); mod_(sumA,MOD);
		ans[i]+=sumA+sumB;
		mod_(ans[i],MOD);
	}
	rep(i,lenA-1,lenB) if (!ans[i]) pos.push_back(i-lenA+1+1);
	// rep(i,lenA-1,lenB) printf("%lld ",ans[i]); puts(" <- nxtans");
	printf("%d\n",(int)pos.size());
	for (auto now:pos) printf("%d ",now);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
any
any
abcdefghijklmnopqrstuvwxyz
*/