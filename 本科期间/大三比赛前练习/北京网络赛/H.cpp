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
template<typename T>inline void add_(T &A,ll B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b,ll MOD=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%MOD)
		if (b&1) ret=(LL)ret*a%MOD;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

double A[maxn],ans[maxn],B[maxn],C[maxn];//C:前缀和
int id[maxn];
inline int seg(double x) {
	if (x<0) return -1; return 1;
}
int main() {
	int T,_t; scanf("%d",&T);
	FOR(_t,1,T) {
		int k,R,i;
		scanf("%d%d",&n,&k);
		scanf("%d",&R);
		FOR(i,1,k) scanf("%lf",&B[i]);
		while (n--) {
			FOR(i,1,k) scanf("%lf",&A[i]),A[i]-=B[i];//dis
			FOR(i,1,k) id[i]=i;
			sort(id+1,id+1+k,[&](int x,int y){
				return abs(A[x])>abs(A[y]);
			});
			FOR(i,1,k) C[i]=abs(A[id[i]])+C[i-1];
			// FOR(i,1,k) printf("%d(%f,%f) \n",id[i],A[id[i]],C[i]);
			int l=1,r=k+1;
			while (l+1<r){
				int mid=(l+r)/2;
				// printf("chk: %d %d(|%d|) : %f %f\n",l,r,mid,abs(A[id[mid]])*mid,C[mid]-R);
				if (abs(A[id[mid]])*mid>C[mid]-R) l=mid;
				else r=mid;
			}
			// printf("l=%d r=%d\n",l,r);
			FOR(i,1,l) ans[id[i]]=A[id[i]]-seg(A[id[i]])*(C[l]-R)/l;
			FOR(i,r,k) ans[id[i]]=0;
			FOR(i,1,k) printf("%f%c",ans[i]+B[i]," \n"[i==k]);
		}
	}
}
/*
1
2 2
2
0 0
2 2
2 6
*/
