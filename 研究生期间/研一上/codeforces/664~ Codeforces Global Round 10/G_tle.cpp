
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

int value[1<<20|7][21];//final_value=x;k=ans;last-position
char s[27],t[27];
int pos[27],fin[27];
int c[maxn][2];
int main() {
	int n,i,m,k,j; scanf("%d%d%d",&n,&m,&k);
	scanf("%s%s",s+1,t+1);
	FOR(i,1,n) scanf("%d%d",&c[i][0],&c[i][1]);
	memset(value,0x3f,sizeof(value));
	//find
	FOR(i,1,k) pos[i]=i;
	rFOR(i,1,n) {
		int x=c[i][0],y=c[i][1];
		swap(pos[x],pos[y]);
	} FOR(i,1,n) {
		int now=0,x=c[i][0],y=c[i][1];
		FOR(j,1,k) fin[pos[j]]=j;
		FOR(j,1,k) now=(now<<1)|(s[fin[j]]-'0');
		// pr2(now,k); puts("<- now");
		min_(value[now][k],i);//n same
		swap(pos[x],pos[y]);
	}
	rFOR(j,1,k) {
		REP(i,(1<<k)) {
			// if (value[i][j]!=INF) {
			// 	printf("j=%d ",j); pr2(i,k); puts("<- contri");
			// 	pr2(i^(1<<(j-1)),k); printf("%d ",value[i][j]); puts("<- upd");
			// }
			int t;
			REP(t,k) min_(value[i^(1<<t)][j-1],value[i][j]);
		}
	} pair<int,pair<int,int> > ans=make_pair(0,make_pair(0,0));
	FOR(i,1,k) pos[i]=i;
	rFOR(i,1,n) {
		int x=c[i][0],y=c[i][1];
		swap(pos[x],pos[y]);
	}
	FOR(i,1,n) {
		int now=0,x=c[i][0],y=c[i][1];
		swap(pos[x],pos[y]);
		FOR(j,1,k) fin[pos[j]]=j;
		FOR(j,1,k) now=(now<<1)|(t[fin[j]]-'0');
		// pr2(now,k); puts("<- t");
		FOR(j,0,k) {
			// if (value[now][j]!=INF) printf("%d-%d: pos=%d\n",value[now][j],i,j);
			if (value[now][j]<=i-m+1) ans=max(ans,make_pair(j,make_pair(value[now][j],i)));
		}
	}
	printf("%d\n",ans.first);
	printf("%d %d\n",ans.second.first,ans.second.second);
}
/*
4
2 6 7 8
^Z
*/