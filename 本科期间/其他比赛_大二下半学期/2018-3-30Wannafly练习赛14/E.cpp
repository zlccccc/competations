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
#include <cassert>
#include <bitset>
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
int n,m,q;
int D[1007][1007];
bitset<1007> B[1007][1007],now;
int Q[1007];
vector<int> edge[maxn];
int main(){
    int i,j;
    scanf("%d%d%d",&n,&m,&q);
    FOR(i,1,n) FOR(j,1,n) D[i][j]=n+1;
    FOR(i,1,n) D[i][i]=0;
    FOR(j,1,m){
        int x,y;
        scanf("%d%d",&x,&y);
        if (D[x][y]<=1) continue;
        edge[x].push_back(y);
        edge[y].push_back(x);
        //这个dis求的是错的...我说为啥老是不对...
    }
    FOR(i,1,n){
        int s=0,t=0;
        Q[t++]=i;
        while (s<t){
            int u=Q[s++];
            for (int v:edge[u]) if (D[i][v]==n+1){
                Q[t++]=v;
                D[i][v]=D[i][u]+1;
            }
        }
    }
//    FOR(i,1,n){
//        FOR(j,1,n) printf("%d ",D[i][j]);puts("");
//    }
    FOR(i,1,n) FOR(j,1,n) B[i][D[i][j]][j]=1;
    FOR(i,1,n) FOR(j,1,n) B[i][j]|=B[i][j-1];
    while (q--){
        int x,y,k;
        scanf("%d",&k);
        now.reset();
        while (k--){
            scanf("%d%d",&x,&y);
            if (y>n) y=n;
            now|=B[x][y];
        }
        printf("%d\n",now.count());
    }
}
/*
5 6 6
2 3
1 3
2 5
1 3
3 2
2 5
1
3 1

1
1 1

1
1 4

1
5 2

1
1 4

2
1 0
5 1
*/
