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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
LL A[maxn],B[maxn],C[maxn];
LL F[maxn],D[maxn],CNT,ANS[maxn];//F:add,D:melt
int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%I64d",&A[i]);
    FOR(i,1,n) scanf("%I64d",&B[i]);
    FOR(i,1,n) C[i]=B[i]+C[i-1];
    FOR(i,1,n) {
        int now=lower_bound(C+i,C+1+n,C[i-1]+A[i])-C;
        F[now]+=C[i-1]+A[i]-C[now-1];D[now]++;
        CNT++;CNT-=D[i];
        ANS[i]=F[i]+B[i]*CNT;
//        printf("melted(now):%d cnt=%lld; F=%lld\n",now,CNT,F[i]);
    }
    FOR(i,1,n) printf("%I64d ",ANS[i]);
}
/*
5
0 0 0 0 0
0 0 0 0 50
*/
