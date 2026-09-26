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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll* a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int b,w;
int i,j;
double ans;
int A[maxn][4];
int main(){
    freopen("black.in","r",stdin);
    freopen("black.out","w",stdout);
    scanf("%d%d",&b,&w);
    b--;w--;
    FOR(i,1,4000) A[i][0]=A[i][1]=1;
    FOR(i,1,w) A[i*2][0]=0;
    FOR(i,1,b) A[i*2][3]=1;
    printf("4 4000\n");
    REP(j,4){
        FOR(i,1,4000) if (A[i][j]) putchar('@');else putchar('.');
        puts("");
    }
}
/*
*/
