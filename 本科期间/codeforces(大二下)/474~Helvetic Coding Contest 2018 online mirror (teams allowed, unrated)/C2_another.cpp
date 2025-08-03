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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int p;
int A[maxn];
int dp[107][107];
inline int lowbit(int x){return x&-x;};
inline void update(int A[],int x,int val){
    x++;
    for (;x<=p;x+=lowbit(x)) A[x]=min(A[x],val);
}inline int query(int A[],int x){
    int ret=INF;x++;
    for (;x;x-=lowbit(x)) ret=min(ret,A[x]);
    return ret;
}
int main() {
    int i,j,l;
    int n,k;
    int now=0;
    scanf("%d%d%d",&n,&k,&p);
    FOR(i,1,n) scanf("%d",&A[i]),(A[i]+=A[i-1])%=p;
    FOR(j,1,k) REP(l,p)
        dp[j][l]=-INF;
    dp[1][0]=0;
    int ans=0;
    FOR(i,1,n){
        now^=1;
        rFOR(j,1,k){
            int now=0;
            FOR(l,0,A[i])
                now=max(now,dp[j][l]-l+A[i]);
            FOR(l,A[i]+1,p-1)
                now=max(now,dp[j][l]-l+A[i]+p);
            dp[j+1][A[i]]=now;
            if (j==k) ans=now;
        }
//        printf("%d:\n",i);
//        FOR(j,1,k){
//            REP(l,p){
//                printf("%10d ",dp[j][l]);
//            }puts("");
//        }
    }printf("%d\n",ans);
    return 0;
}
/*
8 3
3 3 1 2 2 1 1 3
0 0 1
*/
