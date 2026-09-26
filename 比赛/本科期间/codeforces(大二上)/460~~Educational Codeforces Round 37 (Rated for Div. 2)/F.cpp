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
#include <bitset>
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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int f[maxn],a[maxn];
bool could[maxn];LL sum[maxn];
void build(int x,int l,int r){
    if (l==r){
        sum[x]=a[l];could[x]=1;
        if (f[sum[x]]==sum[x]) could[x]=0;
        return;
    }int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    sum[x]=sum[x<<1]+sum[x<<1|1];
    could[x]=could[x<<1]|could[x<<1|1];
}
void update(int x,int l,int r,int L,int R){
    if (!could[x]) return;
    if (L==R){
        sum[x]=f[sum[x]];
        if (f[sum[x]]==sum[x]) could[x]=0;
        return;
    }int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,L,mid);
    if (mid<r) update(x<<1|1,l,r,mid+1,R);
    sum[x]=sum[x<<1]+sum[x<<1|1];
    could[x]=could[x<<1]|could[x<<1|1];
}
LL query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r) return sum[x];
    LL ret=0;int mid=(L+R)/2;
    if (l<=mid) ret+=query(x<<1,l,r,L,mid);
    if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
    return ret;
}
int n,m,k;
int i,j;
int op,l,r;
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,1000000)
        for (j=i;j<=1000000;j+=i) f[j]++;
    FOR(i,1,n) scanf("%d",&a[i]);
    build(1,1,n);
    while (m--){
        scanf("%d%d%d",&op,&l,&r);
        if (op==1) update(1,l,r,1,n);
        else printf("%I64d\n",query(1,l,r,1,n));
    }
}
/*
*/
