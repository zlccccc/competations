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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,q;
int i,j,k;
int f[maxn],g[maxn];
inline int getid(int i,int j){
    return (i-1)*m+j;
}
bool solve(int n,int m){
    if (n==1&&m==1) return 1;
    if (n==1&&m==2) return 0;
    if (n==1&&m==3) return 0;
    if (n==1){
        FOR(i,1,m) g[i]=f[i];
        j=2;i=1;
        for (;j<=m;j+=2,i++) f[i]=g[j];
        j=1;
        for (;j<=m;j+=2,i++) f[i]=g[j];
        return 1;
    }if (n==2&&m==2) return 0;
    if (n==2&&m==3) return 0;
    if (n==3&&m==3){
        FOR(i,1,n*m) g[i]=f[i];
        f[getid(1,1)]=g[2];f[getid(1,2)]=g[9];f[getid(1,3)]=g[4];
        f[getid(2,1)]=g[7];f[getid(2,2)]=g[5];f[getid(2,3)]=g[3];
        f[getid(3,1)]=g[6];f[getid(3,2)]=g[1];f[getid(3,3)]=g[8];
        return 1;
    }FOR(i,1,n) if (i&1) {
        FOR(j,1,m-1) swap(f[getid(i,j)],f[getid(i,j+1)]);
        FOR(j,1,m-1) swap(f[getid(i,j)],f[getid(i,j+1)]);
    }
    FOR(j,1,m){
        if (j%4==1) FOR(i,1,n-1) swap(f[getid(i,j)],f[getid(i+1,j)]);
        if (j%4==3) rFOR(i,2,n) swap(f[getid(i,j)],f[getid(i-1,j)]);
    }
    return 1;
}bool mark;
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n*m) f[i]=i;
    if (n>m){
        FOR(i,1,n*m) g[i]=f[i];
        FOR(i,1,n) FOR(j,1,m) f[(j-1)*n+i]=g[getid(i,j)];
        swap(n,m);mark=1;
    }//FOR(i,1,n*m) printf("%d ",g[i]);puts("g");
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%d ",f[getid(i,j)]);
//        puts("");
//    }puts("");
    if (!solve(n,m)) return 0*puts("NO");
    if (mark){
        FOR(i,1,n*m) g[i]=f[i];
        FOR(i,1,n) FOR(j,1,m) f[(j-1)*n+i]=g[getid(i,j)];
        swap(n,m);mark=0;
    }puts("YES");
    FOR(i,1,n){
        FOR(j,1,m) printf("%d ",f[getid(i,j)]);
        puts("");
    }
}
/*
*/
