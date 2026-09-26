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
const LL maxn=1e6+7;
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

pii A[maxn];
int X[1007][1007],fa[2007];
int XOR[2007];//to upper
vector<pair<int,pii> > Check;
inline int getfa(int x) {
	if (fa[x]==x) return x;
	int y=getfa(fa[x]);
	if (fa[x]!=y) XOR[x]^=XOR[fa[x]];
	fa[x]=y;
	return y;
}
int dfs(int x,int base,int Xor) {
	for (auto now:Check) {
		// printf("dfs: x=%d %d %d ; %d<=%d; %d>=%d\n",x,base,Xor,
		// 	now.second.first,((now.first^x)&Xor)+max(0,base*2-1),
		// 	now.second.second,((now.first^x)&Xor));
		if (now.second.first >((now.first^x)&Xor)+max(0,base*2-1)||
		    now.second.second<((now.first^x)&Xor)) return 0;
	}
	if (base==0) return x;
	int ret=dfs(x,base/2,Xor|base);
	if (ret) return ret;
	ret=dfs(x|base,base/2,Xor|base);
	if (ret) return ret;
	return 0;
}
int main() {
	int T,_; scanf("%d",&T);
	FOR(_,1,T) {
		int i,j,n,m;
		scanf("%d%d",&n,&m);
		FOR(i,1,n+m) scanf("%d%d",&A[i].first,&A[i].second);
		FOR(i,1,n+m) fa[i]=i,XOR[i]=0;
		FOR(i,1,n) FOR(j,1,m) {
			scanf("%d",&X[i][j]);
			if (X[i][j]==-1) continue;
			int x=getfa(i),y=getfa(j+n);
			if (x==y) continue;
			fa[x]=y; XOR[x]=XOR[i]^X[i][j]^XOR[j+n];
		}
		FOR(i,1,n+m) if (getfa(i)==i) { //直接dfs即可!
			Check.clear();
			FOR(j,1,n+m) if (getfa(j)==i){
				Check.push_back(make_pair(XOR[j],A[j]));
				// printf(" XOR %d - %d : %d; %d %d\n",j,i,XOR[j],A[j].first,A[j].second);
			}
			XOR[i]=dfs(0,1<<29,0);//haveans
			// printf("XOR %d : %d\n",i,XOR[i]);
		} FOR(i,1,n+m) if (fa[i]!=i) XOR[i]^=XOR[fa[i]];
		bool okay=1;
		FOR(i,1,n) FOR(j,1,m) if (X[i][j]!=-1&&X[i][j]!=(XOR[i]^XOR[j+n])) okay=0;
		FOR(i,1,n+m) if (!(A[i].first<=XOR[i]&&XOR[i]<=A[i].second)) okay=0;
		if (okay) {
			puts("YES");
			FOR(i,1,n) printf("%d ",XOR[i]); puts("");
			FOR(i,n+1,n+m) printf("%d ",XOR[i]); puts("");
		} else puts("NO");
	}
}
/*
10
3 3
2 4
3 4
4 6
1 3
4 7
6 8
2 7 4
5 0 3
4 1 2
2 2
4 6
5 7
3 9
2 4
3 6
6 5
3 3
2 4
3 4
4 6
1 3
4 7
6 8
2 7 4
5 -1 3
4 1 2

3 3
2 4
3 4
4 6
1 3
4 7
6 8
-1 -1 -1
-1 -1 -1
-1 -1 -1
*/
