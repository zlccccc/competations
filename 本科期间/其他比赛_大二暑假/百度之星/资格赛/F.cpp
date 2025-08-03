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
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

priority_queue<int> Q;
int fa[maxn],Fa[maxn];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}

int ans[maxn];
struct node{
	int u,v,w; char c;
}edge[maxn];
int now;
void solve(char A,char B){
	int noww=now;
	int i,T=0;
	while (Q.size()) Q.pop();
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,m) if (edge[i].c==A||edge[i].c==B){
		int x=getfa(edge[i].u),y=getfa(edge[i].v);
		if (x!=y) {
			noww+=edge[i].w; fa[x]=y;
		} else Q.push(-edge[i].w);
	} else Q.push(-edge[i].w);
	FOR(i,1,n) if (fa[i]==i) T++;
	if (T!=1) return;
	FOR(i,n-1,m){
		if (i!=n-1){
			noww-=Q.top(); Q.pop();
		} min_(ans[i],noww);
	}
}
int main() {
	int T,_T;
	scanf("%d",&T);
	FOR(_T,1,T){
		int i;
		scanf("%d%d",&n,&m);
		FOR(i,1,m){
			scanf("%d%d%d%*c%c",&edge[i].u,&edge[i].v,&edge[i].w,&edge[i].c);
		} sort(edge+1,edge+1+m,[](node A,node B){
			return A.w<B.w;
		});
		FOR(i,1,m) ans[i]=INF;
		solve('R','G');
		solve('B','G');
		printf("Case #%d:\n",_T);
		FOR(i,1,m){
			if (ans[i]!=INF) printf("%d\n",ans[i]);
			else puts("-1");
		}
	}
}
/*

*/
