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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a; }
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int A[maxn];
double ans;
LL sum[maxn],cnt[maxn];
inline int lowbit(int x){return x&-x;}
inline void update(int x,int k){
    for (;x<=100000;x+=lowbit(x)) sum[x]+=k,cnt[x]++;
}inline LL query_sum(int x){
    LL ret=0;
    for (;x;x-=lowbit(x)) ret+=sum[x];
    return ret;
}inline LL query_cnt(int x){
    LL ret=0;
    for (;x;x-=lowbit(x)) ret+=cnt[x];
    return ret;
}
int main() {
    int n,m,i,j;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    reverse(A+1,A+1+n);
    FOR(i,1,n){
        LL cnt=query_cnt(A[i]-1),sum=query_sum(A[i]-1);
        ans+=1.0*cnt*n*(n+1)/2-1.0*sum*(n-i+1);
//        printf("%d : %d   %lld %lld   nowans=%f\n",A[i],i,cnt,sum,ans);
        update(A[i],i);
    }ans/=1.0*n*(n+1)/2;
//    printf("%.10f",ans);
    FOR(i,2,n) ans+=1.0*(n-i+1)*i*(i-1)/n/(n+1)/2;
    printf("%.10f\n",ans);
    return 0;
}
/*
3
2 3 1
2
1 2
*/
