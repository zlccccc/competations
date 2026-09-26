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
const LL maxn=1e5+107;
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

struct node{
	int l,r,val;
}T[maxn*80]; int tot;
void update(int &x,ll pos,int val,int L,int R) {
	T[++tot]=T[x]; x=tot;
	T[x].val+=val;
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) update(T[x].l,pos,val,L,mid);
	else update(T[x].r,pos,val,mid+1,R);
}
int query(int x,int pos,int L,int R) {
	if (T[x].val==R-L+1) return 0;
	// printf("query: %d: (%d): L,R=%d %d; cnt=%d\n",x,pos,L,R,T[x].val);
	if (L==R) return L;
	int mid=(L+R)/2;
	// printf("query: x=%d; y=%d; cnt=%d; val=%d; L,R=%d %d\n",L,R,cnt,T[T[x].l].val-T[T[y].l].val,L,R);
	if (mid<pos) {
		return query(T[x].r,pos,mid+1,R);
	} else {
		int ret=query(T[x].l,pos,L,mid);
		if (ret) return ret;
		// printf("ret=%d; query\n",ret);
		return query(T[x].r,pos,mid+1,R);
	}
}
int A[maxn];
int root,Root[maxn];
int main(){
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,q,i; tot=0;
		scanf("%d%d",&n,&q);
		FOR(i,1,n) scanf("%d",&A[i]);
		FOR(i,1,n) {
			Root[i]=Root[i-1];
			update(Root[i],A[i],1,1,n+1);
		} root=Root[n];
		int lastans=0;
		FOR(i,1,q) {
			int op;
			scanf("%d",&op);
			if (op==1) {
				int t1,pos;
				scanf("%d",&t1);
				pos=t1^lastans;
				if (A[pos]<=n) {
					update(root,A[pos],-1,1,n+1);
					A[pos]+=10000000;
				}
				// update(root,A[pos],-1,1,MAX);
			} else {
				int t2,t3,r,k;
				scanf("%d%d",&t2,&t3);
				r=t2^lastans; k=t3^lastans;
				int ans_1=query(root,k,1,n+1);
				int ans_2=query(Root[r],k,1,n+1);
				lastans=min(ans_1,ans_2);
				// printf("ans_two=%d %d\n",ans_1,ans_2);
				printf("%d\n",lastans);
			}
		}
	}
}
/*
2
12 6
aaabaabaaaab
*/