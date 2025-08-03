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
const LL maxn=1e4+107;
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
// char str[maxn];

int A[107];
int C[10007];
bool okay[10007];//3 times
vector<int> check[10007];
int pre[maxn];
int main() {
	int _,T;
	int i,j,k,t;
	REP(i,4096) C[i]=C[i>>1]+(i&1); 
	REP(i,12) rep(j,i+1,12) rep(k,j+1,12){
		int nowsta=(1<<i)|(1<<j)|(1<<k);
		REP(t,4096) if ((!(t&nowsta))&&(C[t]%3==0))
			check[t].push_back(nowsta);
	} int cnt=0;
	REP(t,4096) cnt+=check[t].size();
	// printf("check_cnt=%d\n",cnt);
	scanf("%d",&T);
	FOR(_,1,T){
		REP(i,12) scanf("%d",&A[i]);
		sort(A,A+12);
		REP(i,4096) okay[i]=0;
		REP(i,12) rep(j,i+1,12) rep(k,j+1,12){
			if (A[i]+A[j]>A[k]) {
				// printf("okay : %d %d %d\n",i,j,k);
				okay[(1<<i)|(1<<j)|(1<<k)]=1;
			}
		} REP(i,4096) pre[i]=-1; pre[0]=-2;
		int last=0;
		REP(i,4096) if (pre[i]!=-1) {
			for (auto now:check[i]) if (okay[now]) {
				pre[i|now]=i;
				// pr2(i,12); pr2(i|now,12); puts("<- trans");
			}
			// pr2(i,12);
		}
		REP(i,4096) if (pre[i]!=-1&&C[i]>C[last]) last=i; 
		printf("Case #%d: %d\n",_,C[last]/3);
		for (;last;last=pre[last]) {
			// pr2(last,12); puts(" <- last");
			int x=last^pre[last],cnt=0;
			REP(i,12) if ((x>>i)&1) printf("%d%c",A[i]," \n"[++cnt==3]);
		}
	}
}
/*
100
2 3 5 7 11 12 1000 100000 1000000 10000000 1000000000 10000000000
*/