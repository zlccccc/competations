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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

LL f[57],g[57];
typedef pair<ll,ll> pll;
pll A[57];
int n;
int check(LL x){
//    debug("check:%I64d \n",x);
    int l,r,i,k;l=r=1;
    FOR(i,1,n) g[i]=-INFF;g[0]=0;
    LL all=0;
    while (l<=n){//k:not use!
        while (r<=n&&A[r].first==A[l].first) r++;
        //count=r-l
        FOR(i,1,n) f[i]=g[i];
        LL now=0;
        FOR(k,1,r-l){//k:used
            now+=A[k+l-1].first+A[k+l-1].second*x;
            for(i=0;l-1-i-i>=k;i++) {
                g[i+k]=max(g[i+k],f[i]+now);
            }
        }all+=now;
        l=r;
//        FOR(i,0,l/2) printf("%lld ",g[i]);puts("");printf("all,now=%I64d %I64d\n",all,now);
    }LL ans=INFF;
    FOR(i,0,n/2) ans=min(ans,all-g[i]);
//    debug("all=%I64d; ans=%I64d\n",all,ans);
    if (ans<=0) return 1;
    return 0;
}
int TaskA(){
    int i,j,k;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%I64d",&A[i].first),A[i].first*=1000;
    FOR(i,1,n) scanf("%I64d",&A[i].second),A[i].second*=-1;
    sort(A+1,A+n+1); reverse(A+1,A+1+n);
    LL l=0,r=INF*1000ll;
    while (l+1<r){
        LL mid=(l+r)/2;
        if (check(mid)) r=mid;
        else l=mid;
    }printf("%I64d\n",r);
    return 0;
}
void initialize(){
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
