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
const LL maxn=1e5+7;
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

//合法方案: 对于每个质因子, 至少存在一个MAX
int mark[maxn],tot;
int p[maxn],cnt[maxn];
//f[i][j]: i; cnt=j; ans=more-notok(next)
//考虑有多少个数字(假设k+1个); now=C^k-C^(k-1); 合并的时候要乘起来
ll fac[maxn],inv[maxn];
map<int,int> MP;//容斥
struct node {
	int x,y;
	node(int _x=0,int _y=0):x(_x),y(_y){};
};
vector<node> V,X;//POW,CNT
LL C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
inline int poww(int a,int b,int M) {
	int ret=1;
	for (; b; b>>=1,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int main() {
	int n,i,j;
    fac[0]=1;
    FOR(i,1,100000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,100000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,100000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	scanf("%d",&n);
	FOR(i,2,n) if (!mark[i]) {
		for (j=i; j<=n; j+=i) mark[j]=1;
		for (j=n/i; j; j/=i) cnt[tot]++;
		p[tot++]=i;
	} REP(i,tot) MP[cnt[i]]++;
	// REP(i,tot) printf("%d: %d\n",p[i],cnt[i]);
	// for (auto now:MP) printf("MP %d : %d\n",now.first,now.second);
	V.push_back(node(1,1));
	for (auto A:MP) {
		int x=A.first,y=A.second;
		X.clear();
		for (auto A:V) {
			int base=1;
			rFOR(i,0,y) {
				X.push_back(node((ll)A.x*poww(x,y-i,M-1)%(M-1)*poww(x+1,i,M-1)%(M-1),
				                 (ll)A.y*C(y,i)%M*base%M));
				base=M-base;
			}
		} V.swap(X);
	} int ans=0;
	for (auto now:V) {
		add_(ans,(ll)powMM(2,now.x)*now.y%M);
	} printf("%d\n",ans);
}
/*
*/