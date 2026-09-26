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
const LL maxn=1e4+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

ll add(ll x,ll y) {return min(INFF,x+y);}
ll mul(ll x,ll y) {return min(INFF/y+1,x)*y;}
vector<int> V;
int getid(int x) {
	return lower_bound(V.begin(),V.end(),x)-V.begin();
} vector<int> ans;
int A[maxn];
ll Cnt[maxn];
ll base[maxn];
int main() {
	int _,T; scanf("%d",&T);
	FOR(_,1,T) {
		int n; ll k;
		int i;
		scanf("%d%*d%lld",&n,&k);
		FOR(i,1,n) scanf("%d",&A[i]);
		V.clear(); ans.clear();
		FOR(i,1,n) V.push_back(A[i]);
		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()),V.end());
		FOR(i,1,n) A[i]=getid(A[i]);//start_position
		FOR(i,1,n) base[i]=1;//base
		while (k>0) {
			REP(i,(int)V.size()) Cnt[i]=0;
			FOR(i,1,n) {
				Cnt[A[i]]=add(Cnt[A[i]],mul(base[i],1ll<<min(62,n-i)));
			}
			int y;
			REP(y,(int)V.size()) {
				if (Cnt[y]<k) k-=Cnt[y];
				else {
					ans.push_back(V[y]);
					rFOR(i,1,n) {
						if (A[i]==y) base[i+1]=base[i],k-=base[i];
						else base[i+1]=0;
					} base[1]=0;
					FOR(i,1,n) base[i]=add(base[i],base[i-1]);
					break;
				}
			}
			// REP(i,(int)V.size()) printf("%lld ",Cnt[i]);  puts(" <- CNT");
			// FOR(i,1,n) printf("%lld ",base[i]); puts("<- base");
			// printf("k=%lld; y=%d\n",k,y);
			if (y==(int)V.size()) break;//ending
		} for (int v:ans) printf("%d ",v); puts("");
	} return 0;
}
/*
*/
