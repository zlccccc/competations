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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
char c[17][17];
int main(){
    int x,y;
    REP(i,9) REP(j,3) scanf("%s",c[i]+j*3);
    scanf("%d%d",&x,&y);x--;y--;
//    REP(i,9) printf("%s",c[i]),puts("");
    x%=3;y%=3;x*=3;y*=3;
//    printf("%d %d\n",x,y);
    bool mark=1;
    REP(i,3) REP(j,3) if (c[i+x][j+y]=='.') mark=0,c[i+x][j+y]='!';
    if (mark)
        REP(i,9)REP(j,9) if (c[i][j]=='.') c[i][j]='!';
    REP(i,9){
        if (i&&i%3==0) puts("");
        REP(j,9){
            if (j&&j%3==0) putchar(' ');
            putchar(c[i][j]);
        }puts("");
    }
}
/*
*/
