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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k,l;
int x[maxn],y[maxn];
double f[307][307];
inline double len(int i,int j){
    return sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
}
inline double get(int i,int j,int k){
    double a=len(i,j),b=len(j,k),c=len(i,k);
    double n=(a+b+c)/2;
//    printf("get : %d %d %d;  %lf\n",i,j,k,sqrt(n*(n-a)*(n-b)*(n-c)));
    return sqrt(n*(n-a)*(n-b)*(n-c));
}
int main(){
    while (~scanf("%d",&n)){
        assert(n>3);
        FOR(i,1,n) scanf("%d%d",&x[i],&y[i]);
        FOR(i,1,n) FOR(j,1,n) f[i][j]=INF;
        FOR(l,1,n-1){
            FOR(i,1,n-l){
                j=i+l;
                if (l==1) f[i][j]=0;
                FOR(k,i+1,j-1)
                    f[i][j]=min(f[i][j],max(max(f[i][k],f[k][j]),get(i,j,k)));
            }
        }
    //    FOR(i,1,n) printf("%lf\n",f[i][i+n-1]);
    //    FOR(i,1,n){
    //        FOR(j,1,n*2) printf("%.3lf ",f[i][j]);puts("");
    //    }
        printf("%.1lf\n",f[1][n]);
    }
}
/*
6
1 1
7 0
6 2
9 5
3 5
0 3
*/
