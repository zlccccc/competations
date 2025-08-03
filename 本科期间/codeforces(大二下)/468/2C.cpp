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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
int ans;
int a[maxn];
int MIN,A,B,C;
int main(){
    scanf("%d",&n);MIN=INF;
    REP(i,n) scanf("%d",&a[i]),MIN=min(MIN,a[i]);
    REP(i,n){
        if (a[i]==MIN) A++;
        if (a[i]==MIN+1) B++;
        if (a[i]==MIN+2) C++;
    }if (C==0){
        printf("%d\n",n);
        REP(i,n) printf("%d ",a[i]);
        return 0;
    }
    int D1=min(A,C);
    int A1=A-D1,B1=B+D1*2,C1=C-D1;
    int A2=A+B/2,B2=B%2,C2=C+B/2;
    if (abs(A-A1)+abs(B-B1)+abs(C-C1)>=abs(A-A2)+abs(B-B2)+abs(C-C2)){
        printf("%d\n",n-(abs(A-A1)+abs(B-B1)+abs(C-C1))/2);
        while (A1--) printf("%d ",MIN);
        while (B1--) printf("%d ",MIN+1);
        while (C1--) printf("%d ",MIN+2);
    }else{
        printf("%d\n",n-(abs(A-A2)+abs(B-B2)+abs(C-C2))/2);
        while (A2--) printf("%d ",MIN);
        while (B2--) printf("%d ",MIN+1);
        while (C2--) printf("%d ",MIN+2);
    }
}
/*
6
0 0 0 0 0 0
*/
