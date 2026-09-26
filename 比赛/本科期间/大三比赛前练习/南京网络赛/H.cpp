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
const LL maxn=6e5+7;
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

struct node{
	int son[2],sum;
}T[maxn*31];
int root[maxn],tot;
void insert(int &x,int val,int dep=0){
	if (dep==31) return;
	if (!x) x=++tot; T[x].sum++;
	int c=(val>>dep)&1;
	insert(T[x].son[c],val,dep+1);
}
int query(int x,int k,int val,int dep=0){
	if (!x) return 0;
	if (dep==k) return T[x].sum;
	int c=(val>>dep)&1;
	return query(T[x].son[c],k,val,dep+1);
}
void merge(int &x,int &y){
	if (!x||!y) {x|=y; return;}
	T[x].sum+=T[y].sum;
	merge(T[x].son[0],T[y].son[0]);
	merge(T[x].son[1],T[y].son[1]);
}
void update(int x){
	if (!x) return;
	swap(T[x].son[0],T[x].son[1]);
	update(T[x].son[0]);
}
int fa[maxn];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int A[maxn];
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&A[i]),fa[i]=i;
	FOR(i,1,n) insert(root[i],A[i]);
	while (m--){
		int op,u,v,k,val;
		scanf("%d",&op);
		if (op==1){
			scanf("%d%d",&u,&v);
			int x=getfa(u),y=getfa(v);
			if (x==y) continue;
			merge(root[y],root[x]); fa[x]=y;
		}
		if (op==2){
			scanf("%d",&u);
			int x=getfa(u);
			update(root[x]);
		}
		if (op==3){
			scanf("%d%d%d",&u,&k,&val);
			int x=getfa(u);
			printf("%d\n",query(root[x],k,val));
		}
	}
}
/*
3 100
2 3 4
3 1 2 2
3 3 1 0
1 1 3
3 3 1 0
2 2
1 2 3
3 3 1 0
*/
