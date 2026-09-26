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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int A[1007][1007];
int LD[1007][1007],RD[1007][1007],LU[1007][1007],RU[1007][1007];
int D[1007][1007],U[1007][1007],R[1007][1007],L[1007][1007],F[1007][1007];
int solve(){
    int n,m;
    int i,j,k;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,m)
        scanf("%d",&A[i][j]);
    FOR(i,0,n) RD[i][0]=RD[i][m+1]=-INF;
    FOR(j,0,m) RD[0][j]=RD[n+1][j]=-INF;
    RD[1][1]=A[1][1];
    FOR(i,1,n) FOR(j,1,m) if (i!=1||j!=1)
        RD[i][j]=max(RD[i][j-1],RD[i-1][j])+A[i][j];
    FOR(i,0,n) LD[i][0]=LD[i][m+1]=-INF;
    FOR(j,0,m) LD[0][j]=LD[n+1][j]=-INF;
    LD[1][m]=A[1][m];
    FOR(i,1,n) rFOR(j,1,m) if (i!=1||j!=m)
        LD[i][j]=max(LD[i][j+1],LD[i-1][j])+A[i][j];
    FOR(i,0,n) RU[i][0]=RU[i][m+1]=-INF;
    FOR(j,0,m) RU[0][j]=RU[n+1][j]=-INF;
    RU[n][1]=A[n][1];
    rFOR(i,1,n) FOR(j,1,m) if (i!=n||j!=1)
        RU[i][j]=max(RU[i][j-1],RU[i+1][j])+A[i][j];
    FOR(i,0,n) LU[i][0]=LU[i][m+1]=-INF;
    FOR(j,0,m) LU[0][j]=LU[n+1][j]=-INF;
    LU[n][m]=A[n][m];
    rFOR(i,1,n) rFOR(j,1,m) if (i!=n||j!=m)
        LU[i][j]=max(LU[i][j+1],LU[i+1][j])+A[i][j];
    int ans=-INF;
    FOR(j,1,m){
        int down=-INF;
        FOR(i,1,n){
            U[i][j]=max(RU[i][j-1]+LU[i][j],RU[i][j]+LU[i][j+1]);
            ans=max(ans,down+U[i][j]);
            D[i][j]=max(RD[i][j-1]+LD[i][j],RD[i][j]+LD[i][j+1]);
            down=max(down+A[i][j],D[i][j]);
        }
    }
    FOR(i,1,n) {
        int right=-INF;
        FOR(j,1,m){
            L[i][j]=max(LD[i-1][j]+LU[i][j],LD[i][j]+LU[i+1][j]);
            ans=max(ans,right+L[i][j]);
            R[i][j]=max(RD[i-1][j]+RU[i][j],RD[i][j]+RU[i+1][j]);
            right=max(right+A[i][j],R[i][j]);
        }
    }
    FOR(i,1,n) {
        int right=-INF;
        FOR(j,1,m){
            F[i][j]=max(RD[i-1][j]+LD[i][j+1]+LU[i+1][j]+RU[i][j-1]+A[i][j],
                        RD[i][j-1]+LD[i-1][j]+LU[i][j+1]+RU[i+1][j]+A[i][j]);
            ans=max(ans,F[i][j]);
        }
    }
    if (n==1&&m==1) ans=max(ans,A[1][1]);

//    puts("RD:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",RD[i][j]);
//        puts("");
//    }
//    puts("LD:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",LD[i][j]);
//        puts("");
//    }
//    puts("RU:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",RU[i][j]);
//        puts("");
//    }
//    puts("LU:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",LU[i][j]);
//        puts("");
//    }
//    puts("D:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",D[i][j]);
//        puts("");
//    }
//    puts("U:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",U[i][j]);
//        puts("");
//    }
//    puts("L:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",L[i][j]);
//        puts("");
//    }
//    puts("R:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",R[i][j]);
//        puts("");
//    }
//    puts("F:");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%5d ",F[i][j]);
//        puts("");
//    }
    static int x=0;
    printf("Case #%d: %d\n",++x,ans);
    return 0;
}
int main() {
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
/*
*/
