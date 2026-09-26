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
inline ll poww(ll a, ll b,ll M) {
	ll ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

vector<int> ans,edge[maxn];
int col[maxn];
int head;
bool used[maxn][2];
void dfs(int x,int fa) {
	// printf("dfs:x=%d\n",x);
	if (head) return;
	col[x]=col[fa]^1;
	for (int v:edge[x]) {
		if (v!=fa) {
			if (col[v]==-1) dfs(v,x);
			else if (col[v]==col[x]) head=x;
		}
	}
}
int S[maxn],top;
bool instack[maxn];
void getans(int x,int col) {
	// printf("getans:x=%d\n",x);
	if (head==x&&col) {
		int i; head=0; printf("%d\n",top);
		FOR(i,1,top) printf("%d%c",S[i]," \n"[i==top]);
	} S[++top]=x; instack[x]=1;
	if (!head) return; used[x][col]=1;
	for (int v:edge[x]) if (!instack[v]||v==head)
		if (!used[v][col^1]) getans(v,col^1);
	if (S[top]==x) top--; instack[x]=0;
}
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} FOR(i,1,n) col[i]=-1; col[0]=1;
	dfs(1,0);
	if (head) getans(head,0);
	else {
		puts("0");
		FOR(i,1,n) printf("%d%c",col[i]," \n"[i==n]);
	}
}
/*
4 4
1 2
2 3
3 4
1 4
*/
