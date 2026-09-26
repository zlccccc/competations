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

LL inv[maxn];//inverse
LL fac[maxn];//Factorial
LL C(int n,int m){
	// printf("%d %d: %lld\n",n,m,fac[n]*inv[m]%M*inv[n-m]%M);
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int A[maxn];
struct node{
	int pos,val,p;
	node(int pos,int val,int p):pos(pos),val(val),p(p){};
};
vector<node> now; int nowcnt;
int main() {
	int i;int T;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;

	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		now.clear();
		FOR(i,1,m) {
			int op;
			scanf("%d",&op);
			if (op==1) {
				int l,r,val;
				scanf("%d%d%d",&l,&r,&val);
				now.push_back(node(l,val,nowcnt-1));
				now.push_back(node(r+1,M-val,nowcnt-1));
			} if (op==2) nowcnt++;
			if (op==3){
				int l,r;
				scanf("%d%d",&l,&r); l--;
				ll ans=0;
				for (auto x:now){
					if (l-x.pos>=0) {
						// printf("- %d %d   %d\n",nowcnt-x.p,l-x.pos,l-x.pos);
						add_(ans,(ll)x.val*(M-C(nowcnt-x.p+l-x.pos,l-x.pos))%M);
					}
					if (r-x.pos>=0) {
						// printf("+ %d %d   %d\n",nowcnt-x.p,r-x.pos,r-x.pos);
						add_(ans,(ll)x.val*C(nowcnt-x.p+r-x.pos,r-x.pos)%M);
					}
				} printf("%lld\n",ans);
			}
		}
	}
}
/*
1 100000 7 1 1 3 1 2 3 2333 6666 2 3 2333 6666 2 3 2333 6666
 
2
2 5
1 1 1 1
2
3 1 2
2
3 1 2

5 7
1 1 3 2
3 2 3
2
2
1 1 3 1
2
3 1 3
ans
4
36

0 0 0
2 2 2
2 4 6
2 6 12
3 7 13
3 10 23

*/
