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
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i;
int X[maxn],Y[maxn],A[maxn],B[maxn];
int MIN[maxn],MAX[maxn];
int cnt[maxn];
void calc(){
    int i;
    FOR(i,0,n*4) MIN[i]=INF,MAX[i]=-INF;
    FOR(i,1,m){
        MIN[X[i]]=min(MIN[X[i]],Y[i]);
        MAX[X[i]]=max(MAX[X[i]],Y[i]);
    }FOR(i,1,m){
        if (MIN[X[i]]<Y[i]) cnt[i]++;
        if (MAX[X[i]]>Y[i]) cnt[i]++;
    }
//    FOR(i,0,n*4) if (MIN[i]!=INF) printf("%d: %d-%d\n",i,MIN[i],MAX[i]);puts("");
}
int ans[8];
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m) scanf("%d%d",&A[i],&B[i]);
    FOR(i,1,m) X[i]=A[i],Y[i]=B[i];calc();
//    FOR(i,1,m) printf("%d ",cnt[i]);puts("");
    FOR(i,1,m) X[i]=B[i],Y[i]=A[i];calc();
//    FOR(i,1,m) printf("%d ",cnt[i]);puts("");
    FOR(i,1,m) X[i]=A[i]+B[i],Y[i]=A[i]-B[i]+n;calc();
//    FOR(i,1,m) printf("%d ",cnt[i]);puts("");
    FOR(i,1,m) X[i]=A[i]-B[i]+n,Y[i]=A[i]+B[i];calc();
//    FOR(i,1,m) printf("%d ",cnt[i]);puts("");
    FOR(i,1,m) ans[cnt[i]]++;
    REP(i,9) {printf("%d",ans[i]);if (i!=8) putchar(' ');}
}
/*
4 2000
4478
*/
