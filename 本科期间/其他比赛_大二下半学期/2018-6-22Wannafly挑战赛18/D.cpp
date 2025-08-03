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

#define DEBUG1
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

int ax[5]={0,1,-1,0,0};
int ay[5]={0,0,0,1,-1};
int pre[207][207][5],now[207][207][5];
void TaskA(){
    int n,m,t,x1,y1,x2,y2,D;
    int i,j,k,_k,_t;
    scanf("%d%d%d%d%d%d%d%d",&n,&m,&t,&x1,&y1,&D,&x2,&y2);
    now[1][1][0]=1;
    REP(_t,t){
        FOR(i,1,n) FOR(j,1,m) REP(k,5)
            pre[i][j][k]=now[i][j][k],now[i][j][k]=0;
        FOR(i,1,n) FOR(j,1,m) REP(k,5){
            int _i,_j;
            if (max(abs(x1-i),abs(y1-j))<=D&&k){
                _k=k;
                _i=i+ax[_k],_j=j+ay[_k];
                now[_i][_j][_k]+=pre[i][j][k];
                (now[_i][_j][_k]>M)&&(now[_i][_j][_k]-=M);
                _k=0;
                _i=i+ax[_k],_j=j+ay[_k];
                now[_i][_j][_k]+=pre[i][j][k];
                (now[_i][_j][_k]>M)&&(now[_i][_j][_k]-=M);
            }else{
                REP(_k,5){
                    _i=i+ax[_k],_j=j+ay[_k];
                    now[_i][_j][_k]+=pre[i][j][k];
                    (now[_i][_j][_k]>M)&&(now[_i][_j][_k]-=M);
                }
            }
        }
        FOR(i,1,n) FOR(j,1,m) REP(k,5)
            if (now[i][j][k]) debug("%d %d %d : %d\n",i,j,k,now[i][j][k]);
        debug("%d\n",_t);
    }LL ans=0;
    debug("OK? %d %d\n",x2,y2);
    REP(_k,5) ans+=now[x2][y2][_k];
    ans%=M;
    printf("%lld\n",ans);
}
int main() {
    int T=1;
//    scanf("%d",&T);
    while (T--) TaskA();
}
/*
2500 3
*/
