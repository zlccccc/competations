#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <map>
#include <set>
#define REP(I,S,N) for (I=S;I<N;I++)
#define rREP(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
const int maxn=1e6+7;
const int INF=0x3f3f3f3f;
using namespace std;
typedef long long LL;
LL f[maxn][2],a[maxn];
int main(){
    int T,n,m,i,j;
    while (~scanf("%d",&n)){
        FOR(i,1,n) f[i][0]=f[i][1]=0;
        FOR(i,1,n) scanf("%d",&a[i]);
        FOR(i,1,n){
            f[i][1]=max(f[i-1][1],f[i-1][0]+a[i]);//did
            f[i][0]=max(f[i-1][0],f[i-1][1]);
        }printf("%lld\n",max(f[n][0],f[n][1]));
    }
}