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

struct node{
	int x,y;ll w;
}A[maxn];
vector<int> V;
inline int getid(int x){return lower_bound(V.begin(), V.end(), x)-V.begin()+1;}
ll MAX[maxn];
inline int lowbit(int x){return x&-x;}
inline void change(int x,ll val){
	for (;x<=(int)V.size();x+=lowbit(x)) max_(MAX[x],val);
}
inline ll query(int x){
	ll ret=0;
	for (;x;x-=lowbit(x)) max_(ret,MAX[x]);
	return ret;
}
int main() {
	while(~scanf("%d",&n)){
		int i;
		V.clear();
		FOR(i,1,n) {
			scanf("%d%d%lld",&A[i].x,&A[i].y,&A[i].w);
			V.push_back(A[i].y);
		} sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()),V.end());
		FOR(i,1,n) A[i].y=getid(A[i].y);
		FOR(i,1,(int)V.size()) MAX[i]=0;
		sort(A+1,A+1+n,[](node x,node y){
			if (x.x!=y.x) return x.x<y.x;
			return x.y>y.y;
		});
		ll ans=0;
		FOR(i,1,n){
			// printf("%d %d\n",A[i].x,A[i].y);
			if (A[i].x==A[i-1].x&&A[i].y==A[i-1].y) A[i].w+=A[i-1].w;
			ll val=query(A[i].y-1)+A[i].w;
			max_(ans,val);
			change(A[i].y,val);
		}printf("%lld\n",ans);
	}
}
/*
*/
