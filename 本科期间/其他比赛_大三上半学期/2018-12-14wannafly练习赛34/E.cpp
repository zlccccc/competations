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

inline int getg(int x){
	int ret=0,dep=0;
	while (x) dep++,ret+=x%10*dep,x/=10;
	if (ret<10) return ret;
	return getg(ret);
}
int g[10007];
struct node{
	ll ans[17];
	node(){memset(ans,0,sizeof(ans)); ans[0]=-1;}
} f[27][10007];//位,already,ans
int value[27];
ll all=0;
node calc(int x,int prev,int flag){
	node ret; ret.ans[0]=0;
	if (x==0) {ret.ans[g[prev]]++; return ret;}
	if (!flag&&f[x][prev].ans[0]!=-1)
		return f[x][prev];
	int i,j,maxi=9;
	if (flag) maxi=min(maxi,value[x]);
	FOR(i,0,maxi){
		node nxt=calc(x-1,prev+i*x,flag&&(i==maxi));
		REP(j,11) ret.ans[j]+=nxt.ans[j];
	}
	if (!flag) f[x][prev]=ret;
	return ret;
}
node calc(LL x) {
    int length=0;
    while (x) value[++length]=x%10,x/=10;
    return calc(length,0,1);
} 
node calc(ll l,ll r){
	node ans=calc(r); int j;
	node more=calc(l-1);
	REP(j,11) ans.ans[j]-=more.ans[j];
	return ans;
}
int main() {
	int _,T; scanf("%d",&T);
	FOR(_,1,10000) g[_]=getg(_);
	FOR(_,1,T){
		ll l,r; int i;
		scanf("%lld%lld",&l,&r);
		node ans=calc(l,r);
		printf("Case #%d: ",_);
		FOR(i,1,9) printf("%lld%c",ans.ans[i]," \n"[i==9]);
	}
}
/*
*/
