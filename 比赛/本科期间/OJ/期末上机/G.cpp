#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#define REP(I,S,N) for (I=S;I<N;I++)
#define rREP(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
const int maxn=1e6+7;
const int INF=0x3f3f3f3f;
using namespace std;
typedef long long LL;
int f[507][507];
char a[507];
int main(){
    int T,n,m,i,j;
    while (~scanf("%s",a+1)){
        n=strlen(a+1);
        int ans=0;
        FOR(i,0,n+1) FOR(j,0,n+1) f[i][j]=0;
        FOR(i,1,n){
            rFOR(j,i,n){
                f[i][j]=max(f[i-1][j],f[i][j+1]);
                if (a[i]==a[j]){
                    if (i!=j)
                        f[i][j]=max(f[i][j],f[i-1][j+1]+2);
                    else f[i][j]=max(f[i][j],f[i-1][j+1]+1);
                }ans=max(ans,f[i][j]);
            }
        }printf("%d\n",ans);
    }
}