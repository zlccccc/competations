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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1000+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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

const int N=70;
struct matrix {
	ll A[N][N];
	matrix() {memset(A,0x3f,sizeof(A));}
} base;
int id[1<<8|7],rid[1<<8|7],cnt=0;
int popcnt(int x) {
	int ret=0;
	while (x) ret+=x&1,x>>=1;
	return ret;
} int c[maxn];
void bfs(int x,int k) {
	int sta,i; base=matrix();
	REP(sta,(1<<k)) if (popcnt(sta)==x) id[sta]=cnt,rid[cnt++]=sta;
	REP(sta,(1<<k)) if (popcnt(sta)==x) {
		if (sta&1) {
			FOR(i,1,k) if (!((sta>>i)&1)) {
				int nxtsta=(sta|(1<<i))>>1;
				base.A[id[sta]][id[nxtsta]]=c[i];
				// pr2(sta,k); debug(" to "); pr2(nxtsta<<1,k+1); debug(" : %d   (%d -> %d)\n",c[i],id[sta],id[nxtsta]);
			}
		} else {
			int nxtsta=sta>>1;
			base.A[id[sta]][id[nxtsta]]=0;
			// pr2(sta,k); debug(" to "); pr2(nxtsta<<1,k+1); debug(" : 0   (%d -> %d)\n",id[sta],id[nxtsta]);
		}
	}
	debug("cnt=%d\n",cnt);
}
matrix mul(matrix &A,matrix &B) {
	matrix C; int i,j,k;
	REP(i,N) REP(j,N) REP(k,N)
		min_(C.A[i][j],A.A[i][k]+B.A[k][j]);
	return C;
}
matrix poww(matrix a,ll b) {
	matrix ret;
	int i; REP(i,N) ret.A[i][i]=0;
	for (; b; b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
}
pair<int,int> p[maxn];
ll now[maxn],nxt[maxn];
int TaskA() {
	int i;
	int x,k,q;
	scanf("%d%d%d%d",&x,&k,&n,&q);
	FOR(i,1,k) scanf("%d",&c[i]);
	bfs(x,k); int nowpos=1;
	FOR(i,1,q) scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+1+q); p[++q]=make_pair(n,0);
	REP(i,N) now[i]=INFF; now[id[(1<<x)-1]]=0;
	FOR(i,1,q){
		int nxtpos=min(p[i].first,n-x+1),j,k;
		// printf("i=%d nowpos=%d; nxtpos=%d\n",i,nowpos,nxtpos);
		matrix trans=poww(base,nxtpos-nowpos); nowpos=nxtpos;
		REP(j,N) nxt[j]=INFF; 
		// REP(j,4) {REP(k,4) debug("%-10d ",trans.A[j][k]);puts("");}
		REP(j,N) REP(k,N) min_(nxt[k],now[j]+trans.A[j][k]);
		REP(j,N) now[j]=nxt[j];
		REP(j,N) if (rid[j]&1) now[j]+=p[i].second;
		// REP(j,N) if (rid[j]) {pr2(rid[j],3); printf("%lld  <- %d\n",now[j],i);}
	}printf("%lld\n",now[id[(1<<x)-1]]);
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
*/
