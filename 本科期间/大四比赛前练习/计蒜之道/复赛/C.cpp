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
const LL M=998244353;
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

int sg[maxn];
int mex[maxn];
void getmex(){
	int i,j;
	FOR(i,1,10000) {
		FOR(j,0,i) mex[j]=0;
		FOR(j,1,i-1) if (i%j==0) mex[sg[i-j]]++;
		int ans=0;
		while (mex[ans]) ans++;
		sg[i]=ans;
	}
	// FOR(i,1,100) {
	// 	printf("%d:%d\n",i,sg[i]);
	// }
}
char str[maxn];
int g[maxn];
ll A[maxn];
void divide(int &n){
	int i;
	// rREP(i,n) printf("%08d",g[i]); puts("");
	REP(i,n) g[i]=(g[i+1]&1)*50000000+g[i]/2;
	REP(i,n) g[i+1]+=g[i]/100000000,g[i]%=100000000;
	while (n&&!g[n-1]) n--;
}
int modify(int n){
	int ret=0,i;
	rREP(i,n) ret=((ll)ret*100000000+g[i])%M;
	// printf("ret=%d\n",ret);
	return ret;
}

void fwt(LL *A,int len,int inv){
	int i,j,k;
	int div=powMM(2ll,M-2);
	for(i=2;i<=len;i<<=1){
		for(j=0;j<len;j+=i){
			for(k=j;k<j+i/2;k++){
				if (inv==1){
					LL a=A[k],b=A[k+i/2];
					A[k]=(a+b)%M;
					A[k+i/2]=(a-b+M)%M;
				//xor:a[k]=x+y,a[k+i/2]=(x-y+mod)%mod;
				//and:a[k]=x+y;
				//or:a[k+i/2]=x+y;
				}else{
					LL a=A[k],b=A[k+i/2];
					A[k]=(a+b)*div%M;
					A[k+i/2]=(a-b+M)%M*div%M;
				//xor:a[k]=(x+y)/2,a[k+i/2]=(x-y)/2;
				//and:a[k]=x-y;
				//or:a[k+i/2]=y-x;
				}
			}
		}
	}
}
ll B[maxn];
int main() {
	// getmex();
	ll m;
	scanf("%s%lld",str,&m);
	int n=strlen(str),i=0,j,k=0;
	REP(i,n) {
		int base=1;
		REP(j,i%8) base*=10;
		g[i/8]+=(str[n-i-1]-'0')*base;
	} n/=8; n++;
	while (n) {
		A[k++]=modify(n); divide(n);
	}
	rREP(i,k) {
		add_(A[i],M-B[i+1]);
		add_(B[i],A[i]);
		add_(B[i],B[i+1]);
	}
	// REP(i,k) printf("%lld ",A[i]); puts("");
	memset(B,0,sizeof(B)); B[0]=1;
	fwt(A,1<<15,1);
	fwt(B,1<<15,1);
	for (;m;m>>=1ll) {
		if (m&1) {
			REP(i,(1<<15)) B[i]=(ll)A[i]*B[i]%M;
		}
		REP(i,(1<<15)) A[i]=(ll)A[i]*A[i]%M;
	}
	fwt(B,1<<15,-1);
	int ans=0;
	// REP(i,16) printf("%lld ",B[i]);
	rep(i,1,(1<<15)) add_(ans,B[i]);
	printf("%d\n",ans);
}
/*
helloworld
1000000000
*/