#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
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
int i,j;
int c[maxn];
LL f[maxn];
LL W,B,X;
int all;
int main(){
    scanf("%d%I64d%I64d%I64d",&n,&W,&B,&X);
    FOR(i,1,n) scanf("%d",&c[i]),all+=c[i];
    FOR(i,1,all) f[i]=-1;
    all=0;f[0]=W;
    FOR(i,1,n){
        int cost;
        scanf("%d",&cost);
        while (c[i]--){
            rFOR(j,0,all) if (f[j]>=cost){
                f[j+1]=max(f[j+1],f[j]-cost);
                all=max(all,j+1);
            }
        }
//        FOR(j,0,all)printf("%d ",f[j]);puts("");
        FOR(j,0,all) f[j]=min(W+B*j,f[j]+X);
    }printf("%d\n",all);
}
/*
*/
