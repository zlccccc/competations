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
char str[maxn];//倒着的

int fa[maxn];
ll val[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    int y=getfa(fa[x]);
    if (fa[x]!=y) val[x]=val[x]*val[fa[x]]%M;
    fa[x]=y;
    return y;
}
int main() {
	int i;
	scanf("%d%d",&n,&m);
	ll Base=powMM(3,n);
	FOR(i,1,n) fa[i]=i,val[i]=1;
	FOR(i,1,m) {
		int op,x,y;
		scanf("%d",&op);
		if (op==1){
			scanf("%d%d",&x,&y);
			assert(fa[x]==x&&fa[y]==y);
			val[y]=val[y]*1*powMM((ll)3,M-2)%M;// 1/3
			val[x]=val[x]*2*powMM((ll)3,M-2)%M;// 2/3
			val[y]=val[y]*powMM((ll)val[x],M-2)%M;// fa
			fa[y]=x;
		} else {
			scanf("%d",&x); int f=getfa(x);
			// printf("%lld %lld %lld",val[x],val[f],Base);
			ll ans=Base*val[x]%M;
			if (x!=f) ans=ans*val[f]%M;
			printf("%lld\n",ans);
		}
	}
}
/*
3 5
2 1
1 2 1
2 1
1 2 3
2 1
*/