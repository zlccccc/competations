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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
    LL del,sum,add;
}T[maxn<<2];
LL a[maxn];//-
node merge(const node &A,const node &B){
    node ret;
    ret.del=max(A.del,B.del);
    ret.sum=max(A.sum,B.sum);
    ret.add=max(A.add,B.add);
    return ret;
}
void update(int x,int pos,int L,int R){
//    printf("upd: %d %d %d %d\n",x,pos,L,R);
    if (L==R) {
        T[x].del=a[L+1]-a[L]-abs(a[L])-abs(a[L+1]);
        T[x].add=a[L]-a[L+1]-abs(a[L])-abs(a[L+1]);
        T[x].sum=abs(a[L]+a[L+1])-abs(a[L])-abs(a[L+1]);
//        printf("     %d(%d) : %I64d %I64d %I64d;\n",x,L,T[x].del,T[x].sum,T[x].add);
        return;
    }int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    else update(x<<1|1,pos,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
node query(int x,int l,int r,int L,int R){
//    printf("query: %d %d %d %d %d\n",x,l,r,L,R);
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (r<=mid) return query(x<<1,l,r,L,mid);
    else if (mid<l) return query(x<<1|1,l,r,mid+1,R);
    else return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
}
int n,m,q;
int i,j;
LL all;
int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%I64d",&a[i]);
    rFOR(i,2,n) a[i]-=a[i-1];a[1]=0;
    FOR(i,2,n) update(1,i,1,n),all+=abs(a[i]);
    scanf("%d",&q);
    while (q--){
        int op,l,r,x;
        scanf("%d%d%d%d",&op,&l,&r,&x);
        if (op==1){
            LL ans=-INFF;
            if (l==1) ans=max(ans,abs(a[2]-x)-abs(a[2])),l++;
            if (r==n) ans=max(ans,abs(a[n]+x)-abs(a[n])),r--;
            if (l<=r){
                node now=query(1,l,r,1,n);
//                printf("now= %I64d %I64d %I64d",now.del,now.add,now.sum);puts("");
                ans=max(ans,now.sum);
                ans=max(ans,now.del-2*x);
                ans=max(ans,now.add+2*x);
            }printf("%I64d\n",ans+all);
        }else{
            if (2<=l){
                all-=abs(a[l]);a[l]+=x;all+=abs(a[l]);
                update(1,l,1,n);update(1,l-1,1,n);
            }if (r+1<=n){
                all-=abs(a[r+1]);a[r+1]-=x;all+=abs(a[r+1]);
                update(1,r,1,n);update(1,r+1,1,n);
            }
        }
//        FOR(i,1,n) printf("%12lld",a[i]);puts("<-  A");
//        printf("all :=  %I64d\n",all);
    }
}
/*
5
1 1 1 1 1
5
1 2 4 1
2 2 3 1
2 4 4 2
2 3 4 1
1 3 3 2
*/
