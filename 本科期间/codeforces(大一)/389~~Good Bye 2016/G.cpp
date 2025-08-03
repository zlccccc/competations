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
const LL M=1e9+7;
const LL maxn=1e6+7;
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

//a+b-c=now
ll f[127][127][2];
ll solve(int a,int b,int cnt,ll now){
    if (now<0) return 0;
    int t=0,i,j,k,l,p;
    while ((1ll<<t)<=now) t++;
//    if (t>max(a,b)+1) return 0;
    FOR(l,0,cnt) f[0][l][0]=f[0][l][1]=0;
    f[0][0][0]=1;
    REP(k,t){
        FOR(l,0,cnt) f[k+1][l][1]=f[k+1][l][0]=0;
        int maxi=(k<a),maxj=(k<b),o=(now>>k)&1;
        FOR(i,0,maxi) FOR(j,0,maxj) FOR(p,0,1){
            int O=(i+j+p-o); if (O<0||(O&1)) continue;
            FOR(l,0,cnt) f[k+1][l+i+j][O>>1]+=f[k][l][p];
        }
    }
//    FOR(k,0,t) {
//        FOR(l,0,cnt) debug("%d-%d  ",f[k][l][0],f[k][l][1]);deputs("");
//    }
//    debug("%d %d %d %I64d:  %I64d; t=%d\n",a,b,cnt,now,f[t][cnt][0],t);
    return f[t][cnt][0];
}
int TaskA(){
    int m,i,j,k; ll n;
    scanf("%I64d",&n);
    ll ans=0;
    FOR(i,0,50) FOR(j,0,50){
        ll mul=(1ll<<(i+1))-1+(1ll<<(j+1))-1-1;
        if (n<mul) break;
        ll now=n%mul-(1ll<<j)+1;
        if (now<0) continue;
        //a<(1<<i); b<(1<<j)
        //a+b-popcnt=now
        for (k=now&1;k<=(i+j);k+=2)
            ans+=solve(i-1,j-1,k,(now+k)/2);
    }printf("%I64d\n",ans);
    return 0;
}
void initialize(){}
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
