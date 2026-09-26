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

int calc(LL n,int F,int k){
    int cnt=1;
    while (n%k==0) n/=k,cnt++;
    F=F/cnt*(cnt+1);
    return F;
}
int T;
int cnt,p[maxn];
LL F[maxn];
int main(){
    int i,j;
    FOR(i,2,10000){
        REP(j,cnt) if (i%p[j]==0) break;
        if (j==cnt) p[cnt++]=i;
    }
//    REP(j,cnt) printf("%lld ",p[j]);
    FOR(i,1,1000000) F[i]=INFF;
    F[1]=1;
    FOR(i,1,1000000){
        if (F[i]==INFF) continue;
        REP(j,cnt){
            int t=calc(F[i],i,p[j]);
            if ((double)F[i]*p[j]<INFF&&t<=1000000)
                F[t]=min(F[t],F[i]*p[j]);
        }
//        printf("%lld: %d\n",F[i],i);
    }
    rFOR(i,1,1000000-1) F[i]=min(F[i],F[i+1]);
//    FOR(i,1,1000) printf("%d:%lld ",i,F[i]);
    scanf("%d",&T);
    while (T--){
        LL n;
        scanf("%lld",&n);
        printf("%d\n",upper_bound(F,F+1000000,n)-F-1);
    }
}
/*
6
13
9
1
13
16
1000000000000000000
*/
