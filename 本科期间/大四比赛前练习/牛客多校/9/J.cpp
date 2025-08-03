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

ll SUML,CNTL,SUMR,CNTR;
priority_queue<pair<ll,int> > Qnot,Ql,Qr;
ll L[maxn],R[maxn];
int main(){
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) {
		scanf("%lld%lld",&L[i],&R[i]);
		Qnot.push(make_pair(-(L[i]+L[i]),i));
	} ll ans=0;
	while (Qnot.size()||Ql.size()||Qr.size()) {
		pair<ll,int> l,mid,r;
		l=mid=r=make_pair(-INFF,0);
		if (Qnot.size()) l=Qnot.top();
		if (Ql.size()) mid=Ql.top();
		if (Qr.size()) r=Qr.top();
		if (l>mid&&l>r) {
			int i=l.second; Qnot.pop();
			Ql.push(make_pair(-(L[i]+R[i]),i));
			SUML+=L[i]+L[i]; CNTL++;
			ll MID=L[i]+L[i];
			ans=max(ans,MID*CNTL-SUML+SUMR-MID*CNTR);
			// printf("left: MID=%lld=>%lld; ans=%lld\n",MID,L[i]+R[i],MID*CNTL-SUML+SUMR-MID*CNTR);
		} else if (mid>r) {
			int i=mid.second; Ql.pop();
			Qr.push(make_pair(-(R[i]+R[i]),i));
			SUML-=L[i]+L[i]; CNTL--;
			SUMR+=R[i]+R[i]; CNTR++;
			ll MID=L[i]+R[i];
			ans=max(ans,MID*CNTL-SUML+SUMR-MID*CNTR);
			// printf("mid: MID=%lld=>%lld; ans=%lld\n",MID,R[i]+R[i],MID*CNTL-SUML+SUMR-MID*CNTR);
		} else {
			int i=r.second; Qr.pop();
			SUMR-=R[i]+R[i]; CNTR--;
			ll MID=R[i]+R[i];
			ans=max(ans,MID*CNTL-SUML+SUMR-MID*CNTR);
			// printf("right: MID=%lld; ans=%lld\n",MID,MID*CNTL-SUML+SUMR-MID*CNTR);
		}
	}
	printf("%lld\n",ans);
}