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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a; }
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int A[105];
LL f[maxn],g[maxn];
LL C(int x,int y){
    LL ret=1,i;
    FOR(i,x-y+1,x) ret*=i;
    FOR(i,1,y) ret/=i;
    return ret;
}
LL get_0(int l,int t){
    if (l==0) return 0;
    int i,j,_i,_j;
    LL ret=get_0(l-1,t);
    rep(i,1,16) if (A[i]!=t){//this
        A[i]++;
        FOR(j,0,l) f[j]=g[j]=0; f[0]=1;
        REP(_i,16){
            FOR(j,0,l) g[j]=f[j],f[j]=0;
            FOR(j,0,l)
            FOR(_j,0,t-A[_i])
                f[j+_j]+=g[j]*C(j+_j,j);
        }ret+=f[l-1];
        A[i]--;
    }
//    printf("len %d : %lld\n",l,ret);
    return ret;
}
LL solve(LL k,int t){
    int i,_i,j,_j,l;
    bool havenum=0;
    LL ret=0;
    REP(i,16) A[i]=0;
    rREP(l,10){
        REP(i,16) if (A[i]!=t){
            if (!i&&!havenum) f[l]=get_0(l,t);
            else {
                A[i]++;
                FOR(j,0,l) f[j]=g[j]=0;
                f[0]=1;
                REP(_i,16){
                    FOR(j,0,l) g[j]=f[j],f[j]=0;
                    FOR(j,0,l)
                    FOR(_j,0,t-A[_i])
                        f[j+_j]+=g[j]*C(j+_j,j);
                }
            }
            if (f[l]>=k) break;
//            printf("%-2d  :%I64d;  i=%d %d\n",l,f[l],i,A[i]);
            if (i||havenum) A[i]--; k-=f[l];
        }if (i) havenum=1;
        ret=ret*16+i;
    }
    printf("%I64x\n",ret);
    return ret;
}
int main() {
    LL k;int t;
    LL i,j;
//    solve(17,1);
//    printf("%I64x ",solve(1000000,2));
//    t=1;
//    solve(239,1);
//    solve(240,1);
//    solve(241,1);
//    solve(242,1);
//    FOR(i,1,10000) if (solve(i,t)+1!=solve(i+1,t)){
//        FOR(j,solve(i,t)+1,solve(i+1,t)-1) printf("%I64x ",j);puts("");
//    }
    scanf("%I64d%d",&k,&t);
    solve(k,t);
    return 0;
}
/*
*/
