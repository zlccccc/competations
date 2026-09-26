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

int n,m;
int i,j,k;
int A[maxn],B[maxn],tot,L[maxn],R[maxn];
int ans;
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        int l,r;
        scanf("%d%d",&l,&r);
        A[l]++;A[r+1]--;
    }FOR(i,1,m) A[i]+=A[i-1];
    FOR(i,1,m){
        int pos=upper_bound(B,B+tot,A[i])-B;
        B[pos]=A[i];if (pos==tot) tot++;
        L[i]=tot;
    }tot=0;
    rFOR(i,1,m){
        int pos=upper_bound(B,B+tot,A[i])-B;
        B[pos]=A[i];if (pos==tot) tot++;
        R[i]=tot;
    }FOR(i,0,m) ans=max(ans,L[i]+R[i+1]);
//    FOR(i,1,m) printf("%d ",A[i]);puts("");
//    FOR(i,1,m) printf("%d ",L[i]);puts("");
//    FOR(i,1,m) printf("%d ",R[i]);puts("");
    printf("%d\n",ans);
}
/*
*/
