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

int n;
int i,j,k;
int f[maxn],g[maxn];
int Q[maxn],Front,End;
int pre;
int main(){
    int q;
    scanf("%d%d",&n,&k);
    f[0]=0;
    FOR(i,1,n) f[i]=INF;//back;
    while(k--){
        int l,r;
        scanf("%d%d",&l,&r);
        FOR(i,0,n) g[i]=f[i];
        Front=1;End=0;
        FOR(i,0,n){
            while (Front<=End&&g[Q[End]]>=g[i]) End--;Q[++End]=i;
            if (0<=r-i&&r-i<=n) f[r-i]=min(f[r-i],g[Q[Front]]+1);
            f[i]=min(f[i],g[Q[Front]]+2);
            if (Q[Front]==i-(r-l)) Front++;
        }
        //FOR(i,0,n) printf("%d ",f[i]);puts("");
    }if (f[n]==INF) return 0*puts("Hungry");
    puts("Full");
    printf("%d\n",f[n]);
}
/*
*/
