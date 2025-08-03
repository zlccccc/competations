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
int n,m;
LL A[maxn],k;
int R[maxn][20];
int main(){
    int i,j;
    scanf("%d%d%lld",&n,&m,&k);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n+1) A[i]+=A[i-1];
    REP(i,20) R[n+1][i]=n+1;
    rFOR(i,1,n){
        R[i][0]=upper_bound(A+i,A+n+1,A[i-1]+k)-A;
        rep(j,1,20) R[i][j]=R[R[i][j-1]][j-1];
    }
//    FOR(i,1,n) printf("%d ",R[i][0]);puts("");
//    FOR(i,1,n) {
//        printf("%d : ",i);
//        REP(j,20) printf("%d ",R[i][j]);puts("");
//    }
    while (m--){
        int l,r,ans=0;
        scanf("%d%d",&l,&r);
        rREP(i,20) if (R[l][i]<=r){
            ans+=1<<i;
            l=R[l][i];
        }
//        printf("R:%d %d\n",l,R[l][0]);
        if (R[l][0]>r){
            ans++;
            printf("%d\n",ans);
        }else puts("Chtholly");
    }
}
/*
5 5 3
2 3 2 3 4
3 3
4 4
5 5
1 5
2 4
*/
