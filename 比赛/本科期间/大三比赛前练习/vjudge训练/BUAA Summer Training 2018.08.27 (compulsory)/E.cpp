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

int MIN[maxn*4];
inline void update(int x,int pos,int val,int L,int R){
	if (L==R){MIN[x]=val; return;}
	int mid=(L+R)/2;
	if (pos<=mid) update(x<<1,pos,val,L,mid);
	else update(x<<1|1,pos,val,mid+1,R);
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
inline int query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return MIN[x];
	int mid=(L+R)/2,ret=INF;
	if (l<=mid) min_(ret,query(x<<1,l,r,L,mid));
	if (mid<r) min_(ret,query(x<<1|1,l,r,mid+1,R));
	return ret;
}
char A[maxn];
int cnt[maxn],ans[maxn];
int main() {
	int i,k;
	scanf("%d%d",&n,&k);
	scanf("%s",str+1);
	scanf("%s",A+1);
	FOR(i,1,n){
		cnt[i]=cnt[i-1];
		if (A[i]!=A[i-1]) cnt[i]++;//cnt[i]
	}
	FOR(i,1,n){
		if (str[i]==A[i]) ans[i]=ans[i-1];
		else ans[i]=INF;
		int now=query(1,max(1,i-k+1),i,1,n+1);
		// printf("query: %d - %d\n",max(1,i-k+1),i);
		min_(ans[i],(cnt[i]+now)/2+1);
		update(1,i+1,2*ans[i]-cnt[i+1]+1,1,n+1);
		// printf("update: %d: %d\n",i+1,2*ans[i]-cnt[i+1]+1);
		// printf("%d ",ans[i]);
	}
	printf("%d\n",ans[n]);
}
/*
8 1
BBWBBWBW
WBBWWWBB

10 5
WWWWWWBBBB
BWBWBWBWBW
*/
