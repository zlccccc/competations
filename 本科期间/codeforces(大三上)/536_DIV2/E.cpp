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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];

multiset<pii> Q;
//只能使得下一个时间不能选啊
vector<pii> ST[maxn],ED[maxn];
int nxt[maxn],val[maxn],posnxt[maxn];
ll ans[maxn][207];//ans
int main() {
	int i,j,k;
	scanf("%d%d%d",&n,&m,&k);
	FOR(i,1,k) {
		int s,t,d,w;
		scanf("%d%d%d%d",&s,&t,&d,&w);
		ST[s].push_back(make_pair(w,d));
		ED[t+1].push_back(make_pair(w,d));
	} FOR(i,1,n){
		for (pii now:ST[i]) Q.insert(now);
		for (pii now:ED[i]) Q.erase(Q.lower_bound(now));
		if (!Q.size()) continue;
		else {
			pii now=*Q.rbegin();
			nxt[i]=now.second; val[i]=now.first; 
		}
	}
	rFOR(i,1,n) if (!val[i]) posnxt[i]=posnxt[i+1]; else posnxt[i]=i;
	// FOR(i,1,n) printf("%d %d  posnxt=%d\n",nxt[i],val[i],posnxt[i]);
	rFOR(i,1,n) {
		FOR(j,0,m) ans[i][j]=ans[posnxt[nxt[i]+1]][j]+val[i];
		FOR(j,1,m) ans[i][j]=min(ans[i][j],ans[posnxt[i+1]][j-1]);
		// printf("%d :",i); FOR(j,0,m) printf("%lld ",ans[i][j]); puts("");
	} printf("%lld\n",ans[1][m]);
}
/*
1
674719119
995154324 384336384
*/