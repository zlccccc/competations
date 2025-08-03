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

int A[maxn];
int MIN[maxn*4],DEL[maxn*4],SUM[maxn*4];
inline void build(int x,int l,int r) {
	if (l==r) {
		MIN[x]=A[l]; SUM[x]=DEL[x]=0;
		return;
	} int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
	SUM[x]=DEL[x]=0;
}
void update(int x,int l,int r,int val,int L,int R) {
	if (l<=L&&R<=r) {
		DEL[x]+=val; MIN[x]-=val;//DEL:this; lazy
		if (MIN[x]==0) {
			if (L==R) {
				MIN[x]=A[L]; SUM[x]++;
				return;
			} int mid=(L+R)/2;
			if (DEL[x]) {
				MIN[x<<1]-=DEL[x]; DEL[x<<1]+=DEL[x];
				MIN[x<<1|1]-=DEL[x]; DEL[x<<1|1]+=DEL[x];
				DEL[x]=0;
			}
			update(x<<1,l,r,0,L,mid);
			update(x<<1|1,l,r,0,mid+1,R);
			MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
			SUM[x]=SUM[x<<1]+SUM[x<<1|1];
		}
		// printf("x=%d; %d-%d: Min=%d Sum=%d\n",x,l,r,MIN[x],SUM[x]);
		return;
	} int mid=(L+R)/2;
	if (DEL[x]) {
		MIN[x<<1]-=DEL[x]; DEL[x<<1]+=DEL[x];
		MIN[x<<1|1]-=DEL[x]; DEL[x<<1|1]+=DEL[x];
		DEL[x]=0;
	}
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
	SUM[x]=SUM[x<<1]+SUM[x<<1|1];
}
int query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {
		return SUM[x];
	} int mid=(L+R)/2,ret=0;
	if (l<=mid) ret+=query(x<<1,l,r,L,mid);
	if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
	return ret;
}
char o[20];
int main(){
	int n,m;
	while (~scanf("%d%d",&n,&m)){
		int i;
		FOR(i,1,n) scanf("%d",&A[i]);
		build(1,1,n);
		FOR(i,1,m) {
			scanf("%s",o);
			int l,r; scanf("%d%d",&l,&r);
			if (o[0]=='a') update(1,l,r,1,1,n);
			else printf("%d\n",query(1,l,r,1,n));
		}
	}
}
/*
5 12
1 5 2 4 3
add 1 4
query 1 4
add 2 5
query 2 5
add 3 5
query 1 5
add 2 4
query 1 4
add 2 5
query 2 5
add 2 2
query 1 5
*/
Select Code
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

int A[maxn];
int MIN[maxn*4],DEL[maxn*4],SUM[maxn*4];
inline void build(int x,int l,int r) {
	if (l==r) {
		MIN[x]=A[l]; SUM[x]=DEL[x]=0;
		return;
	} int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
	SUM[x]=DEL[x]=0;
}
void update(int x,int l,int r,int val,int L,int R) {
	if (l<=L&&R<=r) {
		DEL[x]+=val; MIN[x]-=val;//DEL:this; lazy
		if (MIN[x]==0) {
			if (L==R) {
				MIN[x]=A[L]; SUM[x]++;
				return;
			} int mid=(L+R)/2;
			if (DEL[x]) {
				MIN[x<<1]-=DEL[x]; DEL[x<<1]+=DEL[x];
				MIN[x<<1|1]-=DEL[x]; DEL[x<<1|1]+=DEL[x];
				DEL[x]=0;
			}
			update(x<<1,l,r,0,L,mid);
			update(x<<1|1,l,r,0,mid+1,R);
			MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
			SUM[x]=SUM[x<<1]+SUM[x<<1|1];
		}
		// printf("x=%d; %d-%d: Min=%d Sum=%d\n",x,l,r,MIN[x],SUM[x]);
		return;
	} int mid=(L+R)/2;
	if (DEL[x]) {
		MIN[x<<1]-=DEL[x]; DEL[x<<1]+=DEL[x];
		MIN[x<<1|1]-=DEL[x]; DEL[x<<1|1]+=DEL[x];
		DEL[x]=0;
	}
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
	SUM[x]=SUM[x<<1]+SUM[x<<1|1];
}
int query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {
		return SUM[x];
	} int mid=(L+R)/2,ret=0;
	if (l<=mid) ret+=query(x<<1,l,r,L,mid);
	if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
	return ret;
}
char o[20];
int main(){
	int n,m;
	while (~scanf("%d%d",&n,&m)){
		int i;
		FOR(i,1,n) scanf("%d",&A[i]);
		build(1,1,n);
		FOR(i,1,m) {
			scanf("%s",o);
			int l,r; scanf("%d%d",&l,&r);
			if (o[0]=='a') update(1,l,r,1,1,n);
			else printf("%d\n",query(1,l,r,1,n));
		}
	}
}
/*
5 12
1 5 2 4 3
add 1 4
query 1 4
add 2 5
query 2 5
add 3 5
query 1 5
add 2 4
query 1 4
add 2 5
query 2 5
add 2 2
query 1 5
*/