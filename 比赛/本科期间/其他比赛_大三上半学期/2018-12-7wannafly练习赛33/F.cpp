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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
char str[maxn];

// int A[1007];
// void check() {
// 	int i,j; n=10;
// 	FOR(i,0,n*2) A[i]=i*i*i*i*i*i*i+i*i*i*i;
// 	FOR(j,1,n+1) {
// 		rFOR(i,1,n*2) A[i]=A[i]-A[i-1];
// 		FOR(i,1,n*2) printf("%d ",A[i]); puts("");
// 		int ans=0; FOR(i,1,n) ans+=A[i];
// 		printf("ans=%d\n",ans);
// 	}
// }
//上面是下面前缀和
int base[10007]={1,682498929,491101308,76479948,723816384,67347853,27368307,625544428,199888908,888050723,927880474,281863274,661224977,623534362,970055531,261384175,195888993,66404266,547665832,109838563,933245637,724691727,368925948,268838846,136026497,112390913,135498044,217544623,419363534,500780548,668123525,128487469,30977140,522049725,309058615,386027524,189239124,148528617,940567523,917084264,429277690,996164327,358655417,568392357,780072518,462639908,275105629,909210595,99199382,703397904,733333339,97830135,608823837,256141983,141827977,696628828,637939935,811575797,848924691,131772368,724464507,272814771,326159309,456152084,903466878,92255682,769795511,373745190,606241871,825871994,957939114,435887178,852304035,663307737,375297772,217598709,624148346,671734977,624500515,748510389,203191898,423951674,629786193,672850561,814362881,823845496,116667533,256473217,627655552,245795606,586445753,172114298,193781724,778983779,83868974,315103615,965785236,492741665,377329025,847549272,698611116};
void init(){
	int now=1,i; base[0]=1;
	FOR(i,1,1000000000) {
		now=(ll)now*i%M;
		if (i%10000000==0) printf("%d,",now);
	}
}
int main() {
	// init();
	int T,_; T=1;
	// scanf("%d",&T);
	FOR(_,1,T) {
		int B=0,i;
		scanf("%d%d",&n,&m);
		FOR(i,1,m) {
			int x,y;
			scanf("%d%d",&x,&y);
			if (y==n) B+=x;
		} int ans=(ll)base[n/10000000]*B%M;
		FOR(i,n/10000000*10000000+1,n) ans=(ll)ans*i%M;
		printf("%d\n",ans);
	}
}
/*
*/
