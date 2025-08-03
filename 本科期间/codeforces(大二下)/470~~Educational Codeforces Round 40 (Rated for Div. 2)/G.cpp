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

int n,r;LL k,t;
LL F[maxn],G[maxn];
bool check(LL x){
    LL remain=k,add=0;int i;
    FOR(i,1,n) G[i]=0;
    FOR(i,1,n){
        add+=G[i];
        if (add+F[i]<x){
            remain-=x-F[i]-add;
            G[i+r*2+1]-=x-F[i]-add;
            add=x-F[i];
        }if (remain<0) return 0;
    }
    return 1;
}
int main(){
    int i,j;
    scanf("%d%d%I64d",&n,&r,&k);
    FOR(i,1,n) scanf("%I64d",&t),F[max(1,i-r)]+=t,F[i+r+1]-=t;
    FOR(i,1,n) F[i]+=F[i-1];
    LL L=0,R=INFF;
    while (L+1<R){
        LL mid=(L+R)/2;
        if (check(mid)) L=mid;
        else R=mid;
    }printf("%I64d\n",L);
}
/*
*/
