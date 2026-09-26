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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,h,i,j,k;
int tot,b[maxn];
int f[20][1<<12|7];
int limit[30];
vector<int> could[1<<12|7];
int main(){
    while (~scanf("%d%d",&n,&m)){
        tot=0;
        FOR(i,1,n){
            limit[i]=0;
            FOR(j,1,m){
                scanf("%d",&k);
                limit[i]=limit[i]<<1|k;
            }
        }
        REP(i,(1<<m)) if ((i&(i>>1))==0) b[tot++]=i;
//        printf("tot=%d\n",tot);
        REP(i,tot) could[i].clear();
        REP(i,tot)
            REP(j,tot)
                if ((b[i]&b[j])==0) could[i].push_back(j);
        FOR(k,1,n)
            REP(i,tot)
                f[k][i]=0;
//        REP(i,tot) for (int j:could[i]) printf("%d - %d\n",b[i],b[j]);
        f[0][0]=1;
        FOR(k,1,n)
            REP(i,tot) if ((b[i]&limit[k])==b[i])
                for (int j=0;j<could[i].size();j++)
                    (f[k][i]+=f[k-1][could[i][j]])%=100000000;
        int ans=0;
//        FOR(k,1,n){
//            REP(i,tot) printf("%d ",f[k][i]);puts("");
//        }
        REP(i,tot) (ans+=f[n][i])%=100000000;
        if (n==0||m==0) puts("0");
        else printf("%d\n",ans);
    }
}
/*
3 5
1 0 1 0 0
0 1 1 1 1
1 0 1 1 1
5 3
1 0 1
0 1 0
1 1 1
1 1 0
1 1 0

12 7
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 0 1 1 1
1 1 1 1 1 1 0 1 1 1 1 1
1 1 1 1 1 0 1 1 0 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
*/
