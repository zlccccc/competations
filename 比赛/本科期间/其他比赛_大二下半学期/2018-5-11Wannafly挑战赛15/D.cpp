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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int n;
int val[10][maxn];
inline int lowbit(int x){return x&-x;}
void update(int *sum,int x,int val){
    for (;x<=n;x+=lowbit(x)) sum[x]+=val;
}
inline int query(int *sum,int x){
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=sum[x];
    return ret;
}
inline int query(int *sum,int l,int r){
    if (r<1||l>n) return 0;
    l=max(l,1);r=min(r,n);
    if (l>r) return 0;
    return query(sum,r)-query(sum,l-1);
}
char c[maxn];
int A[maxn];
LL ans;
int main() {
    int i,j,q,l,r;
    scanf("%s%d%d%d",c+1,&q,&l,&r);
    int len=strlen(c+1);n=len;
    FOR(i,1,len){
        A[i]=c[i]-'0';
        update(val[A[i]],i,1);
        FOR(j,A[i]+1,9)
            ans+=query(val[j],i-r+1,i-l+1);
    }
    while (q--){
        int x;
        scanf("%d%d",&i,&x);
        FOR(j,A[i]+1,9)
            ans-=query(val[j],i-r+1,i-l+1);
        FOR(j,0,A[i]-1)
            ans-=query(val[j],i+l-1,i+r-1);
        update(val[A[i]],i,-1);
        A[i]=x;
        update(val[A[i]],i,1);
        FOR(j,A[i]+1,9)
            ans+=query(val[j],i-r+1,i-l+1);
        FOR(j,0,A[i]-1)
            ans+=query(val[j],i+l-1,i+r-1);
        printf("%lld\n",ans);
    }
}
/*
*/
