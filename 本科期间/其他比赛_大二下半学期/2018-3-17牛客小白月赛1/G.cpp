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
#include <cstdlib>
#include <iomanip>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T;
int n,m,t;
int i,j,k;
int A[3607][3607],B[3607][3607];
int main(){
    scanf("%d",&n);
    FOR(i,0,n*4+1) FOR(j,0,n*4+1) A[i][j]=B[i][j]=-INF;
    FOR(i,1,n*4-3) {
        int mid=(i+1)/2;
        int s,t,T;
        T=min(i,n*4-3-i+1);
        if (T>n) T=(T%2)|n;
        if (T>n) T-=2;
        if (i&1) s=mid-T/2,t=mid+T/2;
        else s=mid+1-T/2,t=mid+T/2;
//        printf("s,t=%d-%d;T=%d\n",s,t,T);
        FOR(j,s,t) scanf("%d",&A[i][j]);
    }
    B[1][1]=A[1][1];
    FOR(i,1,n*4){
        FOR(j,1,n*4){
            B[i+1][j]=max(B[i+1][j],B[i][j]+A[i+1][j]);
            B[i+1][j+1]=max(B[i+1][j+1],B[i][j]+A[i+1][j+1]);
            B[i+2][j+1]=max(B[i+2][j+1],B[i][j]+A[i+2][j+1]);
        }
    }printf("%d\n",B[4*n-3][2*n-1]);
}
/*
4
-1
-1 -1
-1 -1 -1
-1 -1 -1 -1
-1 -1 -1
-1 -1 -1 -1
-1 -1 -1
-1 -1 -1 -1
-1 -1 -1
-1 -1 -1 -1
-1 -1 -1
-1 -1
-1
*/
