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
const LL maxn=3e5+107;
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
// char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

struct node{
	int l,r,MAX;
}T[maxn*40],A[maxn];
int tot;
inline void update(int &x,int pos,int val,int L,int R){
	T[++tot]=T[x]; x=tot;
	if (L==R) {
		T[x].MAX=max(T[x].MAX,val);
		return;
	} int mid=(L+R)/2;
	if (pos<=mid) update(T[x].l,pos,val,L,mid);
	if (mid<pos) update(T[x].r,pos,val,mid+1,R);
	T[x].MAX=min(T[T[x].l].MAX,T[T[x].r].MAX);
}
inline int query(int x,int l,int r,int L,int R){
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].MAX;
	int mid=(L+R)/2,ret=INF;
	if (l<=mid) ret=min(ret,query(T[x].l,l,r,L,mid));
	if (mid<r) ret=min(ret,query(T[x].r,l,r,mid+1,R));
	return ret;
}
vector<int> V;
inline int getid(int x) {return lower_bound(V.begin(),V.end(),x)-V.begin();}
int root[maxn]; int rt;
int main() {
	int i;
	scanf("%d%d%d",&n,&q,&m); V.push_back(0);
	FOR(i,1,m) {
		scanf("%d%d%d",&A[i].l,&A[i].r,&A[i].MAX);
		V.push_back(A[i].r);
	} sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	sort(A+1,A+1+m,[](node i,node j){return i.r<j.r;});
	FOR(i,1,m){
		update(rt,A[i].MAX,A[i].l,1,n);
		root[getid(A[i].r)]=rt;
	} FOR(i,1,q){
		int a,b,l,r; fflush(stdout);
		scanf("%d%d%d%d",&a,&b,&l,&r);
		if (query(root[getid(r+1)-1],a,b,1,n)<l) puts("no");
		else puts("yes");
	}
}
/*
4 1
5
*/
