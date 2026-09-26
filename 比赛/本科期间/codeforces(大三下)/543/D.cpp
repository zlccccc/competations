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

typedef pair<int,vector<int> > plv;
plv value[maxn];//son_max; node_cnt
ll ans;
int A[maxn];///Cnt:分支
vector<int> could;
vector<int> edge[maxn];//must_in_ans
void dfs(int x,int fa) {
	int MAX=-1;
	for (int v:edge[x]) if (v!=fa) {
			dfs(v,x); MAX=max(MAX,value[v].first);
		} int cnt=0;
	for (int v:edge[x]) if (v!=fa){
		if (value[v].first==MAX) cnt++;
		else {
			for (int y:value[v].second) could.push_back(y);
			ans+=value[v].first;
		}
	} if (cnt) ans+=(ll)(cnt-1)*MAX;
	value[x].first=A[x];
	for (int v:edge[x]) if (v!=fa){
		if (value[v].first==MAX) {
			if (cnt>1) {
				for (int y:value[v].second) could.push_back(y);
				if (MAX<=A[x]) value[x].first=MAX;
			} else {
				if (MAX<=A[x]) value[x].swap(value[v]);//exchange; 替换掉了
			}
		}
	} if (MAX==-1||MAX>=A[x]) value[x].second.push_back(x);
	assert((unsigned)value[x].first==min((unsigned)A[x],(unsigned)MAX));
	// printf("dfs: %d : %d=min(%d,%d); nowans=%lld;\n",x,A[x],MAX,value[x].first,ans);
	// for (int v:value[x].second) printf("%d ",v); puts("");
}
int main() {
	int i;
	int n;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n-1) {
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0);
	for (int x:value[1].second) could.push_back(x);
	ans+=value[1].first;
	sort(could.begin(), could.end());
	printf("%lld %d\n",ans,(int)could.size());
	for (int x:could) printf("%d ",x);
}
/*
*/