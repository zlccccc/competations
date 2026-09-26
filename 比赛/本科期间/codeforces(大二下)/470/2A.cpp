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
char A[507][507];
int ax[4]={0,0,-1,1};
int ay[4]={-1,1,0,0};
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%s",A[i]+1);
    FOR(i,1,n) FOR(j,1,m) REP(k,4){
        int x=i+ax[k],y=j+ay[k];
        if (A[i][j]=='S'&&A[x][y]=='W') return 0*puts("No");
    }puts("Yes");
    FOR(i,1,n) FOR(j,1,m) if (A[i][j]=='.') A[i][j]='D';
    FOR(i,1,n) printf("%s\n",A[i]+1);
}
/*
*/
