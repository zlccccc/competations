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
int f[maxn];
int main(){
    int T,n,m,i,j;
    while (~scanf("%d%d",&n,&m)){
        FOR(i,1,m) f[i]=-INF;f[0]=0;
        FOR(j,1,n){
            int a,b;
            scanf("%d%d",&a,&b);
            FOR(i,0,m) f[i+a]=max(f[i+a],f[i]+b);
        }if (f[m]>=0) printf("%d\n",f[m]);
        else printf("!\n");
    }
}